#include "scripting/lua-bindings/auto/CCRegisterLuaUtilsAuto.hpp"
#include "base/ccUtils.h"
namespace cocos2d{
void RegisterLuaUtilsgettimeAuto(cocos2d::extension::Lua& lua) {
sol::table pTable = lua["ccu"];
pTable["GetTime"] = static_cast<double(*)()>(&cocos2d::utils::gettime);
}

void RegisterLuaUtilsgetTimeInMillisecondsAuto(cocos2d::extension::Lua& lua) {
sol::table pTable = lua["ccu"];
pTable["GetTimeInMilliseconds"] = static_cast<long long(*)()>(&cocos2d::utils::getTimeInMilliseconds);
}

void RegisterLuaUtilsgetCascadeBoundingBoxAuto(cocos2d::extension::Lua& lua) {
sol::table pTable = lua["ccu"];
pTable["GetCascadeBoundingBox"] = static_cast<cocos2d::Rect(*)(cocos2d::Node*)>(&cocos2d::utils::getCascadeBoundingBox);
}

void RegisterLuaUtilscreateSpriteFromBase64CachedAuto(cocos2d::extension::Lua& lua) {
sol::table pTable = lua["ccu"];
pTable["CreateSpriteFromBase64Cached"] = static_cast<cocos2d::Sprite*(*)(const char*,const char*)>(&cocos2d::utils::createSpriteFromBase64Cached);
}

void RegisterLuaUtilscreateSpriteFromBase64Auto(cocos2d::extension::Lua& lua) {
sol::table pTable = lua["ccu"];
pTable["CreateSpriteFromBase64"] = static_cast<cocos2d::Sprite*(*)(const char*)>(&cocos2d::utils::createSpriteFromBase64);
}

void RegisterLuaUtilsgetFileMD5HashAuto(cocos2d::extension::Lua& lua) {
sol::table pTable = lua["ccu"];
pTable["GetFileMD5Hash"] = static_cast<std::string(*)(const std::string&)>(&cocos2d::utils::getFileMD5Hash);
}

void RegisterLuaUtilsgetDataMD5HashAuto(cocos2d::extension::Lua& lua) {
sol::table pTable = lua["ccu"];
pTable["GetDataMD5Hash"] = static_cast<std::string(*)(const cocos2d::Data&)>(&cocos2d::utils::getDataMD5Hash);
}

void RegisterLuaUtilsgetLanguageTypeByISO2Auto(cocos2d::extension::Lua& lua) {
sol::table pTable = lua["ccu"];
pTable["GetLanguageTypeByISO2"] = static_cast<cocos2d::LanguageType(*)(const char*)>(&cocos2d::utils::getLanguageTypeByISO2);
}

void RegisterLuaUtilstoBackendBlendFactorAuto(cocos2d::extension::Lua& lua) {
sol::table pTable = lua["ccu"];
pTable["ToBackendBlendFactor"] = static_cast<cocos2d::backend::BlendFactor(*)(int)>(&cocos2d::utils::toBackendBlendFactor);
}

void RegisterLuaUtilstoGLBlendFactorAuto(cocos2d::extension::Lua& lua) {
sol::table pTable = lua["ccu"];
pTable["ToGLBlendFactor"] = static_cast<int(*)(cocos2d::backend::BlendFactor)>(&cocos2d::utils::toGLBlendFactor);
}

}