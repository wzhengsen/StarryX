#include "scripting/lua-bindings/auto/CCRegisterLuaCSLoaderAuto.hpp"
#include "cocostudio/ActionTimeline/CSLoader.h"
extern void RegisterLuaCSLoaderCSLoaderAuto(cocos2d::Lua&);
void RegisterLuaCSLoaderAuto(cocos2d::Lua& lua){
RegisterLuaCSLoaderCSLoaderAuto(lua);
}