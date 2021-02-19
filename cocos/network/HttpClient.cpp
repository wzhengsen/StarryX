/****************************************************************************
 Copyright (c) 2012      greathqy
 Copyright (c) 2012      cocos2d-x.org
 Copyright (c) 2013-2016 Chukong Technologies Inc.
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "network/HttpClient.h"
#include <errno.h>
#include <curl/curl.h>
#include "base/CCDirector.h"
#include "base/ccUTF8.h"
#include "platform/CCFileUtils.h"

NS_CC_BEGIN

namespace network {

static HttpClient* _httpClient = nullptr; // pointer to singleton

typedef size_t (*write_callback)(void *ptr, size_t size, size_t nmemb, void *stream);

// Callback function used by libcurl for collect response data
static size_t writeData(void *ptr, size_t size, size_t nmemb, void *stream)
{
    std::vector<char> *recvBuffer = (std::vector<char>*)stream;
    size_t sizes = size * nmemb;
    
    // add data to the end of recvBuffer
    // write data maybe called more than once in a single request
    recvBuffer->insert(recvBuffer->end(), (char*)ptr, (char*)ptr+sizes);
    
    return sizes;
}

// Callback function used by libcurl for collect header data
static size_t writeHeaderData(void *ptr, size_t size, size_t nmemb, void *stream)
{
    std::vector<char> *recvBuffer = (std::vector<char>*)stream;
    size_t sizes = size * nmemb;
    
    // add data to the end of recvBuffer
    // write data maybe called more than once in a single request
    recvBuffer->insert(recvBuffer->end(), (char*)ptr, (char*)ptr+sizes);
    
    return sizes;
}


static int processGetTask(HttpClient* client, HttpRequest* request, write_callback callback, void *stream, long *errorCode, write_callback headerCallback, void *headerStream, char* errorBuffer);
static int processPostTask(HttpClient* client, HttpRequest* request, write_callback callback, void *stream, long *errorCode, write_callback headerCallback, void *headerStream, char* errorBuffer);
static int processPutTask(HttpClient* client,  HttpRequest* request, write_callback callback, void *stream, long *errorCode, write_callback headerCallback, void *headerStream, char* errorBuffer);
static int processDeleteTask(HttpClient* client,  HttpRequest* request, write_callback callback, void *stream, long *errorCode, write_callback headerCallback, void *headerStream, char* errorBuffer);
// int processDownloadTask(HttpRequest *task, write_callback callback, void *stream, int *errorCode);

template<typename _Cont, typename _Fty>
static void __clearQueue(_Cont& queue, _Fty pred) {
    for (auto it = queue.begin(); it != queue.end();)
    {
        if (!pred || pred((*it)))
        {
            (*it)->release();
            it = queue.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

// Worker thread
void HttpClient::networkThread()
{
    increaseThreadCount();

    while (true)
    {
        HttpRequest *request;

        // step 1: send http request if the requestQueue isn't empty
        {
            std::lock_guard<std::recursive_mutex> lock(_requestQueueMutex);
            while (_requestQueue.empty())
            {
                _sleepCondition.wait(_requestQueueMutex);
            }
            request = _requestQueue.front();
            _requestQueue.pop_front();
        }

        if (request == _requestSentinel) {
            break;
        }

        // step 2: libcurl sync access
        
        // Create a HttpResponse object, the default setting is http access failed
        HttpResponse *response = new (std::nothrow) HttpResponse(request);

        processResponse(response, _responseMessage);


        // add response packet into queue
        _responseQueueMutex.lock();
        _responseQueue.push_back(response);
        _responseQueueMutex.unlock();

        if (!_dispatchOnWorkThread) {
            std::lock_guard<std::recursive_mutex> lck(_schedulerMutex);
            if (_scheduler != nullptr)
                _scheduler->performFunctionInCocosThread(CC_CALLBACK_0(HttpClient::dispatchResponseCallbacks, this));
        }
        else
            dispatchResponseCallbacks();
    }
    
    // cleanup: if worker thread received quit signal, clean up un-completed request queue
    _requestQueueMutex.lock();
    __clearQueue(_requestQueue, ClearRequestPredicate{});
    _requestQueueMutex.unlock();

    _responseQueueMutex.lock();
    __clearQueue(_responseQueue, ClearResponsePredicate{});
    _responseQueueMutex.unlock();

    decreaseThreadCountAndMayDeleteThis();
}

// Worker thread
void HttpClient::networkThreadAlone(HttpRequest* request, HttpResponse* response,bool async)
{
    increaseThreadCount();

    char responseMessage[RESPONSE_BUFFER_SIZE] = { 0 };
    processResponse(response, responseMessage);

    auto dispatchFunc = [this, response, request] {
        const ccHttpRequestCallback& callback = request->getCallback();
        Ref* pTarget = request->getTarget();
        SEL_HttpResponse pSelector = request->getSelector();

        if (callback != nullptr)
        {
            callback(this, response);
        }
        else if (pTarget && pSelector)
        {
            (pTarget->*pSelector)(this, response);
        }
        response->release();
        // do not release in other thread
        request->release();
    };

    if (!_dispatchOnWorkThread && async) {
        std::lock_guard<std::recursive_mutex> lck(_schedulerMutex);
        if (_scheduler != nullptr)
            _scheduler->performFunctionInCocosThread(dispatchFunc);
    }
    else
        dispatchFunc();

    decreaseThreadCountAndMayDeleteThis();
}

//Configure curl's timeout property
static bool configureCURL(HttpClient* client, CURL* handle, char* errorBuffer)
{
    if (!handle) {
        return false;
    }
    
    int code = curl_easy_setopt(handle, CURLOPT_ERRORBUFFER, errorBuffer);
    if (code != CURLE_OK) {
        return false;
    }
    code = curl_easy_setopt(handle, CURLOPT_TIMEOUT, HttpClient::getInstance()->getTimeoutForRead());
    if (code != CURLE_OK) {
        return false;
    }
    code = curl_easy_setopt(handle, CURLOPT_CONNECTTIMEOUT, HttpClient::getInstance()->getTimeoutForConnect());
    if (code != CURLE_OK) {
        return false;
    }

    std::string sslCaFilename = client->getSSLVerification();
    if (sslCaFilename.empty()) {
        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0L);
    } else {
        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 2L);
        curl_easy_setopt(handle, CURLOPT_CAINFO, sslCaFilename.c_str());
    }
    
    // FIXED #3224: The subthread of CCHttpClient interrupts main thread if timeout comes.
    // Document is here: http://curl.haxx.se/libcurl/c/curl_easy_setopt.html#CURLOPTNOSIGNAL 
    curl_easy_setopt(handle, CURLOPT_NOSIGNAL, 1L);

    curl_easy_setopt(handle, CURLOPT_ACCEPT_ENCODING, "");

    return true;
}

class CURLRaii
{
    /// Instance of CURL
    CURL *_curl;
    /// Keeps custom header data
    curl_slist *_headers;
    curl_slist *_hosts;
public:
    CURLRaii()
        : _curl(curl_easy_init())
        , _headers(nullptr)
        , _hosts(nullptr)
    {
    }

    ~CURLRaii()
    {
        if (_curl)
            curl_easy_cleanup(_curl);
        /* free the linked list for header data */
        if (_headers)
            curl_slist_free_all(_headers);
    }

    template <class T>
    bool setOption(CURLoption option, T data)
    {
        return CURLE_OK == curl_easy_setopt(_curl, option, data);
    }

    /**
     * @brief Inits CURL instance for common usage
     * @param request Null not allowed
     * @param callback Response write callback
     * @param stream Response write stream
     */
    bool init(HttpClient* client, HttpRequest* request, write_callback callback, void* stream, write_callback headerCallback, void* headerStream, char* errorBuffer)
    {
        if (!_curl)
            return false;
        if (!configureCURL(client, _curl, errorBuffer))
            return false;

		// ����ʹ��HttpRequest�ĺ��볬ʱʱ�串��ԭĬ�ϳ�ʱʱ��
		auto code = curl_easy_setopt(_curl, CURLOPT_CONNECTTIMEOUT_MS, request->GetTimeout());
		if (code != CURLE_OK) {
			return false;
		}
        code = curl_easy_setopt(_curl, CURLOPT_TIMEOUT_MS, request->GetTimeout());
        if (code != CURLE_OK) {
            return false;
        }

        /* get custom header data (if set) */
        auto& headers = request->getHeaders();
        if(!headers.empty())
        {
            /* append custom headers one by one */
            for (auto& header : headers)
                _headers = curl_slist_append(_headers,header.c_str());
            /* set custom headers for curl */
            if (!setOption(CURLOPT_HTTPHEADER, _headers))
                return false;
        }
        /* get custom host data (if set) */
        auto& hosts = request->getHosts();
        if (!hosts.empty()) {
            /* append hosts headers one by one */
            for (auto& host : hosts)
                _hosts = curl_slist_append(_hosts, host.c_str());
            /* set custom hosts for curl */
            if (!setOption(CURLOPT_RESOLVE, _hosts))
                return false;
        }
        std::string cookieFilename = client->getCookieFilename();
        if (!cookieFilename.empty()) {
            if (!setOption(CURLOPT_COOKIEFILE, cookieFilename.c_str())) {
                return false;
            }
            if (!setOption(CURLOPT_COOKIEJAR, cookieFilename.c_str())) {
                return false;
            }
        }
        return setOption(CURLOPT_URL, request->getUrl())
                && setOption(CURLOPT_WRITEFUNCTION, callback)
                && setOption(CURLOPT_WRITEDATA, stream)
                && setOption(CURLOPT_HEADERFUNCTION, headerCallback)
                && setOption(CURLOPT_HEADERDATA, headerStream);
        
    }

    /// @param responseCode Null not allowed
    CURLcode perform(long *responseCode)
    {
        auto ret1 = curl_easy_perform(_curl);
        auto ret2 = curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE, responseCode);
        if (ret2 == CURLE_OK) {
            if(*responseCode >= 200 && *responseCode < 300)
                return CURLE_OK;
        }
        else {
            if (ret1 == CURLE_OK) ret1 = ret2;
            CCLOGERROR("Curl curl_easy_getinfo failed: %s", curl_easy_strerror(ret2));
        }
        // request failed, ensure internalCode not CURLE_OK
        return ret1 != CURLE_OK ? ret1 : (CURLcode)-1;
    }
};

//Process Get Request
static int processGetTask(HttpClient* client, HttpRequest* request, write_callback callback, void* stream, long* responseCode, write_callback headerCallback, void* headerStream, char* errorBuffer)
{
    CURLRaii curl;
    bool ok = curl.init(client, request, callback, stream, headerCallback, headerStream, errorBuffer)
        && curl.setOption(CURLOPT_FOLLOWLOCATION, true);
    return ok ? curl.perform(responseCode) : -1;
}

//Process POST Request
static int processPostTask(HttpClient* client, HttpRequest* request, write_callback callback, void* stream, long* responseCode, write_callback headerCallback, void* headerStream, char* errorBuffer)
{
    CURLRaii curl;
    bool ok = curl.init(client, request, callback, stream, headerCallback, headerStream, errorBuffer)
            && curl.setOption(CURLOPT_POST, 1)
            && curl.setOption(CURLOPT_POSTFIELDS, request->getRequestData())
            && curl.setOption(CURLOPT_POSTFIELDSIZE, request->getRequestDataSize());
    return ok ? curl.perform(responseCode) : -1;
}

//Process PUT Request
static int processPutTask(HttpClient* client, HttpRequest* request, write_callback callback, void* stream, long* responseCode, write_callback headerCallback, void* headerStream, char* errorBuffer)
{
    CURLRaii curl;
    bool ok = curl.init(client, request, callback, stream, headerCallback, headerStream, errorBuffer)
            && curl.setOption(CURLOPT_CUSTOMREQUEST, "PUT")
            && curl.setOption(CURLOPT_POSTFIELDS, request->getRequestData())
            && curl.setOption(CURLOPT_POSTFIELDSIZE, request->getRequestDataSize());
    return ok ? curl.perform(responseCode) : -1;
}

//Process DELETE Request
static int processDeleteTask(HttpClient* client, HttpRequest* request, write_callback callback, void* stream, long* responseCode, write_callback headerCallback, void* headerStream, char* errorBuffer)
{
    CURLRaii curl;
    bool ok = curl.init(client, request, callback, stream, headerCallback, headerStream, errorBuffer)
            && curl.setOption(CURLOPT_CUSTOMREQUEST, "DELETE")
            && curl.setOption(CURLOPT_FOLLOWLOCATION, true);
    return ok ? curl.perform(responseCode) : -1;
}

// HttpClient implementation
HttpClient* HttpClient::getInstance()
{
    if (_httpClient == nullptr)
    {
        _httpClient = new (std::nothrow) HttpClient();
    }
    
    return _httpClient;
}

void HttpClient::destroyInstance()
{
    if (nullptr == _httpClient)
    {
        CCLOG("HttpClient singleton is nullptr");
        return;
    }

    CCLOG("HttpClient::destroyInstance begin");
    auto thiz = _httpClient;
    _httpClient = nullptr;

    thiz->_scheduler->unscheduleAllForTarget(thiz);
    thiz->_schedulerMutex.lock();
    thiz->_scheduler = nullptr;
    thiz->_schedulerMutex.unlock();

    thiz->_requestQueueMutex.lock();
    thiz->_requestQueue.push_back(thiz->_requestSentinel);
    thiz->_requestQueueMutex.unlock();

    thiz->_sleepCondition.notify_one();
    thiz->decreaseThreadCountAndMayDeleteThis();

    CCLOG("HttpClient::destroyInstance() finished!");
}

void HttpClient::enableCookies(const char* cookieFile)
{
    std::lock_guard<std::recursive_mutex> lock(_cookieFileMutex);
    if (cookieFile)
    {
        _cookieFilename = std::string(cookieFile);
    }
    else
    {
        _cookieFilename = (FileUtils::getInstance()->getWritablePath() + "cookieFile.txt");
    }
}
    
void HttpClient::setSSLVerification(const std::string& caFile)
{
    std::lock_guard<std::recursive_mutex> lock(_sslCaFileMutex);
    _sslCaFilename = caFile;
}

HttpClient::HttpClient()
: _isInited(false)
, _dispatchOnWorkThread(false)
, _timeoutForConnect(30)
, _timeoutForRead(60)
, _threadCount(0)
, _cookie(nullptr)
, _requestSentinel(new HttpRequest())
, _clearRequestPredicate(nullptr)
, _clearResponsePredicate(nullptr)
{
    CCLOG("In the constructor of HttpClient!");
    memset(_responseMessage, 0, RESPONSE_BUFFER_SIZE * sizeof(char));
    _scheduler = Director::getInstance()->getScheduler();
    increaseThreadCount();
}

HttpClient::~HttpClient()
{
    CC_SAFE_RELEASE(_requestSentinel);
    CCLOG("HttpClient destructor");
}

//Lazy create semaphore & mutex & thread
bool HttpClient::lazyInitThreadSemaphore()
{
    if (_isInited)
    {
        return true;
    }
    else
    {
        auto t = std::thread(CC_CALLBACK_0(HttpClient::networkThread, this));
        t.detach();
        _isInited = true;
    }
    
    return true;
}

//Add a get task to queue
void HttpClient::send(HttpRequest* request)
{
    if (false == lazyInitThreadSemaphore())
    {
        return;
    }
    
    if (!request)
    {
        return;
    }
        
    request->retain();

    _requestQueueMutex.lock();
    _requestQueue.push_back(request);
    _requestQueueMutex.unlock();

    // Notify thread start to work
    _sleepCondition.notify_one();
}

void HttpClient::sendImmediate(HttpRequest* request)
{
    if(!request)
    {
        return;
    }

    request->retain();
    // Create a HttpResponse object, the default setting is http access failed
    HttpResponse *response = new (std::nothrow) HttpResponse(request);

	if (request->IsAsync()) {
		auto t = std::thread(&HttpClient::networkThreadAlone, this, request, response, true);
		t.detach();
	}
	else {
		networkThreadAlone(request, response, false);
	}
}

// Poll and notify main thread if responses exists in queue
void HttpClient::dispatchResponseCallbacks()
{
    // log("CCHttpClient::dispatchResponseCallbacks is running");
    //occurs when cocos thread fires but the network thread has already quited
    HttpResponse* response = nullptr;

    _responseQueueMutex.lock();
    if (!_responseQueue.empty())
    {
        response = _responseQueue.front();
        _responseQueue.pop_front();
    }
    _responseQueueMutex.unlock();
    
    if (response)
    {
        HttpRequest *request = response->getHttpRequest();
        const ccHttpRequestCallback& callback = request->getCallback();
        Ref* pTarget = request->getTarget();
        SEL_HttpResponse pSelector = request->getSelector();

        if (callback != nullptr)
        {
            callback(this, response);
        }
        else if (pTarget && pSelector)
        {
            (pTarget->*pSelector)(this, response);
        }
        
        response->release();
        // do not release in other thread
        request->release();
    }
}

// Process Response
void HttpClient::processResponse(HttpResponse* response, char* responseMessage)
{
    auto request = response->getHttpRequest();
    long responseCode = -1;
    int retValue = 0;

    // Process the request -> get response packet
    switch (request->getRequestType())
    {
    case HttpRequest::Type::GET: // HTTP GET
        retValue = processGetTask(this, request,
            writeData,
            response->getResponseData(),
            &responseCode,
            writeHeaderData,
            response->getResponseHeader(),
            responseMessage);
        break;

    case HttpRequest::Type::POST: // HTTP POST
        retValue = processPostTask(this, request,
            writeData,
            response->getResponseData(),
            &responseCode,
            writeHeaderData,
            response->getResponseHeader(),
            responseMessage);
        break;

    case HttpRequest::Type::PUT:
        retValue = processPutTask(this, request,
            writeData,
            response->getResponseData(),
            &responseCode,
            writeHeaderData,
            response->getResponseHeader(),
            responseMessage);
        break;

    case HttpRequest::Type::DELETE:
        retValue = processDeleteTask(this, request,
            writeData,
            response->getResponseData(),
            &responseCode,
            writeHeaderData,
            response->getResponseHeader(),
            responseMessage);
        break;

    default:
        CCASSERT(false, "CCHttpClient: unknown request type, only GET, POST, PUT or DELETE is supported");
        break;
    }

    // write data to HttpResponse
    response->setResponseCode(static_cast<int>(responseCode));
    response->setInternalCode(retValue);
    if (retValue != 0)
    {
        response->setSucceed(false);
        response->setErrorBuffer(responseMessage);
    }
    else
    {
        response->setSucceed(true);
    }
}
    
void HttpClient::clearResponseAndRequestQueue()
{
    _requestQueueMutex.lock();
    __clearQueue(_requestQueue, _clearRequestPredicate);
    _requestQueueMutex.unlock();
    
    _responseQueueMutex.lock();
    __clearQueue(_responseQueue, _clearResponsePredicate);
    _responseQueueMutex.unlock();
}

void HttpClient::increaseThreadCount()
{
    _threadCountMutex.lock();
    ++_threadCount;
    _threadCountMutex.unlock();
}

void HttpClient::decreaseThreadCountAndMayDeleteThis()
{
    bool needDeleteThis = false;
    _threadCountMutex.lock();
    --_threadCount;
    if (0 == _threadCount)
    {
        needDeleteThis = true;
    }

    _threadCountMutex.unlock();
    if (needDeleteThis)
    {
        delete this;
    }
}

void HttpClient::setTimeoutForConnect(int value)
{
    std::lock_guard<std::recursive_mutex> lock(_timeoutForConnectMutex);
    _timeoutForConnect = value;
}
    
int HttpClient::getTimeoutForConnect()
{
    std::lock_guard<std::recursive_mutex> lock(_timeoutForConnectMutex);
    return _timeoutForConnect;
}
    
void HttpClient::setTimeoutForRead(int value)
{
    std::lock_guard<std::recursive_mutex> lock(_timeoutForReadMutex);
    _timeoutForRead = value;
}
    
int HttpClient::getTimeoutForRead()
{
    std::lock_guard<std::recursive_mutex> lock(_timeoutForReadMutex);
    return _timeoutForRead;
}
    
const std::string& HttpClient::getCookieFilename()
{
    std::lock_guard<std::recursive_mutex> lock(_cookieFileMutex);
    return _cookieFilename;
}
    
const std::string& HttpClient::getSSLVerification()
{
    std::lock_guard<std::recursive_mutex> lock(_sslCaFileMutex);
    return _sslCaFilename;
}

}

NS_CC_END


