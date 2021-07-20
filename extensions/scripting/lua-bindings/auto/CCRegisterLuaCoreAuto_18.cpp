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
void RegisterLuaCoreMenuItemToggleAuto(cocos2d::extension::Lua& lua){
cocos2d::extension::Lua::Id2Meta[typeid(cocos2d::MenuItemToggle).name()] = sol::usertype_traits<cocos2d::MenuItemToggle*>::metatable();
auto dep=lua.new_usertype<cocos2d::MenuItemToggle>("deprecated.cocos2d::MenuItemToggle");
dep[sol::base_classes]=sol::bases<cocos2d::MenuItem,cocos2d::Node,cocos2d::Ref,cocos2d::extension::LuaObject>();
sol::table mt=lua.NewClass(sol::usertype_traits<cocos2d::MenuItemToggle*>::metatable(),sol::usertype_traits<cocos2d::MenuItem*>::metatable());
lua["cc"]["MenuItemToggle"]=mt;
mt["__new__"] = [](){return nullptr;};
mt["AddSubItem"]=static_cast<void(cocos2d::MenuItemToggle::*)(cocos2d::MenuItem*)>(&cocos2d::MenuItemToggle::addSubItem);
mt["GetSelectedItem"]=static_cast<cocos2d::MenuItem*(cocos2d::MenuItemToggle::*)()>(&cocos2d::MenuItemToggle::getSelectedItem);
mt["get"]["SelectedItem"]=mt["GetSelectedItem"];
mt["GetSelectedIndex"]=static_cast<unsigned int(cocos2d::MenuItemToggle::*)()const>(&cocos2d::MenuItemToggle::getSelectedIndex);
mt["get"]["SelectedIndex"]=mt["GetSelectedIndex"];
mt["SetSelectedIndex"]=static_cast<void(cocos2d::MenuItemToggle::*)(unsigned int)>(&cocos2d::MenuItemToggle::setSelectedIndex);
mt["set"]["SelectedIndex"]=mt["SetSelectedIndex"];
mt["GetSubItems"]=static_cast<const cocos2d::Vector<cocos2d::MenuItem *>&(cocos2d::MenuItemToggle::*)()const>(&cocos2d::MenuItemToggle::getSubItems);
mt["get"]["SubItems"]=mt["GetSubItems"];
mt["SetSubItems"]=static_cast<void(cocos2d::MenuItemToggle::*)(const cocos2d::Vector<cocos2d::MenuItem *>&)>(&cocos2d::MenuItemToggle::setSubItems);
mt["set"]["SubItems"]=mt["SetSubItems"];
}
void RegisterLuaCoreMenuStateAuto(cocos2d::extension::Lua& lua) {
sol::table enumTable = lua.create_table(lua.lua_state(),0,2);
enumTable["WAITING"]=cocos2d::Menu::State::WAITING;
enumTable["TRACKING_TOUCH"]=cocos2d::Menu::State::TRACKING_TOUCH;
lua["cc"]["Menu"]["static"]["State"]=lua.NewEnum(enumTable);
}
void RegisterLuaCoreMenuAuto(cocos2d::extension::Lua& lua){
cocos2d::extension::Lua::Id2Meta[typeid(cocos2d::Menu).name()] = sol::usertype_traits<cocos2d::Menu*>::metatable();
auto dep=lua.new_usertype<cocos2d::Menu>("deprecated.cocos2d::Menu");
dep[sol::base_classes]=sol::bases<cocos2d::Layer,cocos2d::Node,cocos2d::Ref,cocos2d::extension::LuaObject>();
sol::table mt=lua.NewClass(sol::usertype_traits<cocos2d::Menu*>::metatable(),sol::usertype_traits<cocos2d::Layer*>::metatable());
lua["cc"]["Menu"]=mt;
mt["__new__"] = [](){return nullptr;};
mt["AlignItemsVertically"]=static_cast<void(cocos2d::Menu::*)()>(&cocos2d::Menu::alignItemsVertically);
mt["AlignItemsVerticallyWithPadding"]=static_cast<void(cocos2d::Menu::*)(float)>(&cocos2d::Menu::alignItemsVerticallyWithPadding);
mt["AlignItemsHorizontally"]=static_cast<void(cocos2d::Menu::*)()>(&cocos2d::Menu::alignItemsHorizontally);
mt["AlignItemsHorizontallyWithPadding"]=static_cast<void(cocos2d::Menu::*)(float)>(&cocos2d::Menu::alignItemsHorizontallyWithPadding);
mt["AlignItemsInColumnsWithArray"]=static_cast<void(cocos2d::Menu::*)(const cocos2d::ValueVector&)>(&cocos2d::Menu::alignItemsInColumnsWithArray);
mt["AlignItemsInRowsWithArray"]=static_cast<void(cocos2d::Menu::*)(const cocos2d::ValueVector&)>(&cocos2d::Menu::alignItemsInRowsWithArray);
mt["IsEnabled"]=static_cast<bool(cocos2d::Menu::*)()const>(&cocos2d::Menu::isEnabled);
mt["get"]["Enabled"]=mt["IsEnabled"];
mt["SetEnabled"]=static_cast<void(cocos2d::Menu::*)(bool)>(&cocos2d::Menu::setEnabled);
mt["set"]["Enabled"]=mt["SetEnabled"];
RegisterLuaCoreMenuStateAuto(lua);
}
void RegisterLuaCoreMotionStreakAuto(cocos2d::extension::Lua& lua){
cocos2d::extension::Lua::Id2Meta[typeid(cocos2d::MotionStreak).name()] = sol::usertype_traits<cocos2d::MotionStreak*>::metatable();
auto dep=lua.new_usertype<cocos2d::MotionStreak>("deprecated.cocos2d::MotionStreak");
dep[sol::base_classes]=sol::bases<cocos2d::Node,cocos2d::Ref,cocos2d::extension::LuaObject,cocos2d::TextureProtocol,cocos2d::BlendProtocol>();
sol::table mt=lua.NewClass(sol::usertype_traits<cocos2d::MotionStreak*>::metatable(),sol::usertype_traits<cocos2d::Node*>::metatable(),sol::usertype_traits<cocos2d::TextureProtocol*>::metatable());
lua["cc"]["MotionStreak"]=mt;
mt["__new__"]=sol::overload(static_cast<cocos2d::MotionStreak*(*)(float,float,float,const cocos2d::Color3B&,cocos2d::Texture2D*)>(&cocos2d::MotionStreak::create),static_cast<cocos2d::MotionStreak*(*)(float,float,float,const cocos2d::Color3B&,const std::string&)>(&cocos2d::MotionStreak::create));
mt["TintWithColor"]=static_cast<void(cocos2d::MotionStreak::*)(const cocos2d::Color3B&)>(&cocos2d::MotionStreak::tintWithColor);
mt["Reset"]=static_cast<void(cocos2d::MotionStreak::*)()>(&cocos2d::MotionStreak::reset);
mt["IsFastMode"]=static_cast<bool(cocos2d::MotionStreak::*)()const>(&cocos2d::MotionStreak::isFastMode);
mt["get"]["FastMode"]=mt["IsFastMode"];
mt["SetFastMode"]=static_cast<void(cocos2d::MotionStreak::*)(bool)>(&cocos2d::MotionStreak::setFastMode);
mt["set"]["FastMode"]=mt["SetFastMode"];
mt["GetStroke"]=static_cast<float(cocos2d::MotionStreak::*)()const>(&cocos2d::MotionStreak::getStroke);
mt["get"]["Stroke"]=mt["GetStroke"];
mt["SetStroke"]=static_cast<void(cocos2d::MotionStreak::*)(float)>(&cocos2d::MotionStreak::setStroke);
mt["set"]["Stroke"]=mt["SetStroke"];
mt["IsStartingPositionInitialized"]=static_cast<bool(cocos2d::MotionStreak::*)()const>(&cocos2d::MotionStreak::isStartingPositionInitialized);
mt["get"]["StartingPositionInitialized"]=mt["IsStartingPositionInitialized"];
mt["SetStartingPositionInitialized"]=static_cast<void(cocos2d::MotionStreak::*)(bool)>(&cocos2d::MotionStreak::setStartingPositionInitialized);
mt["set"]["StartingPositionInitialized"]=mt["SetStartingPositionInitialized"];
}
void RegisterLuaCoreNodeGridAuto(cocos2d::extension::Lua& lua){
cocos2d::extension::Lua::Id2Meta[typeid(cocos2d::NodeGrid).name()] = sol::usertype_traits<cocos2d::NodeGrid*>::metatable();
auto dep=lua.new_usertype<cocos2d::NodeGrid>("deprecated.cocos2d::NodeGrid");
dep[sol::base_classes]=sol::bases<cocos2d::Node,cocos2d::Ref,cocos2d::extension::LuaObject>();
sol::table mt=lua.NewClass(sol::usertype_traits<cocos2d::NodeGrid*>::metatable(),sol::usertype_traits<cocos2d::Node*>::metatable());
lua["cc"]["NodeGrid"]=mt;
mt["__new__"]=sol::overload(static_cast<cocos2d::NodeGrid*(*)(const cocos2d::Rect&)>(&cocos2d::NodeGrid::create),static_cast<cocos2d::NodeGrid*(*)()>(&cocos2d::NodeGrid::create));
mt["GetGrid"]=static_cast<cocos2d::GridBase*(cocos2d::NodeGrid::*)()>(&cocos2d::NodeGrid::getGrid);
mt["get"]["Grid"]=mt["GetGrid"];
mt["SetGrid"]=static_cast<void(cocos2d::NodeGrid::*)(cocos2d::GridBase*)>(&cocos2d::NodeGrid::setGrid);
mt["set"]["Grid"]=mt["SetGrid"];
mt["SetTarget"]=static_cast<void(cocos2d::NodeGrid::*)(cocos2d::Node*)>(&cocos2d::NodeGrid::setTarget);
mt["set"]["Target"]=mt["SetTarget"];
mt["SetGridRect"]=static_cast<void(cocos2d::NodeGrid::*)(const cocos2d::Rect&)>(&cocos2d::NodeGrid::setGridRect);
mt["set"]["GridRect"]=mt["SetGridRect"];
mt["GetGridRect"]=static_cast<const cocos2d::Rect&(cocos2d::NodeGrid::*)()const>(&cocos2d::NodeGrid::getGridRect);
mt["get"]["GridRect"]=mt["GetGridRect"];
}
void RegisterLuaCoreParticleBatchNodeAuto(cocos2d::extension::Lua& lua){
cocos2d::extension::Lua::Id2Meta[typeid(cocos2d::ParticleBatchNode).name()] = sol::usertype_traits<cocos2d::ParticleBatchNode*>::metatable();
auto dep=lua.new_usertype<cocos2d::ParticleBatchNode>("deprecated.cocos2d::ParticleBatchNode");
dep[sol::base_classes]=sol::bases<cocos2d::Node,cocos2d::Ref,cocos2d::extension::LuaObject,cocos2d::TextureProtocol,cocos2d::BlendProtocol>();
sol::table mt=lua.NewClass(sol::usertype_traits<cocos2d::ParticleBatchNode*>::metatable(),sol::usertype_traits<cocos2d::Node*>::metatable(),sol::usertype_traits<cocos2d::TextureProtocol*>::metatable());
lua["cc"]["ParticleBatchNode"]=mt;
mt["static"]["CreateWithTexture"]=sol::overload([](cocos2d::Texture2D* arg0,int arg1){return cocos2d::ParticleBatchNode::createWithTexture(arg0,arg1);},[](cocos2d::Texture2D* arg0){return cocos2d::ParticleBatchNode::createWithTexture(arg0);});
mt["__new__"]=sol::overload([](const std::string& arg0,int arg1){return cocos2d::ParticleBatchNode::create(arg0,arg1);},[](const std::string& arg0){return cocos2d::ParticleBatchNode::create(arg0);});
mt["InsertChild"]=static_cast<void(cocos2d::ParticleBatchNode::*)(cocos2d::ParticleSystem*,int)>(&cocos2d::ParticleBatchNode::insertChild);
mt["RemoveChildAtIndex"]=static_cast<void(cocos2d::ParticleBatchNode::*)(int,bool)>(&cocos2d::ParticleBatchNode::removeChildAtIndex);
mt["DisableParticle"]=static_cast<void(cocos2d::ParticleBatchNode::*)(int)>(&cocos2d::ParticleBatchNode::disableParticle);
mt["GetTextureAtlas"]=static_cast<cocos2d::TextureAtlas*(cocos2d::ParticleBatchNode::*)()const>(&cocos2d::ParticleBatchNode::getTextureAtlas);
mt["get"]["TextureAtlas"]=mt["GetTextureAtlas"];
mt["SetTextureAtlas"]=static_cast<void(cocos2d::ParticleBatchNode::*)(cocos2d::TextureAtlas*)>(&cocos2d::ParticleBatchNode::setTextureAtlas);
mt["set"]["TextureAtlas"]=mt["SetTextureAtlas"];
}
void RegisterLuaCoreParticleSystemModeAuto(cocos2d::extension::Lua& lua) {
sol::table enumTable = lua.create_table(lua.lua_state(),0,2);
enumTable["GRAVITY"]=cocos2d::ParticleSystem::Mode::GRAVITY;
enumTable["RADIUS"]=cocos2d::ParticleSystem::Mode::RADIUS;
lua["cc"]["ParticleSystem"]["static"]["Mode"]=lua.NewEnum(enumTable);
}
void RegisterLuaCoreParticleSystemPositionTypeAuto(cocos2d::extension::Lua& lua) {
sol::table enumTable = lua.create_table(lua.lua_state(),0,3);
enumTable["FREE"]=cocos2d::ParticleSystem::PositionType::FREE;
enumTable["RELATIVE"]=cocos2d::ParticleSystem::PositionType::RELATIVE;
enumTable["GROUPED"]=cocos2d::ParticleSystem::PositionType::GROUPED;
lua["cc"]["ParticleSystem"]["static"]["PositionType"]=lua.NewEnum(enumTable);
}
void RegisterLuaCoreParticleSystem_AE_5a335f3592950f0f3daff6aec20cf00c_Auto(cocos2d::extension::Lua& lua) {
sol::table pTable = lua["cc"];
pTable = pTable["ParticleSystem"];
pTable["static"]["const"]["DURATION_INFINITY"] = cocos2d::ParticleSystem::DURATION_INFINITY;
pTable["static"]["const"]["START_SIZE_EQUAL_TO_END_SIZE"] = cocos2d::ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE;
pTable["static"]["const"]["START_RADIUS_EQUAL_TO_END_RADIUS"] = cocos2d::ParticleSystem::START_RADIUS_EQUAL_TO_END_RADIUS;
}
void RegisterLuaCoreParticleSystemAuto(cocos2d::extension::Lua& lua){
cocos2d::extension::Lua::Id2Meta[typeid(cocos2d::ParticleSystem).name()] = sol::usertype_traits<cocos2d::ParticleSystem*>::metatable();
auto dep=lua.new_usertype<cocos2d::ParticleSystem>("deprecated.cocos2d::ParticleSystem");
dep[sol::base_classes]=sol::bases<cocos2d::Node,cocos2d::Ref,cocos2d::extension::LuaObject,cocos2d::TextureProtocol,cocos2d::BlendProtocol,cocos2d::PlayableProtocol>();
sol::table mt=lua.NewClass(sol::usertype_traits<cocos2d::ParticleSystem*>::metatable(),sol::usertype_traits<cocos2d::Node*>::metatable(),sol::usertype_traits<cocos2d::TextureProtocol*>::metatable(),sol::usertype_traits<cocos2d::PlayableProtocol*>::metatable());
lua["cc"]["ParticleSystem"]=mt;
mt["__new__"]=static_cast<cocos2d::ParticleSystem*(*)(const std::string&)>(&cocos2d::ParticleSystem::create);
mt["static"]["CreateWithTotalParticles"]=static_cast<cocos2d::ParticleSystem*(*)(int)>(&cocos2d::ParticleSystem::createWithTotalParticles);
mt["static"]["GetAllParticleSystems"]=static_cast<cocos2d::Vector<cocos2d::ParticleSystem *>&(*)()>(&cocos2d::ParticleSystem::getAllParticleSystems);
mt["static"]["get"]["AllParticleSystems"]=mt["GetAllParticleSystems"];
mt["AddParticles"]=static_cast<void(cocos2d::ParticleSystem::*)(int)>(&cocos2d::ParticleSystem::addParticles);
mt["StopSystem"]=static_cast<void(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::stopSystem);
mt["ResetSystem"]=static_cast<void(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::resetSystem);
mt["IsFull"]=static_cast<bool(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::isFull);
mt["get"]["Full"]=mt["IsFull"];
mt["UpdateParticleQuads"]=static_cast<void(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::updateParticleQuads);
mt["PostStep"]=static_cast<void(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::postStep);
mt["UpdateWithNoTime"]=static_cast<void(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::updateWithNoTime);
mt["IsAutoRemoveOnFinish"]=static_cast<bool(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::isAutoRemoveOnFinish);
mt["get"]["AutoRemoveOnFinish"]=mt["IsAutoRemoveOnFinish"];
mt["SetAutoRemoveOnFinish"]=static_cast<void(cocos2d::ParticleSystem::*)(bool)>(&cocos2d::ParticleSystem::setAutoRemoveOnFinish);
mt["set"]["AutoRemoveOnFinish"]=mt["SetAutoRemoveOnFinish"];
mt["GetGravity"]=static_cast<const cocos2d::Vec2&(cocos2d::ParticleSystem::*)()>(&cocos2d::ParticleSystem::getGravity);
mt["get"]["Gravity"]=mt["GetGravity"];
mt["SetGravity"]=static_cast<void(cocos2d::ParticleSystem::*)(const cocos2d::Vec2&)>(&cocos2d::ParticleSystem::setGravity);
mt["set"]["Gravity"]=mt["SetGravity"];
mt["GetSpeed"]=static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getSpeed);
mt["get"]["Speed"]=mt["GetSpeed"];
mt["SetSpeed"]=static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setSpeed);
mt["set"]["Speed"]=mt["SetSpeed"];
mt["GetSpeedVar"]=static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getSpeedVar);
mt["get"]["SpeedVar"]=mt["GetSpeedVar"];
mt["SetSpeedVar"]=static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setSpeedVar);
mt["set"]["SpeedVar"]=mt["SetSpeedVar"];
mt["GetTangentialAccel"]=static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getTangentialAccel);
mt["get"]["TangentialAccel"]=mt["GetTangentialAccel"];
mt["SetTangentialAccel"]=static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setTangentialAccel);
mt["set"]["TangentialAccel"]=mt["SetTangentialAccel"];
mt["GetTangentialAccelVar"]=static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getTangentialAccelVar);
mt["get"]["TangentialAccelVar"]=mt["GetTangentialAccelVar"];
mt["SetTangentialAccelVar"]=static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setTangentialAccelVar);
mt["set"]["TangentialAccelVar"]=mt["SetTangentialAccelVar"];
mt["GetRadialAccel"]=static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getRadialAccel);
mt["get"]["RadialAccel"]=mt["GetRadialAccel"];
mt["SetRadialAccel"]=static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setRadialAccel);
mt["set"]["RadialAccel"]=mt["SetRadialAccel"];
mt["GetRadialAccelVar"]=static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getRadialAccelVar);
mt["get"]["RadialAccelVar"]=mt["GetRadialAccelVar"];
mt["SetRadialAccelVar"]=static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setRadialAccelVar);
mt["set"]["RadialAccelVar"]=mt["SetRadialAccelVar"];
mt["GetRotationIsDir"]=static_cast<bool(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getRotationIsDir);
mt["get"]["RotationIsDir"]=mt["GetRotationIsDir"];
mt["SetRotationIsDir"]=static_cast<void(cocos2d::ParticleSystem::*)(bool)>(&cocos2d::ParticleSystem::setRotationIsDir);
mt["set"]["RotationIsDir"]=mt["SetRotationIsDir"];
mt["GetStartRadius"]=static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getStartRadius);
mt["get"]["StartRadius"]=mt["GetStartRadius"];
mt["SetStartRadius"]=static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setStartRadius);
mt["set"]["StartRadius"]=mt["SetStartRadius"];
mt["GetStartRadiusVar"]=static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getStartRadiusVar);
mt["get"]["StartRadiusVar"]=mt["GetStartRadiusVar"];
mt["SetStartRadiusVar"]=static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setStartRadiusVar);
mt["set"]["StartRadiusVar"]=mt["SetStartRadiusVar"];
mt["GetEndRadius"]=static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getEndRadius);
mt["get"]["EndRadius"]=mt["GetEndRadius"];
mt["SetEndRadius"]=static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setEndRadius);
mt["set"]["EndRadius"]=mt["SetEndRadius"];
mt["GetEndRadiusVar"]=static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getEndRadiusVar);
mt["get"]["EndRadiusVar"]=mt["GetEndRadiusVar"];
mt["SetEndRadiusVar"]=static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setEndRadiusVar);
mt["set"]["EndRadiusVar"]=mt["SetEndRadiusVar"];
mt["GetRotatePerSecond"]=static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getRotatePerSecond);
mt["get"]["RotatePerSecond"]=mt["GetRotatePerSecond"];
mt["SetRotatePerSecond"]=static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setRotatePerSecond);
mt["set"]["RotatePerSecond"]=mt["SetRotatePerSecond"];
mt["GetRotatePerSecondVar"]=static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getRotatePerSecondVar);
mt["get"]["RotatePerSecondVar"]=mt["GetRotatePerSecondVar"];
mt["SetRotatePerSecondVar"]=static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setRotatePerSecondVar);
mt["set"]["RotatePerSecondVar"]=mt["SetRotatePerSecondVar"];
mt["IsActive"]=static_cast<bool(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::isActive);
mt["get"]["Active"]=mt["IsActive"];
mt["IsBlendAdditive"]=static_cast<bool(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::isBlendAdditive);
mt["get"]["BlendAdditive"]=mt["IsBlendAdditive"];
mt["SetBlendAdditive"]=static_cast<void(cocos2d::ParticleSystem::*)(bool)>(&cocos2d::ParticleSystem::setBlendAdditive);
mt["set"]["BlendAdditive"]=mt["SetBlendAdditive"];
mt["GetBatchNode"]=static_cast<cocos2d::ParticleBatchNode*(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getBatchNode);
mt["get"]["BatchNode"]=mt["GetBatchNode"];
mt["SetBatchNode"]=static_cast<void(cocos2d::ParticleSystem::*)(cocos2d::ParticleBatchNode*)>(&cocos2d::ParticleSystem::setBatchNode);
mt["set"]["BatchNode"]=mt["SetBatchNode"];
mt["GetAtlasIndex"]=static_cast<int(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getAtlasIndex);
mt["get"]["AtlasIndex"]=mt["GetAtlasIndex"];
mt["SetAtlasIndex"]=static_cast<void(cocos2d::ParticleSystem::*)(int)>(&cocos2d::ParticleSystem::setAtlasIndex);
mt["set"]["AtlasIndex"]=mt["SetAtlasIndex"];
mt["GetParticleCount"]=static_cast<unsigned int(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getParticleCount);
mt["get"]["ParticleCount"]=mt["GetParticleCount"];
mt["GetDuration"]=static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getDuration);
mt["get"]["Duration"]=mt["GetDuration"];
mt["SetDuration"]=static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setDuration);
mt["set"]["Duration"]=mt["SetDuration"];
mt["GetSourcePosition"]=static_cast<const cocos2d::Vec2&(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getSourcePosition);
mt["get"]["SourcePosition"]=mt["GetSourcePosition"];
mt["SetSourcePosition"]=static_cast<void(cocos2d::ParticleSystem::*)(const cocos2d::Vec2&)>(&cocos2d::ParticleSystem::setSourcePosition);
mt["set"]["SourcePosition"]=mt["SetSourcePosition"];
mt["GetPosVar"]=static_cast<const cocos2d::Vec2&(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getPosVar);
mt["get"]["PosVar"]=mt["GetPosVar"];
mt["SetPosVar"]=static_cast<void(cocos2d::ParticleSystem::*)(const cocos2d::Vec2&)>(&cocos2d::ParticleSystem::setPosVar);
mt["set"]["PosVar"]=mt["SetPosVar"];
mt["GetLife"]=static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getLife);
mt["get"]["Life"]=mt["GetLife"];
mt["SetLife"]=static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setLife);
mt["set"]["Life"]=mt["SetLife"];
mt["GetLifeVar"]=static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getLifeVar);
mt["get"]["LifeVar"]=mt["GetLifeVar"];
mt["SetLifeVar"]=static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setLifeVar);
mt["set"]["LifeVar"]=mt["SetLifeVar"];
mt["GetAngle"]=static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getAngle);
mt["get"]["Angle"]=mt["GetAngle"];
mt["SetAngle"]=static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setAngle);
mt["set"]["Angle"]=mt["SetAngle"];
mt["GetAngleVar"]=static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getAngleVar);
mt["get"]["AngleVar"]=mt["GetAngleVar"];
mt["SetAngleVar"]=static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setAngleVar);
mt["set"]["AngleVar"]=mt["SetAngleVar"];
mt["GetEmitterMode"]=static_cast<cocos2d::ParticleSystem::Mode(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getEmitterMode);
mt["get"]["EmitterMode"]=mt["GetEmitterMode"];
mt["SetEmitterMode"]=static_cast<void(cocos2d::ParticleSystem::*)(cocos2d::ParticleSystem::Mode)>(&cocos2d::ParticleSystem::setEmitterMode);
mt["set"]["EmitterMode"]=mt["SetEmitterMode"];
mt["GetStartSize"]=static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getStartSize);
mt["get"]["StartSize"]=mt["GetStartSize"];
mt["SetStartSize"]=static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setStartSize);
mt["set"]["StartSize"]=mt["SetStartSize"];
mt["GetStartSizeVar"]=static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getStartSizeVar);
mt["get"]["StartSizeVar"]=mt["GetStartSizeVar"];
mt["SetStartSizeVar"]=static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setStartSizeVar);
mt["set"]["StartSizeVar"]=mt["SetStartSizeVar"];
mt["GetEndSize"]=static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getEndSize);
mt["get"]["EndSize"]=mt["GetEndSize"];
mt["SetEndSize"]=static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setEndSize);
mt["set"]["EndSize"]=mt["SetEndSize"];
mt["GetEndSizeVar"]=static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getEndSizeVar);
mt["get"]["EndSizeVar"]=mt["GetEndSizeVar"];
mt["SetEndSizeVar"]=static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setEndSizeVar);
mt["set"]["EndSizeVar"]=mt["SetEndSizeVar"];
mt["GetStartColor"]=static_cast<const cocos2d::Color4F&(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getStartColor);
mt["get"]["StartColor"]=mt["GetStartColor"];
mt["SetStartColor"]=static_cast<void(cocos2d::ParticleSystem::*)(const cocos2d::Color4F&)>(&cocos2d::ParticleSystem::setStartColor);
mt["set"]["StartColor"]=mt["SetStartColor"];
mt["GetStartColorVar"]=static_cast<const cocos2d::Color4F&(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getStartColorVar);
mt["get"]["StartColorVar"]=mt["GetStartColorVar"];
mt["SetStartColorVar"]=static_cast<void(cocos2d::ParticleSystem::*)(const cocos2d::Color4F&)>(&cocos2d::ParticleSystem::setStartColorVar);
mt["set"]["StartColorVar"]=mt["SetStartColorVar"];
mt["GetEndColor"]=static_cast<const cocos2d::Color4F&(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getEndColor);
mt["get"]["EndColor"]=mt["GetEndColor"];
mt["SetEndColor"]=static_cast<void(cocos2d::ParticleSystem::*)(const cocos2d::Color4F&)>(&cocos2d::ParticleSystem::setEndColor);
mt["set"]["EndColor"]=mt["SetEndColor"];
mt["GetEndColorVar"]=static_cast<const cocos2d::Color4F&(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getEndColorVar);
mt["get"]["EndColorVar"]=mt["GetEndColorVar"];
mt["SetEndColorVar"]=static_cast<void(cocos2d::ParticleSystem::*)(const cocos2d::Color4F&)>(&cocos2d::ParticleSystem::setEndColorVar);
mt["set"]["EndColorVar"]=mt["SetEndColorVar"];
mt["GetStartSpin"]=static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getStartSpin);
mt["get"]["StartSpin"]=mt["GetStartSpin"];
mt["SetStartSpin"]=static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setStartSpin);
mt["set"]["StartSpin"]=mt["SetStartSpin"];
mt["GetStartSpinVar"]=static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getStartSpinVar);
mt["get"]["StartSpinVar"]=mt["GetStartSpinVar"];
mt["SetStartSpinVar"]=static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setStartSpinVar);
mt["set"]["StartSpinVar"]=mt["SetStartSpinVar"];
mt["GetEndSpin"]=static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getEndSpin);
mt["get"]["EndSpin"]=mt["GetEndSpin"];
mt["SetEndSpin"]=static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setEndSpin);
mt["set"]["EndSpin"]=mt["SetEndSpin"];
mt["GetEndSpinVar"]=static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getEndSpinVar);
mt["get"]["EndSpinVar"]=mt["GetEndSpinVar"];
mt["SetEndSpinVar"]=static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setEndSpinVar);
mt["set"]["EndSpinVar"]=mt["SetEndSpinVar"];
mt["GetEmissionRate"]=static_cast<float(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getEmissionRate);
mt["get"]["EmissionRate"]=mt["GetEmissionRate"];
mt["SetEmissionRate"]=static_cast<void(cocos2d::ParticleSystem::*)(float)>(&cocos2d::ParticleSystem::setEmissionRate);
mt["set"]["EmissionRate"]=mt["SetEmissionRate"];
mt["GetTotalParticles"]=static_cast<int(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getTotalParticles);
mt["get"]["TotalParticles"]=mt["GetTotalParticles"];
mt["SetTotalParticles"]=static_cast<void(cocos2d::ParticleSystem::*)(int)>(&cocos2d::ParticleSystem::setTotalParticles);
mt["set"]["TotalParticles"]=mt["SetTotalParticles"];
mt["GetPositionType"]=static_cast<cocos2d::ParticleSystem::PositionType(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getPositionType);
mt["get"]["PositionType"]=mt["GetPositionType"];
mt["SetPositionType"]=static_cast<void(cocos2d::ParticleSystem::*)(cocos2d::ParticleSystem::PositionType)>(&cocos2d::ParticleSystem::setPositionType);
mt["set"]["PositionType"]=mt["SetPositionType"];
mt["GetResourceFile"]=static_cast<const std::string&(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::getResourceFile);
mt["get"]["ResourceFile"]=mt["GetResourceFile"];
mt["SetSourcePositionCompatible"]=static_cast<void(cocos2d::ParticleSystem::*)(bool)>(&cocos2d::ParticleSystem::setSourcePositionCompatible);
mt["set"]["SourcePositionCompatible"]=mt["SetSourcePositionCompatible"];
mt["IsSourcePositionCompatible"]=static_cast<bool(cocos2d::ParticleSystem::*)()const>(&cocos2d::ParticleSystem::isSourcePositionCompatible);
mt["get"]["SourcePositionCompatible"]=mt["IsSourcePositionCompatible"];
RegisterLuaCoreParticleSystemModeAuto(lua);
RegisterLuaCoreParticleSystemPositionTypeAuto(lua);
RegisterLuaCoreParticleSystem_AE_5a335f3592950f0f3daff6aec20cf00c_Auto(lua);
}
void RegisterLuaCoreParticleSystemQuadAuto(cocos2d::extension::Lua& lua){
cocos2d::extension::Lua::Id2Meta[typeid(cocos2d::ParticleSystemQuad).name()] = sol::usertype_traits<cocos2d::ParticleSystemQuad*>::metatable();
auto dep=lua.new_usertype<cocos2d::ParticleSystemQuad>("deprecated.cocos2d::ParticleSystemQuad");
dep[sol::base_classes]=sol::bases<cocos2d::ParticleSystem,cocos2d::Node,cocos2d::Ref,cocos2d::extension::LuaObject,cocos2d::TextureProtocol,cocos2d::BlendProtocol,cocos2d::PlayableProtocol>();
sol::table mt=lua.NewClass(sol::usertype_traits<cocos2d::ParticleSystemQuad*>::metatable(),sol::usertype_traits<cocos2d::ParticleSystem*>::metatable());
lua["cc"]["ParticleSystemQuad"]=mt;
mt["__new__"]=sol::overload(static_cast<cocos2d::ParticleSystemQuad*(*)(const cocos2d::ValueMap&)>(&cocos2d::ParticleSystemQuad::create),static_cast<cocos2d::ParticleSystemQuad*(*)(const std::string&)>(&cocos2d::ParticleSystemQuad::create),static_cast<cocos2d::ParticleSystemQuad*(*)()>(&cocos2d::ParticleSystemQuad::create));
mt["static"]["CreateWithTotalParticles"]=static_cast<cocos2d::ParticleSystemQuad*(*)(int)>(&cocos2d::ParticleSystemQuad::createWithTotalParticles);
mt["SetDisplayFrame"]=static_cast<void(cocos2d::ParticleSystemQuad::*)(cocos2d::SpriteFrame*)>(&cocos2d::ParticleSystemQuad::setDisplayFrame);
mt["set"]["DisplayFrame"]=mt["SetDisplayFrame"];
mt["SetTextureWithRect"]=static_cast<void(cocos2d::ParticleSystemQuad::*)(cocos2d::Texture2D*,const cocos2d::Rect&)>(&cocos2d::ParticleSystemQuad::setTextureWithRect);
mt["ListenRendererRecreated"]=static_cast<void(cocos2d::ParticleSystemQuad::*)(cocos2d::EventCustom*)>(&cocos2d::ParticleSystemQuad::listenRendererRecreated);
}
void RegisterLuaCoreParticleFireAuto(cocos2d::extension::Lua& lua){
cocos2d::extension::Lua::Id2Meta[typeid(cocos2d::ParticleFire).name()] = sol::usertype_traits<cocos2d::ParticleFire*>::metatable();
auto dep=lua.new_usertype<cocos2d::ParticleFire>("deprecated.cocos2d::ParticleFire");
dep[sol::base_classes]=sol::bases<cocos2d::ParticleSystemQuad,cocos2d::ParticleSystem,cocos2d::Node,cocos2d::Ref,cocos2d::extension::LuaObject,cocos2d::TextureProtocol,cocos2d::BlendProtocol,cocos2d::PlayableProtocol>();
sol::table mt=lua.NewClass(sol::usertype_traits<cocos2d::ParticleFire*>::metatable(),sol::usertype_traits<cocos2d::ParticleSystemQuad*>::metatable());
lua["cc"]["ParticleFire"]=mt;
mt["__new__"]=static_cast<cocos2d::ParticleFire*(*)()>(&cocos2d::ParticleFire::create);
mt["static"]["CreateWithTotalParticles"]=static_cast<cocos2d::ParticleFire*(*)(int)>(&cocos2d::ParticleFire::createWithTotalParticles);
}
void RegisterLuaCoreParticleFireworksAuto(cocos2d::extension::Lua& lua){
cocos2d::extension::Lua::Id2Meta[typeid(cocos2d::ParticleFireworks).name()] = sol::usertype_traits<cocos2d::ParticleFireworks*>::metatable();
auto dep=lua.new_usertype<cocos2d::ParticleFireworks>("deprecated.cocos2d::ParticleFireworks");
dep[sol::base_classes]=sol::bases<cocos2d::ParticleSystemQuad,cocos2d::ParticleSystem,cocos2d::Node,cocos2d::Ref,cocos2d::extension::LuaObject,cocos2d::TextureProtocol,cocos2d::BlendProtocol,cocos2d::PlayableProtocol>();
sol::table mt=lua.NewClass(sol::usertype_traits<cocos2d::ParticleFireworks*>::metatable(),sol::usertype_traits<cocos2d::ParticleSystemQuad*>::metatable());
lua["cc"]["ParticleFireworks"]=mt;
mt["__new__"]=static_cast<cocos2d::ParticleFireworks*(*)()>(&cocos2d::ParticleFireworks::create);
mt["static"]["CreateWithTotalParticles"]=static_cast<cocos2d::ParticleFireworks*(*)(int)>(&cocos2d::ParticleFireworks::createWithTotalParticles);
}
void RegisterLuaCoreParticleSunAuto(cocos2d::extension::Lua& lua){
cocos2d::extension::Lua::Id2Meta[typeid(cocos2d::ParticleSun).name()] = sol::usertype_traits<cocos2d::ParticleSun*>::metatable();
auto dep=lua.new_usertype<cocos2d::ParticleSun>("deprecated.cocos2d::ParticleSun");
dep[sol::base_classes]=sol::bases<cocos2d::ParticleSystemQuad,cocos2d::ParticleSystem,cocos2d::Node,cocos2d::Ref,cocos2d::extension::LuaObject,cocos2d::TextureProtocol,cocos2d::BlendProtocol,cocos2d::PlayableProtocol>();
sol::table mt=lua.NewClass(sol::usertype_traits<cocos2d::ParticleSun*>::metatable(),sol::usertype_traits<cocos2d::ParticleSystemQuad*>::metatable());
lua["cc"]["ParticleSun"]=mt;
mt["__new__"]=static_cast<cocos2d::ParticleSun*(*)()>(&cocos2d::ParticleSun::create);
mt["static"]["CreateWithTotalParticles"]=static_cast<cocos2d::ParticleSun*(*)(int)>(&cocos2d::ParticleSun::createWithTotalParticles);
}
}
