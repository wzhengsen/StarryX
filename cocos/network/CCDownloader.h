/****************************************************************************
 Copyright (c) 2015-2016 cocos2d-x.org
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

#pragma once

#include <functional>
#include <string>
#include <memory>
#include <vector>

#include "platform/CCPlatformMacros.h"

namespace cocos2d { namespace network {

    class IDownloadTask;
    class IDownloaderImpl;
    class Downloader;

    class CC_DLL DownloadTask final
    {
    public:
        const static int ERROR_NO_ERROR = 0;
        const static int ERROR_INVALID_PARAMS = -1;
        const static int ERROR_OPEN_FILE_FAILED = -2;
        const static int ERROR_IMPL_INTERNAL = -3;
        const static int ERROR_TASK_DUPLICATED = -4;
        const static int ERROR_CREATE_DIR_FAILED = -5;
        const static int ERROR_REMOVE_FILE_FAILED = -6;
        const static int ERROR_RENAME_FILE_FAILED = -7;
        const static int ERROR_CHECK_SUM_FAILED = -8;
		const static int ERROR_ORIGIN_FILE_MISSING = -9;

        std::string identifier;
        std::string requestURL;
        std::string storagePath;

        struct {
            // progress
            int64_t  totalBytesExpected = 0;
            int64_t  bytesReceived = 0;
            int64_t  totalBytesReceived = 0;
            // speed
            double   speedInBytes = 0;
        } mutable progressInfo;

        DownloadTask();
        DownloadTask(const std::string& srcUrl, const std::string& identifier);
        DownloadTask(const std::string& srcUrl,
            const std::string& storagePath,
            const std::string& checksum, // currently is MD5
            const std::string& identifier);

        virtual ~DownloadTask();
        
        // Cancel the download, it's useful for ios platform switch wifi to 4g
        void cancel();

		std::string checksum; // The MD5 checksum for check only when download finished.
		
    private:
        friend class Downloader;
        std::unique_ptr<IDownloadTask> _coTask;
    };

    class CC_DLL DownloaderHints
    {
    public:
        uint32_t countOfMaxProcessingTasks = 6;
        uint32_t timeoutInMS = 45000;
        std::string tempFileNameSuffix = ".temp";
    };

    class CC_DLL Downloader final
    {
    public:
        Downloader();
        Downloader(const DownloaderHints& hints);
        ~Downloader();

        std::function<void(const DownloadTask& task,
                           std::vector<unsigned char>& data)> onDataTaskSuccess;

        std::function<void(const DownloadTask& task)> onFileTaskSuccess;

        std::function<void(const DownloadTask& task)> onTaskProgress;

        std::function<void(const DownloadTask& task,
                           int errorCode,
                           int errorCodeInternal,
                           const std::string& errorStr)> onTaskError;
        
        void setOnFileTaskSuccess(const std::function<void(const DownloadTask& task)>& callback) {onFileTaskSuccess = callback;};
        
        void setOnTaskProgress(const std::function<void(const DownloadTask& task)>& callback) {onTaskProgress = callback;};
        
        void setOnTaskError(const std::function<void(const DownloadTask& task,
                                               int errorCode,
                                               int errorCodeInternal,
                                               const std::string& errorStr)>& callback) {onTaskError = callback;};

        std::shared_ptr<DownloadTask> createDownloadDataTask(const std::string& srcUrl, const std::string& identifier = "");

        std::shared_ptr<DownloadTask> createDownloadFileTask(
            const std::string& srcUrl, const std::string& storagePath, const std::string& identifier = "", const std::string& checksum = "");

    private:
        std::unique_ptr<IDownloaderImpl> _impl;
    };

}}  // namespace cocos2d::network

