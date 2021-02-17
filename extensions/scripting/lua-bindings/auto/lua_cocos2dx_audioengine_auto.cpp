#include "scripting/lua-bindings/auto/lua_cocos2dx_audioengine_auto.hpp"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
#include "audio/include/AudioEngine.h"
void lua_register_cocos2dx_audioengine_AudioProfile(cocos2d::Lua& lua){
auto mt=cocos2d::Lua::NewUserType<cocos2d::AudioProfile>(lua.get_or("cc",lua.create_named_table("cc")),"AudioProfile");
}
void lua_register_cocos2dx_audioengine_AudioEngine(cocos2d::Lua& lua){
auto mt=cocos2d::Lua::NewUserType<cocos2d::AudioEngine>(lua.get_or("cc",lua.create_named_table("cc")),"AudioEngine");
mt["lazyInit"]=static_cast<bool(*)()>(&cocos2d::AudioEngine::lazyInit);
mt["end"]=static_cast<void(*)()>(&cocos2d::AudioEngine::end);
mt["getDefaultProfile"]=static_cast<cocos2d::AudioProfile*(*)()>(&cocos2d::AudioEngine::getDefaultProfile);
mt["play2d"]=sol::overload([](cocos2d::AudioEngine* obj,const std::string& arg0){return obj->play2d(arg0);},[](cocos2d::AudioEngine* obj,const std::string& arg0,bool arg1){return obj->play2d(arg0,arg1);},[](cocos2d::AudioEngine* obj,const std::string& arg0,bool arg1,float arg2){return obj->play2d(arg0,arg1,arg2);},[](cocos2d::AudioEngine* obj,const std::string& arg0,bool arg1,float arg2,const cocos2d::AudioProfile* arg3){return obj->play2d(arg0,arg1,arg2,arg3);});
mt["setLoop"]=static_cast<void(*)(int,bool)>(&cocos2d::AudioEngine::setLoop);
mt["isLoop"]=static_cast<bool(*)(int)>(&cocos2d::AudioEngine::isLoop);
mt["setVolume"]=static_cast<void(*)(int,float)>(&cocos2d::AudioEngine::setVolume);
mt["getVolume"]=static_cast<float(*)(int)>(&cocos2d::AudioEngine::getVolume);
mt["pause"]=static_cast<void(*)(int)>(&cocos2d::AudioEngine::pause);
mt["pauseAll"]=static_cast<void(*)()>(&cocos2d::AudioEngine::pauseAll);
mt["resume"]=static_cast<void(*)(int)>(&cocos2d::AudioEngine::resume);
mt["resumeAll"]=static_cast<void(*)()>(&cocos2d::AudioEngine::resumeAll);
mt["stop"]=static_cast<void(*)(int)>(&cocos2d::AudioEngine::stop);
mt["stopAll"]=static_cast<void(*)()>(&cocos2d::AudioEngine::stopAll);
mt["setCurrentTime"]=static_cast<bool(*)(int,float)>(&cocos2d::AudioEngine::setCurrentTime);
mt["getCurrentTime"]=static_cast<float(*)(int)>(&cocos2d::AudioEngine::getCurrentTime);
mt["getDuration"]=static_cast<float(*)(int)>(&cocos2d::AudioEngine::getDuration);
mt["getState"]=static_cast<cocos2d::AudioEngine::AudioState(*)(int)>(&cocos2d::AudioEngine::getState);
mt["getMaxAudioInstance"]=static_cast<int(*)()>(&cocos2d::AudioEngine::getMaxAudioInstance);
mt["setMaxAudioInstance"]=static_cast<bool(*)(int)>(&cocos2d::AudioEngine::setMaxAudioInstance);
mt["uncache"]=static_cast<void(*)(const std::string&)>(&cocos2d::AudioEngine::uncache);
mt["uncacheAll"]=static_cast<void(*)()>(&cocos2d::AudioEngine::uncacheAll);
mt["getProfile"]=static_cast<cocos2d::AudioProfile*(*)(const std::string&)>(&cocos2d::AudioEngine::getProfile),static_cast<cocos2d::AudioProfile*(*)(int)>(&cocos2d::AudioEngine::getProfile);
mt["getPlayingAudioCount"]=static_cast<int(*)()>(&cocos2d::AudioEngine::getPlayingAudioCount);
mt["setEnabled"]=static_cast<void(*)(bool)>(&cocos2d::AudioEngine::setEnabled);
mt["isEnabled"]=static_cast<bool(*)()>(&cocos2d::AudioEngine::isEnabled);
}
void register_all_cocos2dx_audioengine(cocos2d::Lua& lua) {
	lua_register_cocos2dx_audioengine_AudioProfile(lua);
	lua_register_cocos2dx_audioengine_AudioEngine(lua);
}
#endif
