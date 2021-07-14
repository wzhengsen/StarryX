#include "scripting/lua-bindings/auto/CCRegisterLuaCoreAuto.hpp"
#include "cocos2d.h"
#include "2d/CCProtectedNode.h"
#include "base/CCAsyncTaskPool.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCPipelineDescriptor.h"
#include "renderer/backend/RenderTarget.h"
#include "navmesh/CCNavMesh.h"
#include "ui/UIWidget.h"
#include "base/TGAlib.h"
namespace cocos2d{
void RegisterLuaCoreFastTMXTiledMapAuto(cocos2d::extension::Lua& lua){
cocos2d::extension::Lua::Id2Meta[typeid(cocos2d::FastTMXTiledMap).name()] = sol::usertype_traits<cocos2d::FastTMXTiledMap*>::metatable();
auto dep=lua.new_usertype<cocos2d::FastTMXTiledMap>("deprecated.cocos2d::FastTMXTiledMap");
dep[sol::base_classes]=sol::bases<cocos2d::Node,cocos2d::Ref,cocos2d::extension::LuaObject>();
sol::table mt=lua.NewClass(sol::usertype_traits<cocos2d::FastTMXTiledMap*>::metatable(),sol::usertype_traits<cocos2d::Node*>::metatable());
lua["cc"]["FastTMXTiledMap"]=mt;
mt["__new__"]=static_cast<cocos2d::FastTMXTiledMap*(*)(const std::string&)>(&cocos2d::FastTMXTiledMap::create);
mt["static"]["CreateWithXML"]=static_cast<cocos2d::FastTMXTiledMap*(*)(const std::string&,const std::string&)>(&cocos2d::FastTMXTiledMap::createWithXML);
mt["GetLayer"]=static_cast<cocos2d::FastTMXLayer*(cocos2d::FastTMXTiledMap::*)(const std::string&)const>(&cocos2d::FastTMXTiledMap::getLayer);
mt["GetObjectGroup"]=static_cast<cocos2d::TMXObjectGroup*(cocos2d::FastTMXTiledMap::*)(const std::string&)const>(&cocos2d::FastTMXTiledMap::getObjectGroup);
mt["GetProperty"]=static_cast<cocos2d::Value(cocos2d::FastTMXTiledMap::*)(const std::string&)const>(&cocos2d::FastTMXTiledMap::getProperty);
mt["GetPropertiesForGID"]=static_cast<cocos2d::Value(cocos2d::FastTMXTiledMap::*)(int)const>(&cocos2d::FastTMXTiledMap::getPropertiesForGID);
mt["GetMapSize"]=static_cast<const cocos2d::Size&(cocos2d::FastTMXTiledMap::*)()const>(&cocos2d::FastTMXTiledMap::getMapSize);
mt["get"]["MapSize"]=mt["GetMapSize"];
mt["SetMapSize"]=static_cast<void(cocos2d::FastTMXTiledMap::*)(const cocos2d::Size&)>(&cocos2d::FastTMXTiledMap::setMapSize);
mt["set"]["MapSize"]=mt["SetMapSize"];
mt["GetTileSize"]=static_cast<const cocos2d::Size&(cocos2d::FastTMXTiledMap::*)()const>(&cocos2d::FastTMXTiledMap::getTileSize);
mt["get"]["TileSize"]=mt["GetTileSize"];
mt["SetTileSize"]=static_cast<void(cocos2d::FastTMXTiledMap::*)(const cocos2d::Size&)>(&cocos2d::FastTMXTiledMap::setTileSize);
mt["set"]["TileSize"]=mt["SetTileSize"];
mt["GetMapOrientation"]=static_cast<int(cocos2d::FastTMXTiledMap::*)()const>(&cocos2d::FastTMXTiledMap::getMapOrientation);
mt["get"]["MapOrientation"]=mt["GetMapOrientation"];
mt["SetMapOrientation"]=static_cast<void(cocos2d::FastTMXTiledMap::*)(int)>(&cocos2d::FastTMXTiledMap::setMapOrientation);
mt["set"]["MapOrientation"]=mt["SetMapOrientation"];
mt["GetObjectGroups"]=static_cast<const cocos2d::Vector<cocos2d::TMXObjectGroup *>&(cocos2d::FastTMXTiledMap::*)()const>(&cocos2d::FastTMXTiledMap::getObjectGroups);
mt["get"]["ObjectGroups"]=mt["GetObjectGroups"];
mt["SetObjectGroups"]=static_cast<void(cocos2d::FastTMXTiledMap::*)(const cocos2d::Vector<cocos2d::TMXObjectGroup *>&)>(&cocos2d::FastTMXTiledMap::setObjectGroups);
mt["set"]["ObjectGroups"]=mt["SetObjectGroups"];
mt["GetProperties"]=static_cast<const cocos2d::ValueMap&(cocos2d::FastTMXTiledMap::*)()const>(&cocos2d::FastTMXTiledMap::getProperties);
mt["get"]["Properties"]=mt["GetProperties"];
mt["SetProperties"]=static_cast<void(cocos2d::FastTMXTiledMap::*)(const cocos2d::ValueMap&)>(&cocos2d::FastTMXTiledMap::setProperties);
mt["set"]["Properties"]=mt["SetProperties"];
mt["SetTileAnimEnabled"]=static_cast<void(cocos2d::FastTMXTiledMap::*)(bool)>(&cocos2d::FastTMXTiledMap::setTileAnimEnabled);
mt["set"]["TileAnimEnabled"]=mt["SetTileAnimEnabled"];
mt["GetLayerCount"]=static_cast<int(cocos2d::FastTMXTiledMap::*)()const>(&cocos2d::FastTMXTiledMap::getLayerCount);
mt["get"]["LayerCount"]=mt["GetLayerCount"];
mt["GetResourceFile"]=static_cast<const std::string&(cocos2d::FastTMXTiledMap::*)()const>(&cocos2d::FastTMXTiledMap::getResourceFile);
mt["get"]["ResourceFile"]=mt["GetResourceFile"];
}
void RegisterLuaCoreCryptoEncodeModeAuto(cocos2d::extension::Lua& lua) {
sol::table enumTable = lua.create_table_with(0,3);
enumTable["BASE64"]=cocos2d::Crypto::EncodeMode::BASE64;
enumTable["HEX"]=cocos2d::Crypto::EncodeMode::HEX;
enumTable["URL"]=cocos2d::Crypto::EncodeMode::URL;
lua["cc"]["Crypto"]["static"]["EncodeMode"]=lua.NewEnum(enumTable);
}
void RegisterLuaCoreCryptoHashModeAuto(cocos2d::extension::Lua& lua) {
sol::table enumTable = lua.create_table_with(0,6);
enumTable["SHA1"]=cocos2d::Crypto::HashMode::SHA1;
enumTable["SHA224"]=cocos2d::Crypto::HashMode::SHA224;
enumTable["SHA256"]=cocos2d::Crypto::HashMode::SHA256;
enumTable["SHA384"]=cocos2d::Crypto::HashMode::SHA384;
enumTable["SHA512"]=cocos2d::Crypto::HashMode::SHA512;
enumTable["MD5"]=cocos2d::Crypto::HashMode::MD5;
lua["cc"]["Crypto"]["static"]["HashMode"]=lua.NewEnum(enumTable);
}
void RegisterLuaCoreCryptoAuto(cocos2d::extension::Lua& lua){
cocos2d::extension::Lua::Id2Meta[typeid(cocos2d::Crypto).name()] = sol::usertype_traits<cocos2d::Crypto*>::metatable();
auto dep=lua.new_usertype<cocos2d::Crypto>("deprecated.cocos2d::Crypto");
sol::table mt=lua.NewClass(sol::usertype_traits<cocos2d::Crypto*>::metatable());
lua["cc"]["Crypto"]=mt;
mt["__new__"] = [](){return nullptr;};
mt["static"]["Encode"]=static_cast<std::string(*)(const std::string&,cocos2d::Crypto::EncodeMode)>(&cocos2d::Crypto::Encode);
mt["static"]["Decode"]=static_cast<std::string(*)(const std::string&,cocos2d::Crypto::DecodeMode)>(&cocos2d::Crypto::Decode);
mt["static"]["Hash"]=sol::overload([](const std::string& arg0,cocos2d::Crypto::HashMode arg1,bool arg2){return cocos2d::Crypto::Hash(arg0,arg1,arg2);},[](const std::string& arg0,cocos2d::Crypto::HashMode arg1){return cocos2d::Crypto::Hash(arg0,arg1);});
mt["static"]["SHA1"]=static_cast<std::string(*)(const std::string&)>(&cocos2d::Crypto::SHA1);
mt["static"]["SHA224"]=static_cast<std::string(*)(const std::string&)>(&cocos2d::Crypto::SHA224);
mt["static"]["SHA256"]=static_cast<std::string(*)(const std::string&)>(&cocos2d::Crypto::SHA256);
mt["static"]["SHA384"]=static_cast<std::string(*)(const std::string&)>(&cocos2d::Crypto::SHA384);
mt["static"]["SHA512"]=static_cast<std::string(*)(const std::string&)>(&cocos2d::Crypto::SHA512);
mt["static"]["MD5"]=static_cast<std::string(*)(const std::string&)>(&cocos2d::Crypto::MD5);
mt["static"]["Encrypt"]=sol::overload([](const std::string& arg0,const std::string& arg1,const std::string& arg2){return cocos2d::Crypto::Encrypt(arg0,arg1,arg2);},[](const std::string& arg0,const std::string& arg1){return cocos2d::Crypto::Encrypt(arg0,arg1);});
mt["static"]["Decrypt"]=sol::overload([](const std::string& arg0,const std::string& arg1,const std::string& arg2){return cocos2d::Crypto::Decrypt(arg0,arg1,arg2);},[](const std::string& arg0,const std::string& arg1){return cocos2d::Crypto::Decrypt(arg0,arg1);});
mt["static"]["CFB128"]=static_cast<void(*)(const void*,size_t,void*,size_t,const char*,uint8_t,const char*,uint8_t,bool)>(&cocos2d::Crypto::CFB128);
RegisterLuaCoreCryptoEncodeModeAuto(lua);
RegisterLuaCoreCryptoHashModeAuto(lua);
}
void RegisterLuaCoreConnectionKindAuto(cocos2d::extension::Lua& lua) {
sol::table enumTable = lua.create_table_with(0,3);
enumTable["TCP"]=cocos2d::network::Connection::Kind::TCP;
enumTable["UDP"]=cocos2d::network::Connection::Kind::UDP;
enumTable["KCP"]=cocos2d::network::Connection::Kind::KCP;
lua["cc"]["Connection"]["static"]["Kind"]=lua.NewEnum(enumTable);
}
void RegisterLuaCoreConnectionAuto(cocos2d::extension::Lua& lua){
cocos2d::extension::Lua::Id2Meta[typeid(cocos2d::network::Connection).name()] = sol::usertype_traits<cocos2d::network::Connection*>::metatable();
auto dep=lua.new_usertype<cocos2d::network::Connection>("deprecated.cocos2d::network::Connection");
dep[sol::base_classes]=sol::bases<cocos2d::extension::LuaObject>();
sol::table mt=lua.NewClass(sol::usertype_traits<cocos2d::network::Connection*>::metatable(),sol::usertype_traits<cocos2d::extension::LuaObject*>::metatable());
lua["cc"]["Connection"]=mt;
mt["__new__"] = [](){return nullptr;};
mt["Open"]=static_cast<void(cocos2d::network::Connection::*)()>(&cocos2d::network::Connection::Open);
mt["Close"]=static_cast<void(cocos2d::network::Connection::*)()>(&cocos2d::network::Connection::Close);
mt["Write"]=static_cast<int(cocos2d::network::Connection::*)(const std::string&)>(&cocos2d::network::Connection::Write);
mt["SetHeartBeat"]=sol::overload([](cocos2d::network::Connection* obj,size_t arg0,size_t arg1){return obj->SetHeartBeat(arg0,arg1);},[](cocos2d::network::Connection* obj,size_t arg0){return obj->SetHeartBeat(arg0);},[](cocos2d::network::Connection* obj){return obj->SetHeartBeat();});
mt["set"]["HeartBeat"]=mt["SetHeartBeat"];
RegisterLuaCoreConnectionKindAuto(lua);
}
void RegisterLuaCoreServerAuto(cocos2d::extension::Lua& lua){
cocos2d::extension::Lua::Id2Meta[typeid(cocos2d::network::Server).name()] = sol::usertype_traits<cocos2d::network::Server*>::metatable();
auto dep=lua.new_usertype<cocos2d::network::Server>("deprecated.cocos2d::network::Server");
dep[sol::base_classes]=sol::bases<cocos2d::network::Connection,cocos2d::extension::LuaObject>();
sol::table mt=lua.NewClass(sol::usertype_traits<cocos2d::network::Server*>::metatable(),sol::usertype_traits<cocos2d::network::Connection*>::metatable());
lua["cc"]["Server"]=mt;
mt["__new__"]=sol::overload([](const std::string_view& arg0,uint16_t arg1,cocos2d::network::Connection::Kind arg2){return new cocos2d::network::Server(arg0,arg1,arg2);},[](uint16_t arg0,cocos2d::network::Connection::Kind arg1){return new cocos2d::network::Server(arg0,arg1);},[](const std::string_view& arg0,uint16_t arg1){return new cocos2d::network::Server(arg0,arg1);},[](uint16_t arg0){return new cocos2d::network::Server(arg0);});
mt["SetConnectHandler"]=static_cast<void(cocos2d::network::Server::*)(const cocos2d::network::Server::SC_Handler&)>(&cocos2d::network::Server::SetConnectHandler);
mt["set"]["ConnectHandler"]=mt["SetConnectHandler"];
mt["SetMessageHandler"]=static_cast<void(cocos2d::network::Server::*)(const cocos2d::network::Server::SM_Handler&)>(&cocos2d::network::Server::SetMessageHandler);
mt["set"]["MessageHandler"]=mt["SetMessageHandler"];
mt["SetLoseHandler"]=static_cast<void(cocos2d::network::Server::*)(const cocos2d::network::Server::SL_Handler&)>(&cocos2d::network::Server::SetLoseHandler);
mt["set"]["LoseHandler"]=mt["SetLoseHandler"];
mt["Write"]=sol::overload(static_cast<int(cocos2d::network::Server::*)(yasio::inet::transport_handle_t,const std::string&)>(&cocos2d::network::Server::Write),static_cast<int(cocos2d::network::Server::*)(const std::string&)>(&cocos2d::network::Server::Write));
mt["Close"]=static_cast<void(cocos2d::network::Server::*)(yasio::inet::transport_handle_t)>(&cocos2d::network::Server::Close);
}
void RegisterLuaCoreClientAuto(cocos2d::extension::Lua& lua){
cocos2d::extension::Lua::Id2Meta[typeid(cocos2d::network::Client).name()] = sol::usertype_traits<cocos2d::network::Client*>::metatable();
auto dep=lua.new_usertype<cocos2d::network::Client>("deprecated.cocos2d::network::Client");
dep[sol::base_classes]=sol::bases<cocos2d::network::Connection,cocos2d::extension::LuaObject>();
sol::table mt=lua.NewClass(sol::usertype_traits<cocos2d::network::Client*>::metatable(),sol::usertype_traits<cocos2d::network::Connection*>::metatable());
lua["cc"]["Client"]=mt;
mt["__new__"]=sol::overload([](const std::string_view& arg0,uint16_t arg1,cocos2d::network::Connection::Kind arg2){return new cocos2d::network::Client(arg0,arg1,arg2);},[](const std::string_view& arg0,uint16_t arg1){return new cocos2d::network::Client(arg0,arg1);});
mt["SetConnectHandler"]=static_cast<void(cocos2d::network::Client::*)(const cocos2d::network::Client::CC_Handler&)>(&cocos2d::network::Client::SetConnectHandler);
mt["set"]["ConnectHandler"]=mt["SetConnectHandler"];
mt["SetMessageHandler"]=static_cast<void(cocos2d::network::Client::*)(const cocos2d::network::Client::CM_Handler&)>(&cocos2d::network::Client::SetMessageHandler);
mt["set"]["MessageHandler"]=mt["SetMessageHandler"];
mt["SetLoseHandler"]=static_cast<void(cocos2d::network::Client::*)(const cocos2d::network::Client::CL_Handler&)>(&cocos2d::network::Client::SetLoseHandler);
mt["set"]["LoseHandler"]=mt["SetLoseHandler"];
mt["Open"]=sol::overload(static_cast<void(cocos2d::network::Client::*)(size_t)>(&cocos2d::network::Client::Open),static_cast<void(cocos2d::network::Client::*)()>(&cocos2d::network::Client::Open));
}
void RegisterLuaCoreDownloadTaskAuto(cocos2d::extension::Lua& lua){
cocos2d::extension::Lua::Id2Meta[typeid(cocos2d::network::DownloadTask).name()] = sol::usertype_traits<cocos2d::network::DownloadTask*>::metatable();
auto dep=lua.new_usertype<cocos2d::network::DownloadTask>("deprecated.cocos2d::network::DownloadTask");
dep[sol::base_classes]=sol::bases<cocos2d::extension::LuaObject>();
sol::table mt=lua.NewClass(sol::usertype_traits<cocos2d::network::DownloadTask*>::metatable(),sol::usertype_traits<cocos2d::extension::LuaObject*>::metatable());
lua["cc"]["DownloadTask"]=mt;
mt["__new__"]=sol::overload([](const std::string& arg0,const std::string& arg1,const std::string& arg2,const std::string& arg3,bool arg4){return new cocos2d::network::DownloadTask(arg0,arg1,arg2,arg3,arg4);},[](const std::string& arg0,const std::string& arg1){return new cocos2d::network::DownloadTask(arg0,arg1);},[](){return new cocos2d::network::DownloadTask();});
mt["Cancel"]=static_cast<void(cocos2d::network::DownloadTask::*)()>(&cocos2d::network::DownloadTask::cancel);
mt["static"]["get"]["ERROR_NO_ERROR"]=[]()->const int&{return cocos2d::network::DownloadTask::ERROR_NO_ERROR;};
mt["static"]["get"]["ERROR_INVALID_PARAMS"]=[]()->const int&{return cocos2d::network::DownloadTask::ERROR_INVALID_PARAMS;};
mt["static"]["get"]["ERROR_OPEN_FILE_FAILED"]=[]()->const int&{return cocos2d::network::DownloadTask::ERROR_OPEN_FILE_FAILED;};
mt["static"]["get"]["ERROR_IMPL_INTERNAL"]=[]()->const int&{return cocos2d::network::DownloadTask::ERROR_IMPL_INTERNAL;};
mt["static"]["get"]["ERROR_TASK_DUPLICATED"]=[]()->const int&{return cocos2d::network::DownloadTask::ERROR_TASK_DUPLICATED;};
mt["static"]["get"]["ERROR_CREATE_DIR_FAILED"]=[]()->const int&{return cocos2d::network::DownloadTask::ERROR_CREATE_DIR_FAILED;};
mt["static"]["get"]["ERROR_REMOVE_FILE_FAILED"]=[]()->const int&{return cocos2d::network::DownloadTask::ERROR_REMOVE_FILE_FAILED;};
mt["static"]["get"]["ERROR_RENAME_FILE_FAILED"]=[]()->const int&{return cocos2d::network::DownloadTask::ERROR_RENAME_FILE_FAILED;};
mt["static"]["get"]["ERROR_CHECK_SUM_FAILED"]=[]()->const int&{return cocos2d::network::DownloadTask::ERROR_CHECK_SUM_FAILED;};
mt["static"]["get"]["ERROR_ORIGIN_FILE_MISSING"]=[]()->const int&{return cocos2d::network::DownloadTask::ERROR_ORIGIN_FILE_MISSING;};
mt["set"]["Identifier"]=[](cocos2d::network::DownloadTask* obj,const std::string& value){obj->identifier = value;};
mt["get"]["Identifier"]=[](cocos2d::network::DownloadTask* obj)->const std::string&{return obj->identifier;};
mt["set"]["RequestURL"]=[](cocos2d::network::DownloadTask* obj,const std::string& value){obj->requestURL = value;};
mt["get"]["RequestURL"]=[](cocos2d::network::DownloadTask* obj)->const std::string&{return obj->requestURL;};
mt["set"]["StoragePath"]=[](cocos2d::network::DownloadTask* obj,const std::string& value){obj->storagePath = value;};
mt["get"]["StoragePath"]=[](cocos2d::network::DownloadTask* obj)->const std::string&{return obj->storagePath;};
mt["set"]["ProgressInfo"]=[](cocos2d::network::DownloadTask* obj,const cocos2d::network::DownloadTask::ProgressInfo& value){obj->progressInfo = value;};
mt["get"]["ProgressInfo"]=[](cocos2d::network::DownloadTask* obj)->const cocos2d::network::DownloadTask::ProgressInfo&{return obj->progressInfo;};
mt["set"]["Checksum"]=[](cocos2d::network::DownloadTask* obj,const std::string& value){obj->checksum = value;};
mt["get"]["Checksum"]=[](cocos2d::network::DownloadTask* obj)->const std::string&{return obj->checksum;};
mt["set"]["Background"]=[](cocos2d::network::DownloadTask* obj,const bool& value){obj->background = value;};
mt["get"]["Background"]=[](cocos2d::network::DownloadTask* obj)->const bool&{return obj->background;};
}
void RegisterLuaCoreDownloaderAuto(cocos2d::extension::Lua& lua){
cocos2d::extension::Lua::Id2Meta[typeid(cocos2d::network::Downloader).name()] = sol::usertype_traits<cocos2d::network::Downloader*>::metatable();
auto dep=lua.new_usertype<cocos2d::network::Downloader>("deprecated.cocos2d::network::Downloader");
dep[sol::base_classes]=sol::bases<cocos2d::extension::LuaObject>();
sol::table mt=lua.NewClass(sol::usertype_traits<cocos2d::network::Downloader*>::metatable(),sol::usertype_traits<cocos2d::extension::LuaObject*>::metatable());
lua["cc"]["Downloader"]=mt;
mt["__new__"]=sol::overload([](const cocos2d::network::DownloaderHints& arg0){return new cocos2d::network::Downloader(arg0);},[](){return new cocos2d::network::Downloader();});
mt["DownloadData"]=sol::overload([](cocos2d::network::Downloader* obj,const std::string& arg0,const std::string& arg1){return obj->createDownloadDataTask(arg0,arg1);},[](cocos2d::network::Downloader* obj,const std::string& arg0){return obj->createDownloadDataTask(arg0);});
mt["DownloadFile"]=sol::overload([](cocos2d::network::Downloader* obj,const std::string& arg0,const std::string& arg1,const std::string& arg2,const std::string& arg3,bool arg4){return obj->createDownloadFileTask(arg0,arg1,arg2,arg3,arg4);},[](cocos2d::network::Downloader* obj,const std::string& arg0,const std::string& arg1,const std::string& arg2,const std::string& arg3){return obj->createDownloadFileTask(arg0,arg1,arg2,arg3);},[](cocos2d::network::Downloader* obj,const std::string& arg0,const std::string& arg1,const std::string& arg2){return obj->createDownloadFileTask(arg0,arg1,arg2);},[](cocos2d::network::Downloader* obj,const std::string& arg0,const std::string& arg1){return obj->createDownloadFileTask(arg0,arg1);});
mt["set"]["OnDataTaskSuccess"]=[](cocos2d::network::Downloader* obj,const std::function<void (const cocos2d::network::DownloadTask *, std::vector<unsigned char, std::allocator<unsigned char> > &)>& value){obj->onDataTaskSuccess = value;};
mt["get"]["OnDataTaskSuccess"]=[](cocos2d::network::Downloader* obj)->const std::function<void (const cocos2d::network::DownloadTask *, std::vector<unsigned char, std::allocator<unsigned char> > &)>&{return obj->onDataTaskSuccess;};
mt["set"]["OnFileTaskSuccess"]=[](cocos2d::network::Downloader* obj,const std::function<void (const cocos2d::network::DownloadTask *)>& value){obj->onFileTaskSuccess = value;};
mt["get"]["OnFileTaskSuccess"]=[](cocos2d::network::Downloader* obj)->const std::function<void (const cocos2d::network::DownloadTask *)>&{return obj->onFileTaskSuccess;};
mt["set"]["OnTaskProgress"]=[](cocos2d::network::Downloader* obj,const std::function<void (const cocos2d::network::DownloadTask *)>& value){obj->onTaskProgress = value;};
mt["get"]["OnTaskProgress"]=[](cocos2d::network::Downloader* obj)->const std::function<void (const cocos2d::network::DownloadTask *)>&{return obj->onTaskProgress;};
mt["set"]["OnTaskError"]=[](cocos2d::network::Downloader* obj,const std::function<void (const cocos2d::network::DownloadTask *, int, int, const std::basic_string<char, std::char_traits<char>, std::allocator<char> > &)>& value){obj->onTaskError = value;};
mt["get"]["OnTaskError"]=[](cocos2d::network::Downloader* obj)->const std::function<void (const cocos2d::network::DownloadTask *, int, int, const std::basic_string<char, std::char_traits<char>, std::allocator<char> > &)>&{return obj->onTaskError;};
}
}
