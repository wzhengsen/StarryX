#include "scripting/lua-bindings/auto/CCRegisterLuaUIAuto.hpp"
#include "ui/CocosGUI.h"
void RegisterLuaUIImageViewAuto(cocos2d::Lua& lua){
sol::table ns = lua["ccui"];
auto mt=lua.NewUserType<cocos2d::ui::ImageView,cocos2d::ui::Widget,cocos2d::ProtectedNode,cocos2d::Node,cocos2d::Ref,cocos2d::LuaObject,cocos2d::ui::LayoutParameterProtocol,cocos2d::BlendProtocol>("ImageView",false);
ns["ImageView"] = mt;
lua["ImageView"] = sol::nil;
mt.set_function("loadTexture",sol::overload([](cocos2d::ui::ImageView* obj,const std::string& arg0){return obj->loadTexture(arg0);},[](cocos2d::ui::ImageView* obj,const std::string& arg0,cocos2d::ui::Widget::TextureResType arg1){return obj->loadTexture(arg0,arg1);}));
mt.set_function("setTextureRect",static_cast<void(cocos2d::ui::ImageView::*)(const cocos2d::Rect&)>(&cocos2d::ui::ImageView::setTextureRect));
mt.set_function("setScale9Enabled",static_cast<void(cocos2d::ui::ImageView::*)(bool)>(&cocos2d::ui::ImageView::setScale9Enabled));
mt.set_function("isScale9Enabled",static_cast<bool(cocos2d::ui::ImageView::*)()const>(&cocos2d::ui::ImageView::isScale9Enabled));
mt.set_function("setCapInsets",static_cast<void(cocos2d::ui::ImageView::*)(const cocos2d::Rect&)>(&cocos2d::ui::ImageView::setCapInsets));
mt.set_function("getCapInsets",static_cast<const cocos2d::Rect&(cocos2d::ui::ImageView::*)()const>(&cocos2d::ui::ImageView::getCapInsets));
mt.set_function("getRenderer",static_cast<cocos2d::ui::Scale9Sprite*(cocos2d::ui::ImageView::*)()const>(&cocos2d::ui::ImageView::getRenderer));
mt.set_function("setBlendFunc",static_cast<void(cocos2d::ui::ImageView::*)(const cocos2d::BlendFunc&)>(&cocos2d::ui::ImageView::setBlendFunc));
mt.set_function("getBlendFunc",static_cast<const cocos2d::BlendFunc&(cocos2d::ui::ImageView::*)()const>(&cocos2d::ui::ImageView::getBlendFunc));
mt.set_function("ignoreContentAdaptWithSize",static_cast<void(cocos2d::ui::ImageView::*)(bool)>(&cocos2d::ui::ImageView::ignoreContentAdaptWithSize));
mt.set_function("getDescription",static_cast<std::string(cocos2d::ui::ImageView::*)()const>(&cocos2d::ui::ImageView::getDescription));
mt.set_function("getVirtualRendererSize",static_cast<cocos2d::Size(cocos2d::ui::ImageView::*)()const>(&cocos2d::ui::ImageView::getVirtualRendererSize));
mt.set_function("getVirtualRenderer",static_cast<cocos2d::Node*(cocos2d::ui::ImageView::*)()>(&cocos2d::ui::ImageView::getVirtualRenderer));
mt.set_function("getRenderFile",static_cast<cocos2d::ResourceData(cocos2d::ui::ImageView::*)()>(&cocos2d::ui::ImageView::getRenderFile));
mt.set_function("createInstance",static_cast<cocos2d::Ref*(*)()>(&cocos2d::ui::ImageView::createInstance));
mt.set_function(sol::meta_function::construct,sol::overload([](cocos2d::ui::ImageView* obj,const std::string& arg0){return obj->create(arg0);},[](cocos2d::ui::ImageView* obj,const std::string& arg0,cocos2d::ui::Widget::TextureResType arg1){return obj->create(arg0,arg1);},static_cast<cocos2d::ui::ImageView*(*)()>(&cocos2d::ui::ImageView::create)));
}
void RegisterLuaUITextTypeAuto(cocos2d::Lua& lua) {
sol::table pTable = lua["ccui"];
pTable = pTable["Text"];
pTable.new_enum("Type"
,"SYSTEM",0
,"TTF",1
);}
void RegisterLuaUITextAuto(cocos2d::Lua& lua){
sol::table ns = lua["ccui"];
auto mt=lua.NewUserType<cocos2d::ui::Text,cocos2d::ui::Widget,cocos2d::ProtectedNode,cocos2d::Node,cocos2d::Ref,cocos2d::LuaObject,cocos2d::ui::LayoutParameterProtocol,cocos2d::BlendProtocol>("Text",false);
ns["Text"] = mt;
lua["Text"] = sol::nil;
mt.set_function("setString",static_cast<void(cocos2d::ui::Text::*)(const std::string&)>(&cocos2d::ui::Text::setString));
mt.set_function("getString",static_cast<const std::string&(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getString));
mt.set_function("getStringLength",static_cast<ssize_t(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getStringLength));
mt.set_function("setFontSize",static_cast<void(cocos2d::ui::Text::*)(float)>(&cocos2d::ui::Text::setFontSize));
mt.set_function("getFontSize",static_cast<float(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getFontSize));
mt.set_function("setFontName",static_cast<void(cocos2d::ui::Text::*)(const std::string&)>(&cocos2d::ui::Text::setFontName));
mt.set_function("getFontName",static_cast<const std::string&(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getFontName));
mt.set_function("getType",static_cast<cocos2d::ui::Text::Type(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getType));
mt.set_function("setTouchScaleChangeEnabled",static_cast<void(cocos2d::ui::Text::*)(bool)>(&cocos2d::ui::Text::setTouchScaleChangeEnabled));
mt.set_function("isTouchScaleChangeEnabled",static_cast<bool(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::isTouchScaleChangeEnabled));
mt.set_function("getVirtualRendererSize",static_cast<cocos2d::Size(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getVirtualRendererSize));
mt.set_function("getVirtualRenderer",static_cast<cocos2d::Node*(cocos2d::ui::Text::*)()>(&cocos2d::ui::Text::getVirtualRenderer));
mt.set_function("getAutoRenderSize",static_cast<cocos2d::Size(cocos2d::ui::Text::*)()>(&cocos2d::ui::Text::getAutoRenderSize));
mt.set_function("getDescription",static_cast<std::string(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getDescription));
mt.set_function("setTextAreaSize",static_cast<void(cocos2d::ui::Text::*)(const cocos2d::Size&)>(&cocos2d::ui::Text::setTextAreaSize));
mt.set_function("getTextAreaSize",static_cast<const cocos2d::Size&(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getTextAreaSize));
mt.set_function("setTextHorizontalAlignment",static_cast<void(cocos2d::ui::Text::*)(cocos2d::TextHAlignment)>(&cocos2d::ui::Text::setTextHorizontalAlignment));
mt.set_function("getTextHorizontalAlignment",static_cast<cocos2d::TextHAlignment(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getTextHorizontalAlignment));
mt.set_function("setTextVerticalAlignment",static_cast<void(cocos2d::ui::Text::*)(cocos2d::TextVAlignment)>(&cocos2d::ui::Text::setTextVerticalAlignment));
mt.set_function("getTextVerticalAlignment",static_cast<cocos2d::TextVAlignment(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getTextVerticalAlignment));
mt.set_function("setTextColor",static_cast<void(cocos2d::ui::Text::*)(const cocos2d::Color4B)>(&cocos2d::ui::Text::setTextColor));
mt.set_function("getTextColor",static_cast<const cocos2d::Color4B&(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getTextColor));
mt.set_function("enableShadow",sol::overload([](cocos2d::ui::Text* obj){return obj->enableShadow();},[](cocos2d::ui::Text* obj,const cocos2d::Color4B& arg0){return obj->enableShadow(arg0);},[](cocos2d::ui::Text* obj,const cocos2d::Color4B& arg0,const cocos2d::Size& arg1){return obj->enableShadow(arg0,arg1);},[](cocos2d::ui::Text* obj,const cocos2d::Color4B& arg0,const cocos2d::Size& arg1,int arg2){return obj->enableShadow(arg0,arg1,arg2);}));
mt.set_function("enableOutline",sol::overload([](cocos2d::ui::Text* obj,const cocos2d::Color4B& arg0){return obj->enableOutline(arg0);},[](cocos2d::ui::Text* obj,const cocos2d::Color4B& arg0,int arg1){return obj->enableOutline(arg0,arg1);}));
mt.set_function("enableGlow",static_cast<void(cocos2d::ui::Text::*)(const cocos2d::Color4B&)>(&cocos2d::ui::Text::enableGlow));
mt.set_function("disableEffect",sol::overload(static_cast<void(cocos2d::ui::Text::*)(cocos2d::LabelEffect)>(&cocos2d::ui::Text::disableEffect),static_cast<void(cocos2d::ui::Text::*)()>(&cocos2d::ui::Text::disableEffect)));
mt.set_function("isShadowEnabled",static_cast<bool(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::isShadowEnabled));
mt.set_function("getShadowOffset",static_cast<cocos2d::Size(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getShadowOffset));
mt.set_function("getShadowBlurRadius",static_cast<float(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getShadowBlurRadius));
mt.set_function("getShadowColor",static_cast<cocos2d::Color4B(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getShadowColor));
mt.set_function("getOutlineSize",static_cast<int(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getOutlineSize));
mt.set_function("getLabelEffectType",static_cast<cocos2d::LabelEffect(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getLabelEffectType));
mt.set_function("getEffectColor",static_cast<cocos2d::Color4B(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getEffectColor));
mt.set_function("getLetter",static_cast<cocos2d::Sprite*(cocos2d::ui::Text::*)(int)>(&cocos2d::ui::Text::getLetter));
mt.set_function("setBlendFunc",static_cast<void(cocos2d::ui::Text::*)(const cocos2d::BlendFunc&)>(&cocos2d::ui::Text::setBlendFunc));
mt.set_function("getBlendFunc",static_cast<const cocos2d::BlendFunc&(cocos2d::ui::Text::*)()const>(&cocos2d::ui::Text::getBlendFunc));
mt.set_function("createInstance",static_cast<cocos2d::Ref*(*)()>(&cocos2d::ui::Text::createInstance));
mt.set_function(sol::meta_function::construct,sol::overload(static_cast<cocos2d::ui::Text*(*)(const std::string&,const std::string&,float)>(&cocos2d::ui::Text::create),static_cast<cocos2d::ui::Text*(*)()>(&cocos2d::ui::Text::create)));
RegisterLuaUITextTypeAuto(lua);
}
void RegisterLuaUITextAtlasAuto(cocos2d::Lua& lua){
sol::table ns = lua["ccui"];
auto mt=lua.NewUserType<cocos2d::ui::TextAtlas,cocos2d::ui::Widget,cocos2d::ProtectedNode,cocos2d::Node,cocos2d::Ref,cocos2d::LuaObject,cocos2d::ui::LayoutParameterProtocol>("TextAtlas",false);
ns["TextAtlas"] = mt;
lua["TextAtlas"] = sol::nil;
mt.set_function("setProperty",static_cast<void(cocos2d::ui::TextAtlas::*)(const std::string&,const std::string&,int,int,const std::string&)>(&cocos2d::ui::TextAtlas::setProperty));
mt.set_function("setString",static_cast<void(cocos2d::ui::TextAtlas::*)(const std::string&)>(&cocos2d::ui::TextAtlas::setString));
mt.set_function("getString",static_cast<const std::string&(cocos2d::ui::TextAtlas::*)()const>(&cocos2d::ui::TextAtlas::getString));
mt.set_function("getStringLength",static_cast<ssize_t(cocos2d::ui::TextAtlas::*)()const>(&cocos2d::ui::TextAtlas::getStringLength));
mt.set_function("getVirtualRendererSize",static_cast<cocos2d::Size(cocos2d::ui::TextAtlas::*)()const>(&cocos2d::ui::TextAtlas::getVirtualRendererSize));
mt.set_function("getVirtualRenderer",static_cast<cocos2d::Node*(cocos2d::ui::TextAtlas::*)()>(&cocos2d::ui::TextAtlas::getVirtualRenderer));
mt.set_function("getDescription",static_cast<std::string(cocos2d::ui::TextAtlas::*)()const>(&cocos2d::ui::TextAtlas::getDescription));
mt.set_function("adaptRenderers",static_cast<void(cocos2d::ui::TextAtlas::*)()>(&cocos2d::ui::TextAtlas::adaptRenderers));
mt.set_function("getRenderFile",static_cast<cocos2d::ResourceData(cocos2d::ui::TextAtlas::*)()>(&cocos2d::ui::TextAtlas::getRenderFile));
mt.set_function("createInstance",static_cast<cocos2d::Ref*(*)()>(&cocos2d::ui::TextAtlas::createInstance));
mt.set_function(sol::meta_function::construct,sol::overload(static_cast<cocos2d::ui::TextAtlas*(*)(const std::string&,const std::string&,int,int,const std::string&)>(&cocos2d::ui::TextAtlas::create),static_cast<cocos2d::ui::TextAtlas*(*)()>(&cocos2d::ui::TextAtlas::create)));
}
void RegisterLuaUILoadingBarDirectionAuto(cocos2d::Lua& lua) {
sol::table pTable = lua["ccui"];
pTable = pTable["LoadingBar"];
pTable.new_enum("Direction"
,"LEFT",0
,"RIGHT",1
);}
void RegisterLuaUILoadingBarAuto(cocos2d::Lua& lua){
sol::table ns = lua["ccui"];
auto mt=lua.NewUserType<cocos2d::ui::LoadingBar,cocos2d::ui::Widget,cocos2d::ProtectedNode,cocos2d::Node,cocos2d::Ref,cocos2d::LuaObject,cocos2d::ui::LayoutParameterProtocol>("LoadingBar",false);
ns["LoadingBar"] = mt;
lua["LoadingBar"] = sol::nil;
mt.set_function("setDirection",static_cast<void(cocos2d::ui::LoadingBar::*)(cocos2d::ui::LoadingBar::Direction)>(&cocos2d::ui::LoadingBar::setDirection));
mt.set_function("getDirection",static_cast<cocos2d::ui::LoadingBar::Direction(cocos2d::ui::LoadingBar::*)()const>(&cocos2d::ui::LoadingBar::getDirection));
mt.set_function("loadTexture",sol::overload([](cocos2d::ui::LoadingBar* obj,const std::string& arg0){return obj->loadTexture(arg0);},[](cocos2d::ui::LoadingBar* obj,const std::string& arg0,cocos2d::ui::Widget::TextureResType arg1){return obj->loadTexture(arg0,arg1);}));
mt.set_function("setPercent",static_cast<void(cocos2d::ui::LoadingBar::*)(float)>(&cocos2d::ui::LoadingBar::setPercent));
mt.set_function("getPercent",static_cast<float(cocos2d::ui::LoadingBar::*)()const>(&cocos2d::ui::LoadingBar::getPercent));
mt.set_function("setScale9Enabled",static_cast<void(cocos2d::ui::LoadingBar::*)(bool)>(&cocos2d::ui::LoadingBar::setScale9Enabled));
mt.set_function("isScale9Enabled",static_cast<bool(cocos2d::ui::LoadingBar::*)()const>(&cocos2d::ui::LoadingBar::isScale9Enabled));
mt.set_function("setCapInsets",static_cast<void(cocos2d::ui::LoadingBar::*)(const cocos2d::Rect&)>(&cocos2d::ui::LoadingBar::setCapInsets));
mt.set_function("getCapInsets",static_cast<const cocos2d::Rect&(cocos2d::ui::LoadingBar::*)()const>(&cocos2d::ui::LoadingBar::getCapInsets));
mt.set_function("ignoreContentAdaptWithSize",static_cast<void(cocos2d::ui::LoadingBar::*)(bool)>(&cocos2d::ui::LoadingBar::ignoreContentAdaptWithSize));
mt.set_function("getVirtualRendererSize",static_cast<cocos2d::Size(cocos2d::ui::LoadingBar::*)()const>(&cocos2d::ui::LoadingBar::getVirtualRendererSize));
mt.set_function("getVirtualRenderer",static_cast<cocos2d::Node*(cocos2d::ui::LoadingBar::*)()>(&cocos2d::ui::LoadingBar::getVirtualRenderer));
mt.set_function("getDescription",static_cast<std::string(cocos2d::ui::LoadingBar::*)()const>(&cocos2d::ui::LoadingBar::getDescription));
mt.set_function("getRenderFile",static_cast<cocos2d::ResourceData(cocos2d::ui::LoadingBar::*)()>(&cocos2d::ui::LoadingBar::getRenderFile));
mt.set_function("createInstance",static_cast<cocos2d::Ref*(*)()>(&cocos2d::ui::LoadingBar::createInstance));
mt.set_function(sol::meta_function::construct,sol::overload([](cocos2d::ui::LoadingBar* obj,const std::string& arg0){return obj->create(arg0);},[](cocos2d::ui::LoadingBar* obj,const std::string& arg0,float arg1){return obj->create(arg0,arg1);},static_cast<cocos2d::ui::LoadingBar*(*)()>(&cocos2d::ui::LoadingBar::create),[](cocos2d::ui::LoadingBar* obj,const std::string& arg0,cocos2d::ui::Widget::TextureResType arg1){return obj->create(arg0,arg1);},[](cocos2d::ui::LoadingBar* obj,const std::string& arg0,cocos2d::ui::Widget::TextureResType arg1,float arg2){return obj->create(arg0,arg1,arg2);}));
RegisterLuaUILoadingBarDirectionAuto(lua);
}
void RegisterLuaUIScrollViewDirectionAuto(cocos2d::Lua& lua) {
sol::table pTable = lua["ccui"];
pTable = pTable["ScrollView"];
pTable.new_enum("Direction"
,"NONE",0
,"VERTICAL",1
,"HORIZONTAL",2
,"BOTH",3
);}
void RegisterLuaUIScrollViewEventTypeAuto(cocos2d::Lua& lua) {
sol::table pTable = lua["ccui"];
pTable = pTable["ScrollView"];
pTable.new_enum("EventType"
,"SCROLL_TO_TOP",0
,"SCROLL_TO_BOTTOM",1
,"SCROLL_TO_LEFT",2
,"SCROLL_TO_RIGHT",3
,"SCROLLING",4
,"BOUNCE_TOP",5
,"BOUNCE_BOTTOM",6
,"BOUNCE_LEFT",7
,"BOUNCE_RIGHT",8
,"CONTAINER_MOVED",9
,"SCROLLING_BEGAN",10
,"SCROLLING_ENDED",11
,"AUTOSCROLL_ENDED",12
);}
void RegisterLuaUIScrollViewAuto(cocos2d::Lua& lua){
sol::table ns = lua["ccui"];
auto mt=lua.NewUserType<cocos2d::ui::ScrollView,cocos2d::ui::Layout,cocos2d::ui::Widget,cocos2d::ProtectedNode,cocos2d::Node,cocos2d::Ref,cocos2d::LuaObject,cocos2d::ui::LayoutParameterProtocol,cocos2d::ui::LayoutProtocol>("ScrollView",false);
ns["ScrollView"] = mt;
lua["ScrollView"] = sol::nil;
mt.set_function("setDirection",static_cast<void(cocos2d::ui::ScrollView::*)(cocos2d::ui::ScrollView::Direction)>(&cocos2d::ui::ScrollView::setDirection));
mt.set_function("getDirection",static_cast<cocos2d::ui::ScrollView::Direction(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getDirection));
mt.set_function("getInnerContainer",static_cast<cocos2d::ui::Layout*(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getInnerContainer));
mt.set_function("stopScroll",static_cast<void(cocos2d::ui::ScrollView::*)()>(&cocos2d::ui::ScrollView::stopScroll));
mt.set_function("stopAutoScroll",static_cast<void(cocos2d::ui::ScrollView::*)()>(&cocos2d::ui::ScrollView::stopAutoScroll));
mt.set_function("stopOverallScroll",static_cast<void(cocos2d::ui::ScrollView::*)()>(&cocos2d::ui::ScrollView::stopOverallScroll));
mt.set_function("scrollToBottom",static_cast<void(cocos2d::ui::ScrollView::*)(float,bool)>(&cocos2d::ui::ScrollView::scrollToBottom));
mt.set_function("scrollToTop",static_cast<void(cocos2d::ui::ScrollView::*)(float,bool)>(&cocos2d::ui::ScrollView::scrollToTop));
mt.set_function("scrollToLeft",static_cast<void(cocos2d::ui::ScrollView::*)(float,bool)>(&cocos2d::ui::ScrollView::scrollToLeft));
mt.set_function("scrollToRight",static_cast<void(cocos2d::ui::ScrollView::*)(float,bool)>(&cocos2d::ui::ScrollView::scrollToRight));
mt.set_function("scrollToTopLeft",static_cast<void(cocos2d::ui::ScrollView::*)(float,bool)>(&cocos2d::ui::ScrollView::scrollToTopLeft));
mt.set_function("scrollToTopRight",static_cast<void(cocos2d::ui::ScrollView::*)(float,bool)>(&cocos2d::ui::ScrollView::scrollToTopRight));
mt.set_function("scrollToBottomLeft",static_cast<void(cocos2d::ui::ScrollView::*)(float,bool)>(&cocos2d::ui::ScrollView::scrollToBottomLeft));
mt.set_function("scrollToBottomRight",static_cast<void(cocos2d::ui::ScrollView::*)(float,bool)>(&cocos2d::ui::ScrollView::scrollToBottomRight));
mt.set_function("scrollToPercentVertical",static_cast<void(cocos2d::ui::ScrollView::*)(float,float,bool)>(&cocos2d::ui::ScrollView::scrollToPercentVertical));
mt.set_function("scrollToPercentHorizontal",static_cast<void(cocos2d::ui::ScrollView::*)(float,float,bool)>(&cocos2d::ui::ScrollView::scrollToPercentHorizontal));
mt.set_function("scrollToPercentBothDirection",static_cast<void(cocos2d::ui::ScrollView::*)(const cocos2d::Vec2&,float,bool)>(&cocos2d::ui::ScrollView::scrollToPercentBothDirection));
mt.set_function("getScrolledPercentVertical",static_cast<float(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getScrolledPercentVertical));
mt.set_function("getScrolledPercentHorizontal",static_cast<float(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getScrolledPercentHorizontal));
mt.set_function("getScrolledPercentBothDirection",static_cast<cocos2d::Vec2(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getScrolledPercentBothDirection));
mt.set_function("jumpToBottom",static_cast<void(cocos2d::ui::ScrollView::*)()>(&cocos2d::ui::ScrollView::jumpToBottom));
mt.set_function("jumpToTop",static_cast<void(cocos2d::ui::ScrollView::*)()>(&cocos2d::ui::ScrollView::jumpToTop));
mt.set_function("jumpToLeft",static_cast<void(cocos2d::ui::ScrollView::*)()>(&cocos2d::ui::ScrollView::jumpToLeft));
mt.set_function("jumpToRight",static_cast<void(cocos2d::ui::ScrollView::*)()>(&cocos2d::ui::ScrollView::jumpToRight));
mt.set_function("jumpToTopLeft",static_cast<void(cocos2d::ui::ScrollView::*)()>(&cocos2d::ui::ScrollView::jumpToTopLeft));
mt.set_function("jumpToTopRight",static_cast<void(cocos2d::ui::ScrollView::*)()>(&cocos2d::ui::ScrollView::jumpToTopRight));
mt.set_function("jumpToBottomLeft",static_cast<void(cocos2d::ui::ScrollView::*)()>(&cocos2d::ui::ScrollView::jumpToBottomLeft));
mt.set_function("jumpToBottomRight",static_cast<void(cocos2d::ui::ScrollView::*)()>(&cocos2d::ui::ScrollView::jumpToBottomRight));
mt.set_function("jumpToPercentVertical",static_cast<void(cocos2d::ui::ScrollView::*)(float)>(&cocos2d::ui::ScrollView::jumpToPercentVertical));
mt.set_function("jumpToPercentHorizontal",static_cast<void(cocos2d::ui::ScrollView::*)(float)>(&cocos2d::ui::ScrollView::jumpToPercentHorizontal));
mt.set_function("jumpToPercentBothDirection",static_cast<void(cocos2d::ui::ScrollView::*)(const cocos2d::Vec2&)>(&cocos2d::ui::ScrollView::jumpToPercentBothDirection));
mt.set_function("setInnerContainerSize",static_cast<void(cocos2d::ui::ScrollView::*)(const cocos2d::Size&)>(&cocos2d::ui::ScrollView::setInnerContainerSize));
mt.set_function("getInnerContainerSize",static_cast<const cocos2d::Size&(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getInnerContainerSize));
mt.set_function("setInnerContainerPosition",static_cast<void(cocos2d::ui::ScrollView::*)(const cocos2d::Vec2&)>(&cocos2d::ui::ScrollView::setInnerContainerPosition));
mt.set_function("getInnerContainerPosition",static_cast<const cocos2d::Vec2&(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getInnerContainerPosition));
mt.set_function("addEventListener",static_cast<void(cocos2d::ui::ScrollView::*)(const std::function<void (cocos2d::Ref *, cocos2d::ui::ScrollView::EventType)>&)>(&cocos2d::ui::ScrollView::addEventListener));
mt.set_function("addChild",sol::overload(static_cast<void(cocos2d::ui::ScrollView::*)(cocos2d::Node*,int)>(&cocos2d::ui::ScrollView::addChild),static_cast<void(cocos2d::ui::ScrollView::*)(cocos2d::Node*)>(&cocos2d::ui::ScrollView::addChild),static_cast<void(cocos2d::ui::ScrollView::*)(cocos2d::Node*,int,int)>(&cocos2d::ui::ScrollView::addChild),static_cast<void(cocos2d::ui::ScrollView::*)(cocos2d::Node*,int,const std::string&)>(&cocos2d::ui::ScrollView::addChild)));
mt.set_function("removeAllChildren",static_cast<void(cocos2d::ui::ScrollView::*)()>(&cocos2d::ui::ScrollView::removeAllChildren));
mt.set_function("removeAllChildrenWithCleanup",static_cast<void(cocos2d::ui::ScrollView::*)(bool)>(&cocos2d::ui::ScrollView::removeAllChildrenWithCleanup));
mt.set_function("removeChild",sol::overload([](cocos2d::ui::ScrollView* obj,cocos2d::Node* arg0){return obj->removeChild(arg0);},[](cocos2d::ui::ScrollView* obj,cocos2d::Node* arg0,bool arg1){return obj->removeChild(arg0,arg1);}));
mt.set_function("getChildren",sol::overload(static_cast<const cocos2d::Vector<cocos2d::Node *>&(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getChildren),static_cast<cocos2d::Vector<cocos2d::Node *>&(cocos2d::ui::ScrollView::*)()>(&cocos2d::ui::ScrollView::getChildren)));
mt.set_function("getChildrenCount",static_cast<ssize_t(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getChildrenCount));
mt.set_function("getChildByTag",static_cast<cocos2d::Node*(cocos2d::ui::ScrollView::*)(int)const>(&cocos2d::ui::ScrollView::getChildByTag));
mt.set_function("getChildByName",static_cast<cocos2d::Node*(cocos2d::ui::ScrollView::*)(const std::string&)const>(&cocos2d::ui::ScrollView::getChildByName));
mt.set_function("onTouchBegan",static_cast<bool(cocos2d::ui::ScrollView::*)(cocos2d::Touch*,cocos2d::Event*)>(&cocos2d::ui::ScrollView::onTouchBegan));
mt.set_function("onTouchMoved",static_cast<void(cocos2d::ui::ScrollView::*)(cocos2d::Touch*,cocos2d::Event*)>(&cocos2d::ui::ScrollView::onTouchMoved));
mt.set_function("onTouchEnded",static_cast<void(cocos2d::ui::ScrollView::*)(cocos2d::Touch*,cocos2d::Event*)>(&cocos2d::ui::ScrollView::onTouchEnded));
mt.set_function("onTouchCancelled",static_cast<void(cocos2d::ui::ScrollView::*)(cocos2d::Touch*,cocos2d::Event*)>(&cocos2d::ui::ScrollView::onTouchCancelled));
mt.set_function("update",static_cast<void(cocos2d::ui::ScrollView::*)(float)>(&cocos2d::ui::ScrollView::update));
mt.set_function("setBounceEnabled",static_cast<void(cocos2d::ui::ScrollView::*)(bool)>(&cocos2d::ui::ScrollView::setBounceEnabled));
mt.set_function("isBounceEnabled",static_cast<bool(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::isBounceEnabled));
mt.set_function("setInertiaScrollEnabled",static_cast<void(cocos2d::ui::ScrollView::*)(bool)>(&cocos2d::ui::ScrollView::setInertiaScrollEnabled));
mt.set_function("isInertiaScrollEnabled",static_cast<bool(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::isInertiaScrollEnabled));
mt.set_function("setScrollBarEnabled",static_cast<void(cocos2d::ui::ScrollView::*)(bool)>(&cocos2d::ui::ScrollView::setScrollBarEnabled));
mt.set_function("isScrollBarEnabled",static_cast<bool(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::isScrollBarEnabled));
mt.set_function("setScrollBarPositionFromCorner",static_cast<void(cocos2d::ui::ScrollView::*)(const cocos2d::Vec2&)>(&cocos2d::ui::ScrollView::setScrollBarPositionFromCorner));
mt.set_function("setScrollBarPositionFromCornerForVertical",static_cast<void(cocos2d::ui::ScrollView::*)(const cocos2d::Vec2&)>(&cocos2d::ui::ScrollView::setScrollBarPositionFromCornerForVertical));
mt.set_function("getScrollBarPositionFromCornerForVertical",static_cast<cocos2d::Vec2(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getScrollBarPositionFromCornerForVertical));
mt.set_function("setScrollBarPositionFromCornerForHorizontal",static_cast<void(cocos2d::ui::ScrollView::*)(const cocos2d::Vec2&)>(&cocos2d::ui::ScrollView::setScrollBarPositionFromCornerForHorizontal));
mt.set_function("getScrollBarPositionFromCornerForHorizontal",static_cast<cocos2d::Vec2(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getScrollBarPositionFromCornerForHorizontal));
mt.set_function("setScrollBarWidth",static_cast<void(cocos2d::ui::ScrollView::*)(float)>(&cocos2d::ui::ScrollView::setScrollBarWidth));
mt.set_function("getScrollBarWidth",static_cast<float(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getScrollBarWidth));
mt.set_function("setScrollBarColor",static_cast<void(cocos2d::ui::ScrollView::*)(const cocos2d::Color3B&)>(&cocos2d::ui::ScrollView::setScrollBarColor));
mt.set_function("getScrollBarColor",static_cast<const cocos2d::Color3B&(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getScrollBarColor));
mt.set_function("setScrollBarOpacity",static_cast<void(cocos2d::ui::ScrollView::*)(uint8_t)>(&cocos2d::ui::ScrollView::setScrollBarOpacity));
mt.set_function("getScrollBarOpacity",static_cast<uint8_t(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getScrollBarOpacity));
mt.set_function("setScrollBarAutoHideEnabled",static_cast<void(cocos2d::ui::ScrollView::*)(bool)>(&cocos2d::ui::ScrollView::setScrollBarAutoHideEnabled));
mt.set_function("isScrollBarAutoHideEnabled",static_cast<bool(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::isScrollBarAutoHideEnabled));
mt.set_function("setScrollBarAutoHideTime",static_cast<void(cocos2d::ui::ScrollView::*)(float)>(&cocos2d::ui::ScrollView::setScrollBarAutoHideTime));
mt.set_function("getScrollBarAutoHideTime",static_cast<float(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getScrollBarAutoHideTime));
mt.set_function("setTouchTotalTimeThreshold",static_cast<void(cocos2d::ui::ScrollView::*)(float)>(&cocos2d::ui::ScrollView::setTouchTotalTimeThreshold));
mt.set_function("getTouchTotalTimeThreshold",static_cast<float(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getTouchTotalTimeThreshold));
mt.set_function("setLayoutType",static_cast<void(cocos2d::ui::ScrollView::*)(cocos2d::ui::Layout::Type)>(&cocos2d::ui::ScrollView::setLayoutType));
mt.set_function("getLayoutType",static_cast<cocos2d::ui::Layout::Type(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getLayoutType));
mt.set_function("getDescription",static_cast<std::string(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::getDescription));
mt.set_function("onEnter",static_cast<void(cocos2d::ui::ScrollView::*)()>(&cocos2d::ui::ScrollView::onEnter));
mt.set_function("onExit",static_cast<void(cocos2d::ui::ScrollView::*)()>(&cocos2d::ui::ScrollView::onExit));
mt.set_function("findNextFocusedWidget",static_cast<cocos2d::ui::Widget*(cocos2d::ui::ScrollView::*)(cocos2d::ui::Widget::FocusDirection,cocos2d::ui::Widget*)>(&cocos2d::ui::ScrollView::findNextFocusedWidget));
mt.set_function("isScrolling",static_cast<bool(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::isScrolling));
mt.set_function("isAutoScrolling",static_cast<bool(cocos2d::ui::ScrollView::*)()const>(&cocos2d::ui::ScrollView::isAutoScrolling));
mt.set_function("createInstance",static_cast<cocos2d::Ref*(*)()>(&cocos2d::ui::ScrollView::createInstance));
mt.set_function(sol::meta_function::construct,static_cast<cocos2d::ui::ScrollView*(*)()>(&cocos2d::ui::ScrollView::create));
RegisterLuaUIScrollViewDirectionAuto(lua);
RegisterLuaUIScrollViewEventTypeAuto(lua);
}
void RegisterLuaUIListViewGravityAuto(cocos2d::Lua& lua) {
sol::table pTable = lua["ccui"];
pTable = pTable["ListView"];
pTable.new_enum("Gravity"
,"LEFT",0
,"RIGHT",1
,"CENTER_HORIZONTAL",2
,"TOP",3
,"BOTTOM",4
,"CENTER_VERTICAL",5
);}
void RegisterLuaUIListViewEventTypeAuto(cocos2d::Lua& lua) {
sol::table pTable = lua["ccui"];
pTable = pTable["ListView"];
pTable.new_enum("EventType"
,"ON_SELECTED_ITEM_START",0
,"ON_SELECTED_ITEM_END",1
);}
void RegisterLuaUIListViewMagneticTypeAuto(cocos2d::Lua& lua) {
sol::table pTable = lua["ccui"];
pTable = pTable["ListView"];
pTable.new_enum("MagneticType"
,"NONE",0
,"CENTER",1
,"BOTH_END",2
,"LEFT",3
,"RIGHT",4
,"TOP",5
,"BOTTOM",6
);}
void RegisterLuaUIListViewAuto(cocos2d::Lua& lua){
sol::table ns = lua["ccui"];
auto mt=lua.NewUserType<cocos2d::ui::ListView,cocos2d::ui::ScrollView,cocos2d::ui::Layout,cocos2d::ui::Widget,cocos2d::ProtectedNode,cocos2d::Node,cocos2d::Ref,cocos2d::LuaObject,cocos2d::ui::LayoutParameterProtocol,cocos2d::ui::LayoutProtocol>("ListView",false);
ns["ListView"] = mt;
lua["ListView"] = sol::nil;
mt.set_function("setItemModel",static_cast<void(cocos2d::ui::ListView::*)(cocos2d::ui::Widget*)>(&cocos2d::ui::ListView::setItemModel));
mt.set_function("pushBackDefaultItem",static_cast<void(cocos2d::ui::ListView::*)()>(&cocos2d::ui::ListView::pushBackDefaultItem));
mt.set_function("insertDefaultItem",static_cast<void(cocos2d::ui::ListView::*)(ssize_t)>(&cocos2d::ui::ListView::insertDefaultItem));
mt.set_function("pushBackCustomItem",static_cast<void(cocos2d::ui::ListView::*)(cocos2d::ui::Widget*)>(&cocos2d::ui::ListView::pushBackCustomItem));
mt.set_function("insertCustomItem",static_cast<void(cocos2d::ui::ListView::*)(cocos2d::ui::Widget*,ssize_t)>(&cocos2d::ui::ListView::insertCustomItem));
mt.set_function("removeLastItem",static_cast<void(cocos2d::ui::ListView::*)()>(&cocos2d::ui::ListView::removeLastItem));
mt.set_function("removeItem",static_cast<void(cocos2d::ui::ListView::*)(ssize_t)>(&cocos2d::ui::ListView::removeItem));
mt.set_function("removeAllItems",static_cast<void(cocos2d::ui::ListView::*)()>(&cocos2d::ui::ListView::removeAllItems));
mt.set_function("getItem",static_cast<cocos2d::ui::Widget*(cocos2d::ui::ListView::*)(ssize_t)const>(&cocos2d::ui::ListView::getItem));
mt.set_function("getItems",static_cast<cocos2d::Vector<cocos2d::ui::Widget *>&(cocos2d::ui::ListView::*)()>(&cocos2d::ui::ListView::getItems));
mt.set_function("getIndex",static_cast<ssize_t(cocos2d::ui::ListView::*)(cocos2d::ui::Widget*)const>(&cocos2d::ui::ListView::getIndex));
mt.set_function("setGravity",static_cast<void(cocos2d::ui::ListView::*)(cocos2d::ui::ListView::Gravity)>(&cocos2d::ui::ListView::setGravity));
mt.set_function("setMagneticType",static_cast<void(cocos2d::ui::ListView::*)(cocos2d::ui::ListView::MagneticType)>(&cocos2d::ui::ListView::setMagneticType));
mt.set_function("getMagneticType",static_cast<cocos2d::ui::ListView::MagneticType(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getMagneticType));
mt.set_function("setMagneticAllowedOutOfBoundary",static_cast<void(cocos2d::ui::ListView::*)(bool)>(&cocos2d::ui::ListView::setMagneticAllowedOutOfBoundary));
mt.set_function("getMagneticAllowedOutOfBoundary",static_cast<bool(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getMagneticAllowedOutOfBoundary));
mt.set_function("setItemsMargin",static_cast<void(cocos2d::ui::ListView::*)(float)>(&cocos2d::ui::ListView::setItemsMargin));
mt.set_function("getItemsMargin",static_cast<float(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getItemsMargin));
mt.set_function("setPadding",static_cast<void(cocos2d::ui::ListView::*)(float,float,float,float)>(&cocos2d::ui::ListView::setPadding));
mt.set_function("setLeftPadding",static_cast<void(cocos2d::ui::ListView::*)(float)>(&cocos2d::ui::ListView::setLeftPadding));
mt.set_function("setTopPadding",static_cast<void(cocos2d::ui::ListView::*)(float)>(&cocos2d::ui::ListView::setTopPadding));
mt.set_function("setRightPadding",static_cast<void(cocos2d::ui::ListView::*)(float)>(&cocos2d::ui::ListView::setRightPadding));
mt.set_function("setBottomPadding",static_cast<void(cocos2d::ui::ListView::*)(float)>(&cocos2d::ui::ListView::setBottomPadding));
mt.set_function("getLeftPadding",static_cast<float(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getLeftPadding));
mt.set_function("getTopPadding",static_cast<float(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getTopPadding));
mt.set_function("getRightPadding",static_cast<float(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getRightPadding));
mt.set_function("getBottomPadding",static_cast<float(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getBottomPadding));
mt.set_function("setScrollDuration",static_cast<void(cocos2d::ui::ListView::*)(float)>(&cocos2d::ui::ListView::setScrollDuration));
mt.set_function("getScrollDuration",static_cast<float(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getScrollDuration));
mt.set_function("doLayout",static_cast<void(cocos2d::ui::ListView::*)()>(&cocos2d::ui::ListView::doLayout));
mt.set_function("requestDoLayout",static_cast<void(cocos2d::ui::ListView::*)()>(&cocos2d::ui::ListView::requestDoLayout));
mt.set_function("addChild",sol::overload(static_cast<void(cocos2d::ui::ListView::*)(cocos2d::Node*,int)>(&cocos2d::ui::ListView::addChild),static_cast<void(cocos2d::ui::ListView::*)(cocos2d::Node*)>(&cocos2d::ui::ListView::addChild),static_cast<void(cocos2d::ui::ListView::*)(cocos2d::Node*,int,int)>(&cocos2d::ui::ListView::addChild),static_cast<void(cocos2d::ui::ListView::*)(cocos2d::Node*,int,const std::string&)>(&cocos2d::ui::ListView::addChild)));
mt.set_function("removeAllChildren",static_cast<void(cocos2d::ui::ListView::*)()>(&cocos2d::ui::ListView::removeAllChildren));
mt.set_function("removeAllChildrenWithCleanup",static_cast<void(cocos2d::ui::ListView::*)(bool)>(&cocos2d::ui::ListView::removeAllChildrenWithCleanup));
mt.set_function("removeChild",sol::overload([](cocos2d::ui::ListView* obj,cocos2d::Node* arg0){return obj->removeChild(arg0);},[](cocos2d::ui::ListView* obj,cocos2d::Node* arg0,bool arg1){return obj->removeChild(arg0,arg1);}));
mt.set_function("getClosestItemToPosition",static_cast<cocos2d::ui::Widget*(cocos2d::ui::ListView::*)(const cocos2d::Vec2&,const cocos2d::Vec2&)const>(&cocos2d::ui::ListView::getClosestItemToPosition));
mt.set_function("getClosestItemToPositionInCurrentView",static_cast<cocos2d::ui::Widget*(cocos2d::ui::ListView::*)(const cocos2d::Vec2&,const cocos2d::Vec2&)const>(&cocos2d::ui::ListView::getClosestItemToPositionInCurrentView));
mt.set_function("getCenterItemInCurrentView",static_cast<cocos2d::ui::Widget*(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getCenterItemInCurrentView));
mt.set_function("getLeftmostItemInCurrentView",static_cast<cocos2d::ui::Widget*(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getLeftmostItemInCurrentView));
mt.set_function("getRightmostItemInCurrentView",static_cast<cocos2d::ui::Widget*(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getRightmostItemInCurrentView));
mt.set_function("getTopmostItemInCurrentView",static_cast<cocos2d::ui::Widget*(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getTopmostItemInCurrentView));
mt.set_function("getBottommostItemInCurrentView",static_cast<cocos2d::ui::Widget*(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getBottommostItemInCurrentView));
mt.set_function("jumpToBottom",static_cast<void(cocos2d::ui::ListView::*)()>(&cocos2d::ui::ListView::jumpToBottom));
mt.set_function("jumpToTop",static_cast<void(cocos2d::ui::ListView::*)()>(&cocos2d::ui::ListView::jumpToTop));
mt.set_function("jumpToLeft",static_cast<void(cocos2d::ui::ListView::*)()>(&cocos2d::ui::ListView::jumpToLeft));
mt.set_function("jumpToRight",static_cast<void(cocos2d::ui::ListView::*)()>(&cocos2d::ui::ListView::jumpToRight));
mt.set_function("jumpToTopLeft",static_cast<void(cocos2d::ui::ListView::*)()>(&cocos2d::ui::ListView::jumpToTopLeft));
mt.set_function("jumpToTopRight",static_cast<void(cocos2d::ui::ListView::*)()>(&cocos2d::ui::ListView::jumpToTopRight));
mt.set_function("jumpToBottomLeft",static_cast<void(cocos2d::ui::ListView::*)()>(&cocos2d::ui::ListView::jumpToBottomLeft));
mt.set_function("jumpToBottomRight",static_cast<void(cocos2d::ui::ListView::*)()>(&cocos2d::ui::ListView::jumpToBottomRight));
mt.set_function("jumpToPercentVertical",static_cast<void(cocos2d::ui::ListView::*)(float)>(&cocos2d::ui::ListView::jumpToPercentVertical));
mt.set_function("jumpToPercentHorizontal",static_cast<void(cocos2d::ui::ListView::*)(float)>(&cocos2d::ui::ListView::jumpToPercentHorizontal));
mt.set_function("jumpToPercentBothDirection",static_cast<void(cocos2d::ui::ListView::*)(const cocos2d::Vec2&)>(&cocos2d::ui::ListView::jumpToPercentBothDirection));
mt.set_function("jumpToItem",static_cast<void(cocos2d::ui::ListView::*)(ssize_t,const cocos2d::Vec2&,const cocos2d::Vec2&)>(&cocos2d::ui::ListView::jumpToItem));
mt.set_function("scrollToItem",sol::overload(static_cast<void(cocos2d::ui::ListView::*)(ssize_t,const cocos2d::Vec2&,const cocos2d::Vec2&,float)>(&cocos2d::ui::ListView::scrollToItem),static_cast<void(cocos2d::ui::ListView::*)(ssize_t,const cocos2d::Vec2&,const cocos2d::Vec2&)>(&cocos2d::ui::ListView::scrollToItem)));
mt.set_function("getCurSelectedIndex",static_cast<ssize_t(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getCurSelectedIndex));
mt.set_function("setCurSelectedIndex",static_cast<void(cocos2d::ui::ListView::*)(int)>(&cocos2d::ui::ListView::setCurSelectedIndex));
mt.set_function("addEventListener",static_cast<void(cocos2d::ui::ListView::*)(const std::function<void (cocos2d::Ref *, cocos2d::ui::ListView::EventType)>&)>(&cocos2d::ui::ListView::addEventListener));
mt.set_function("setDirection",static_cast<void(cocos2d::ui::ListView::*)(cocos2d::ui::ScrollView::Direction)>(&cocos2d::ui::ListView::setDirection));
mt.set_function("getDescription",static_cast<std::string(cocos2d::ui::ListView::*)()const>(&cocos2d::ui::ListView::getDescription));
mt.set_function("createInstance",static_cast<cocos2d::Ref*(*)()>(&cocos2d::ui::ListView::createInstance));
mt.set_function(sol::meta_function::construct,static_cast<cocos2d::ui::ListView*(*)()>(&cocos2d::ui::ListView::create));
RegisterLuaUIListViewGravityAuto(lua);
RegisterLuaUIListViewEventTypeAuto(lua);
RegisterLuaUIListViewMagneticTypeAuto(lua);
}
void RegisterLuaUISliderEventTypeAuto(cocos2d::Lua& lua) {
sol::table pTable = lua["ccui"];
pTable = pTable["Slider"];
pTable.new_enum("EventType"
,"ON_PERCENTAGE_CHANGED",0
,"ON_SLIDEBALL_DOWN",1
,"ON_SLIDEBALL_UP",2
,"ON_SLIDEBALL_CANCEL",3
);}
void RegisterLuaUISliderAuto(cocos2d::Lua& lua){
sol::table ns = lua["ccui"];
auto mt=lua.NewUserType<cocos2d::ui::Slider,cocos2d::ui::Widget,cocos2d::ProtectedNode,cocos2d::Node,cocos2d::Ref,cocos2d::LuaObject,cocos2d::ui::LayoutParameterProtocol>("Slider",false);
ns["Slider"] = mt;
lua["Slider"] = sol::nil;
mt.set_function("loadBarTexture",sol::overload([](cocos2d::ui::Slider* obj,const std::string& arg0){return obj->loadBarTexture(arg0);},[](cocos2d::ui::Slider* obj,const std::string& arg0,cocos2d::ui::Widget::TextureResType arg1){return obj->loadBarTexture(arg0,arg1);}));
mt.set_function("setScale9Enabled",static_cast<void(cocos2d::ui::Slider::*)(bool)>(&cocos2d::ui::Slider::setScale9Enabled));
mt.set_function("isScale9Enabled",static_cast<bool(cocos2d::ui::Slider::*)()const>(&cocos2d::ui::Slider::isScale9Enabled));
mt.set_function("setCapInsets",static_cast<void(cocos2d::ui::Slider::*)(const cocos2d::Rect&)>(&cocos2d::ui::Slider::setCapInsets));
mt.set_function("setCapInsetsBarRenderer",static_cast<void(cocos2d::ui::Slider::*)(const cocos2d::Rect&)>(&cocos2d::ui::Slider::setCapInsetsBarRenderer));
mt.set_function("getCapInsetsBarRenderer",static_cast<const cocos2d::Rect&(cocos2d::ui::Slider::*)()const>(&cocos2d::ui::Slider::getCapInsetsBarRenderer));
mt.set_function("setCapInsetProgressBarRenderer",static_cast<void(cocos2d::ui::Slider::*)(const cocos2d::Rect&)>(&cocos2d::ui::Slider::setCapInsetProgressBarRenderer));
mt.set_function("getCapInsetsProgressBarRenderer",static_cast<const cocos2d::Rect&(cocos2d::ui::Slider::*)()const>(&cocos2d::ui::Slider::getCapInsetsProgressBarRenderer));
mt.set_function("loadSlidBallTextures",sol::overload([](cocos2d::ui::Slider* obj,const std::string& arg0){return obj->loadSlidBallTextures(arg0);},[](cocos2d::ui::Slider* obj,const std::string& arg0,const std::string& arg1){return obj->loadSlidBallTextures(arg0,arg1);},[](cocos2d::ui::Slider* obj,const std::string& arg0,const std::string& arg1,const std::string& arg2){return obj->loadSlidBallTextures(arg0,arg1,arg2);},[](cocos2d::ui::Slider* obj,const std::string& arg0,const std::string& arg1,const std::string& arg2,cocos2d::ui::Widget::TextureResType arg3){return obj->loadSlidBallTextures(arg0,arg1,arg2,arg3);}));
mt.set_function("loadSlidBallTextureNormal",sol::overload([](cocos2d::ui::Slider* obj,const std::string& arg0){return obj->loadSlidBallTextureNormal(arg0);},[](cocos2d::ui::Slider* obj,const std::string& arg0,cocos2d::ui::Widget::TextureResType arg1){return obj->loadSlidBallTextureNormal(arg0,arg1);}));
mt.set_function("loadSlidBallTexturePressed",sol::overload([](cocos2d::ui::Slider* obj,const std::string& arg0){return obj->loadSlidBallTexturePressed(arg0);},[](cocos2d::ui::Slider* obj,const std::string& arg0,cocos2d::ui::Widget::TextureResType arg1){return obj->loadSlidBallTexturePressed(arg0,arg1);}));
mt.set_function("loadSlidBallTextureDisabled",sol::overload([](cocos2d::ui::Slider* obj,const std::string& arg0){return obj->loadSlidBallTextureDisabled(arg0);},[](cocos2d::ui::Slider* obj,const std::string& arg0,cocos2d::ui::Widget::TextureResType arg1){return obj->loadSlidBallTextureDisabled(arg0,arg1);}));
mt.set_function("loadProgressBarTexture",sol::overload([](cocos2d::ui::Slider* obj,const std::string& arg0){return obj->loadProgressBarTexture(arg0);},[](cocos2d::ui::Slider* obj,const std::string& arg0,cocos2d::ui::Widget::TextureResType arg1){return obj->loadProgressBarTexture(arg0,arg1);}));
mt.set_function("setPercent",static_cast<void(cocos2d::ui::Slider::*)(int)>(&cocos2d::ui::Slider::setPercent));
mt.set_function("updateVisualSlider",static_cast<void(cocos2d::ui::Slider::*)()>(&cocos2d::ui::Slider::updateVisualSlider));
mt.set_function("getPercent",static_cast<int(cocos2d::ui::Slider::*)()const>(&cocos2d::ui::Slider::getPercent));
mt.set_function("setMaxPercent",static_cast<void(cocos2d::ui::Slider::*)(int)>(&cocos2d::ui::Slider::setMaxPercent));
mt.set_function("getMaxPercent",static_cast<int(cocos2d::ui::Slider::*)()const>(&cocos2d::ui::Slider::getMaxPercent));
mt.set_function("addEventListener",static_cast<void(cocos2d::ui::Slider::*)(const std::function<void (cocos2d::Ref *, cocos2d::ui::Slider::EventType)>&)>(&cocos2d::ui::Slider::addEventListener));
mt.set_function("onTouchBegan",static_cast<bool(cocos2d::ui::Slider::*)(cocos2d::Touch*,cocos2d::Event*)>(&cocos2d::ui::Slider::onTouchBegan));
mt.set_function("onTouchMoved",static_cast<void(cocos2d::ui::Slider::*)(cocos2d::Touch*,cocos2d::Event*)>(&cocos2d::ui::Slider::onTouchMoved));
mt.set_function("onTouchEnded",static_cast<void(cocos2d::ui::Slider::*)(cocos2d::Touch*,cocos2d::Event*)>(&cocos2d::ui::Slider::onTouchEnded));
mt.set_function("onTouchCancelled",static_cast<void(cocos2d::ui::Slider::*)(cocos2d::Touch*,cocos2d::Event*)>(&cocos2d::ui::Slider::onTouchCancelled));
mt.set_function("getVirtualRendererSize",static_cast<cocos2d::Size(cocos2d::ui::Slider::*)()const>(&cocos2d::ui::Slider::getVirtualRendererSize));
mt.set_function("getVirtualRenderer",static_cast<cocos2d::Node*(cocos2d::ui::Slider::*)()>(&cocos2d::ui::Slider::getVirtualRenderer));
mt.set_function("ignoreContentAdaptWithSize",static_cast<void(cocos2d::ui::Slider::*)(bool)>(&cocos2d::ui::Slider::ignoreContentAdaptWithSize));
mt.set_function("hitTest",static_cast<bool(cocos2d::ui::Slider::*)(const cocos2d::Vec2&,const cocos2d::Camera*,cocos2d::Vec3*)const>(&cocos2d::ui::Slider::hitTest));
mt.set_function("getDescription",static_cast<std::string(cocos2d::ui::Slider::*)()const>(&cocos2d::ui::Slider::getDescription));
mt.set_function("setZoomScale",static_cast<void(cocos2d::ui::Slider::*)(float)>(&cocos2d::ui::Slider::setZoomScale));
mt.set_function("getZoomScale",static_cast<float(cocos2d::ui::Slider::*)()const>(&cocos2d::ui::Slider::getZoomScale));
mt.set_function("getSlidBallNormalRenderer",static_cast<cocos2d::Sprite*(cocos2d::ui::Slider::*)()const>(&cocos2d::ui::Slider::getSlidBallNormalRenderer));
mt.set_function("getSlidBallPressedRenderer",static_cast<cocos2d::Sprite*(cocos2d::ui::Slider::*)()const>(&cocos2d::ui::Slider::getSlidBallPressedRenderer));
mt.set_function("getSlidBallDisabledRenderer",static_cast<cocos2d::Sprite*(cocos2d::ui::Slider::*)()const>(&cocos2d::ui::Slider::getSlidBallDisabledRenderer));
mt.set_function("getSlidBallRenderer",static_cast<cocos2d::Node*(cocos2d::ui::Slider::*)()const>(&cocos2d::ui::Slider::getSlidBallRenderer));
mt.set_function("getBackFile",static_cast<cocos2d::ResourceData(cocos2d::ui::Slider::*)()>(&cocos2d::ui::Slider::getBackFile));
mt.set_function("getProgressBarFile",static_cast<cocos2d::ResourceData(cocos2d::ui::Slider::*)()>(&cocos2d::ui::Slider::getProgressBarFile));
mt.set_function("getBallNormalFile",static_cast<cocos2d::ResourceData(cocos2d::ui::Slider::*)()>(&cocos2d::ui::Slider::getBallNormalFile));
mt.set_function("getBallPressedFile",static_cast<cocos2d::ResourceData(cocos2d::ui::Slider::*)()>(&cocos2d::ui::Slider::getBallPressedFile));
mt.set_function("getBallDisabledFile",static_cast<cocos2d::ResourceData(cocos2d::ui::Slider::*)()>(&cocos2d::ui::Slider::getBallDisabledFile));
mt.set_function("createInstance",static_cast<cocos2d::Ref*(*)()>(&cocos2d::ui::Slider::createInstance));
mt.set_function(sol::meta_function::construct,sol::overload([](cocos2d::ui::Slider* obj,const std::string& arg0,const std::string& arg1){return obj->create(arg0,arg1);},[](cocos2d::ui::Slider* obj,const std::string& arg0,const std::string& arg1,cocos2d::ui::Widget::TextureResType arg2){return obj->create(arg0,arg1,arg2);},static_cast<cocos2d::ui::Slider*(*)()>(&cocos2d::ui::Slider::create)));
RegisterLuaUISliderEventTypeAuto(lua);
}
void RegisterLuaUITextFieldEventTypeAuto(cocos2d::Lua& lua) {
sol::table pTable = lua["ccui"];
pTable = pTable["TextField"];
pTable.new_enum("EventType"
,"ATTACH_WITH_IME",0
,"DETACH_WITH_IME",1
,"INSERT_TEXT",2
,"DELETE_BACKWARD",3
);}
void RegisterLuaUITextFieldAuto(cocos2d::Lua& lua){
sol::table ns = lua["ccui"];
auto mt=lua.NewUserType<cocos2d::ui::TextField,cocos2d::ui::Widget,cocos2d::ProtectedNode,cocos2d::Node,cocos2d::Ref,cocos2d::LuaObject,cocos2d::ui::LayoutParameterProtocol>("TextField",false);
ns["TextField"] = mt;
lua["TextField"] = sol::nil;
mt.set_function("setTouchSize",static_cast<void(cocos2d::ui::TextField::*)(const cocos2d::Size&)>(&cocos2d::ui::TextField::setTouchSize));
mt.set_function("getTouchSize",static_cast<cocos2d::Size(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getTouchSize));
mt.set_function("setTouchAreaEnabled",static_cast<void(cocos2d::ui::TextField::*)(bool)>(&cocos2d::ui::TextField::setTouchAreaEnabled));
mt.set_function("hitTest",static_cast<bool(cocos2d::ui::TextField::*)(const cocos2d::Vec2&,const cocos2d::Camera*,cocos2d::Vec3*)const>(&cocos2d::ui::TextField::hitTest));
mt.set_function("setPlaceHolder",static_cast<void(cocos2d::ui::TextField::*)(const std::string&)>(&cocos2d::ui::TextField::setPlaceHolder));
mt.set_function("getPlaceHolder",static_cast<const std::string&(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getPlaceHolder));
mt.set_function("getPlaceHolderColor",static_cast<const cocos2d::Color4B&(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getPlaceHolderColor));
mt.set_function("setPlaceHolderColor",sol::overload(static_cast<void(cocos2d::ui::TextField::*)(const cocos2d::Color4B&)>(&cocos2d::ui::TextField::setPlaceHolderColor),static_cast<void(cocos2d::ui::TextField::*)(const cocos2d::Color3B&)>(&cocos2d::ui::TextField::setPlaceHolderColor)));
mt.set_function("getTextColor",static_cast<const cocos2d::Color4B&(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getTextColor));
mt.set_function("setTextColor",static_cast<void(cocos2d::ui::TextField::*)(const cocos2d::Color4B&)>(&cocos2d::ui::TextField::setTextColor));
mt.set_function("setFontSize",static_cast<void(cocos2d::ui::TextField::*)(int)>(&cocos2d::ui::TextField::setFontSize));
mt.set_function("getFontSize",static_cast<int(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getFontSize));
mt.set_function("setFontName",static_cast<void(cocos2d::ui::TextField::*)(const std::string&)>(&cocos2d::ui::TextField::setFontName));
mt.set_function("getFontName",static_cast<const std::string&(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getFontName));
mt.set_function("didNotSelectSelf",static_cast<void(cocos2d::ui::TextField::*)()>(&cocos2d::ui::TextField::didNotSelectSelf));
mt.set_function("setString",static_cast<void(cocos2d::ui::TextField::*)(const std::string&)>(&cocos2d::ui::TextField::setString));
mt.set_function("getString",static_cast<const std::string&(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getString));
mt.set_function("onTouchBegan",static_cast<bool(cocos2d::ui::TextField::*)(cocos2d::Touch*,cocos2d::Event*)>(&cocos2d::ui::TextField::onTouchBegan));
mt.set_function("setMaxLengthEnabled",static_cast<void(cocos2d::ui::TextField::*)(bool)>(&cocos2d::ui::TextField::setMaxLengthEnabled));
mt.set_function("isMaxLengthEnabled",static_cast<bool(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::isMaxLengthEnabled));
mt.set_function("setMaxLength",static_cast<void(cocos2d::ui::TextField::*)(int)>(&cocos2d::ui::TextField::setMaxLength));
mt.set_function("getMaxLength",static_cast<int(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getMaxLength));
mt.set_function("getStringLength",static_cast<int(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getStringLength));
mt.set_function("setPasswordEnabled",static_cast<void(cocos2d::ui::TextField::*)(bool)>(&cocos2d::ui::TextField::setPasswordEnabled));
mt.set_function("isPasswordEnabled",static_cast<bool(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::isPasswordEnabled));
mt.set_function("setPasswordStyleText",static_cast<void(cocos2d::ui::TextField::*)(const char*)>(&cocos2d::ui::TextField::setPasswordStyleText));
mt.set_function("getPasswordStyleText",static_cast<const char*(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getPasswordStyleText));
mt.set_function("update",static_cast<void(cocos2d::ui::TextField::*)(float)>(&cocos2d::ui::TextField::update));
mt.set_function("getAttachWithIME",static_cast<bool(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getAttachWithIME));
mt.set_function("setAttachWithIME",static_cast<void(cocos2d::ui::TextField::*)(bool)>(&cocos2d::ui::TextField::setAttachWithIME));
mt.set_function("getDetachWithIME",static_cast<bool(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getDetachWithIME));
mt.set_function("setDetachWithIME",static_cast<void(cocos2d::ui::TextField::*)(bool)>(&cocos2d::ui::TextField::setDetachWithIME));
mt.set_function("getInsertText",static_cast<bool(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getInsertText));
mt.set_function("setInsertText",static_cast<void(cocos2d::ui::TextField::*)(bool)>(&cocos2d::ui::TextField::setInsertText));
mt.set_function("getDeleteBackward",static_cast<bool(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getDeleteBackward));
mt.set_function("setDeleteBackward",static_cast<void(cocos2d::ui::TextField::*)(bool)>(&cocos2d::ui::TextField::setDeleteBackward));
mt.set_function("addEventListener",static_cast<void(cocos2d::ui::TextField::*)(const std::function<void (cocos2d::Ref *, cocos2d::ui::TextField::EventType)>&)>(&cocos2d::ui::TextField::addEventListener));
mt.set_function("getDescription",static_cast<std::string(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getDescription));
mt.set_function("getAutoRenderSize",static_cast<cocos2d::Size(cocos2d::ui::TextField::*)()>(&cocos2d::ui::TextField::getAutoRenderSize));
mt.set_function("getVirtualRendererSize",static_cast<cocos2d::Size(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getVirtualRendererSize));
mt.set_function("getVirtualRenderer",static_cast<cocos2d::Node*(cocos2d::ui::TextField::*)()>(&cocos2d::ui::TextField::getVirtualRenderer));
mt.set_function("onEnter",static_cast<void(cocos2d::ui::TextField::*)()>(&cocos2d::ui::TextField::onEnter));
mt.set_function("attachWithIME",static_cast<void(cocos2d::ui::TextField::*)()>(&cocos2d::ui::TextField::attachWithIME));
mt.set_function("setTextAreaSize",static_cast<void(cocos2d::ui::TextField::*)(const cocos2d::Size&)>(&cocos2d::ui::TextField::setTextAreaSize));
mt.set_function("setTextHorizontalAlignment",static_cast<void(cocos2d::ui::TextField::*)(cocos2d::TextHAlignment)>(&cocos2d::ui::TextField::setTextHorizontalAlignment));
mt.set_function("getTextHorizontalAlignment",static_cast<cocos2d::TextHAlignment(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getTextHorizontalAlignment));
mt.set_function("setTextVerticalAlignment",static_cast<void(cocos2d::ui::TextField::*)(cocos2d::TextVAlignment)>(&cocos2d::ui::TextField::setTextVerticalAlignment));
mt.set_function("getTextVerticalAlignment",static_cast<cocos2d::TextVAlignment(cocos2d::ui::TextField::*)()const>(&cocos2d::ui::TextField::getTextVerticalAlignment));
mt.set_function("setCursorEnabled",static_cast<void(cocos2d::ui::TextField::*)(bool)>(&cocos2d::ui::TextField::setCursorEnabled));
mt.set_function("setCursorChar",static_cast<void(cocos2d::ui::TextField::*)(char)>(&cocos2d::ui::TextField::setCursorChar));
mt.set_function("setCursorPosition",static_cast<void(cocos2d::ui::TextField::*)(size_t)>(&cocos2d::ui::TextField::setCursorPosition));
mt.set_function("setCursorFromPoint",static_cast<void(cocos2d::ui::TextField::*)(const cocos2d::Vec2&,const cocos2d::Camera*)>(&cocos2d::ui::TextField::setCursorFromPoint));
mt.set_function("createInstance",static_cast<cocos2d::Ref*(*)()>(&cocos2d::ui::TextField::createInstance));
mt.set_function(sol::meta_function::construct,sol::overload(static_cast<cocos2d::ui::TextField*(*)(const std::string&,const std::string&,int)>(&cocos2d::ui::TextField::create),static_cast<cocos2d::ui::TextField*(*)()>(&cocos2d::ui::TextField::create)));
RegisterLuaUITextFieldEventTypeAuto(lua);
}
void RegisterLuaUITextBMFontAuto(cocos2d::Lua& lua){
sol::table ns = lua["ccui"];
auto mt=lua.NewUserType<cocos2d::ui::TextBMFont,cocos2d::ui::Widget,cocos2d::ProtectedNode,cocos2d::Node,cocos2d::Ref,cocos2d::LuaObject,cocos2d::ui::LayoutParameterProtocol>("TextBMFont",false);
ns["TextBMFont"] = mt;
lua["TextBMFont"] = sol::nil;
mt.set_function("setFntFile",static_cast<void(cocos2d::ui::TextBMFont::*)(const std::string&)>(&cocos2d::ui::TextBMFont::setFntFile));
mt.set_function("setString",static_cast<void(cocos2d::ui::TextBMFont::*)(const std::string&)>(&cocos2d::ui::TextBMFont::setString));
mt.set_function("getString",static_cast<const std::string&(cocos2d::ui::TextBMFont::*)()const>(&cocos2d::ui::TextBMFont::getString));
mt.set_function("getStringLength",static_cast<ssize_t(cocos2d::ui::TextBMFont::*)()const>(&cocos2d::ui::TextBMFont::getStringLength));
mt.set_function("getVirtualRendererSize",static_cast<cocos2d::Size(cocos2d::ui::TextBMFont::*)()const>(&cocos2d::ui::TextBMFont::getVirtualRendererSize));
mt.set_function("getVirtualRenderer",static_cast<cocos2d::Node*(cocos2d::ui::TextBMFont::*)()>(&cocos2d::ui::TextBMFont::getVirtualRenderer));
mt.set_function("getDescription",static_cast<std::string(cocos2d::ui::TextBMFont::*)()const>(&cocos2d::ui::TextBMFont::getDescription));
mt.set_function("getRenderFile",static_cast<cocos2d::ResourceData(cocos2d::ui::TextBMFont::*)()>(&cocos2d::ui::TextBMFont::getRenderFile));
mt.set_function("resetRender",static_cast<void(cocos2d::ui::TextBMFont::*)()>(&cocos2d::ui::TextBMFont::resetRender));
mt.set_function("createInstance",static_cast<cocos2d::Ref*(*)()>(&cocos2d::ui::TextBMFont::createInstance));
mt.set_function(sol::meta_function::construct,sol::overload(static_cast<cocos2d::ui::TextBMFont*(*)(const std::string&,const std::string&)>(&cocos2d::ui::TextBMFont::create),static_cast<cocos2d::ui::TextBMFont*(*)()>(&cocos2d::ui::TextBMFont::create)));
}
void RegisterLuaUIPageViewEventTypeAuto(cocos2d::Lua& lua) {
sol::table pTable = lua["ccui"];
pTable = pTable["PageView"];
pTable.new_enum("EventType"
,"TURNING",0
);}
void RegisterLuaUIPageViewTouchDirectionAuto(cocos2d::Lua& lua) {
sol::table pTable = lua["ccui"];
pTable = pTable["PageView"];
pTable.new_enum("TouchDirection"
,"LEFT",0
,"RIGHT",1
,"UP",2
,"DOWN",3
);}
void RegisterLuaUIPageViewAuto(cocos2d::Lua& lua){
sol::table ns = lua["ccui"];
auto mt=lua.NewUserType<cocos2d::ui::PageView,cocos2d::ui::ListView,cocos2d::ui::ScrollView,cocos2d::ui::Layout,cocos2d::ui::Widget,cocos2d::ProtectedNode,cocos2d::Node,cocos2d::Ref,cocos2d::LuaObject,cocos2d::ui::LayoutParameterProtocol,cocos2d::ui::LayoutProtocol>("PageView",false);
ns["PageView"] = mt;
lua["PageView"] = sol::nil;
mt.set_function("setDirection",static_cast<void(cocos2d::ui::PageView::*)(cocos2d::ui::ScrollView::Direction)>(&cocos2d::ui::PageView::setDirection));
mt.set_function("addPage",static_cast<void(cocos2d::ui::PageView::*)(cocos2d::ui::Widget*)>(&cocos2d::ui::PageView::addPage));
mt.set_function("insertPage",static_cast<void(cocos2d::ui::PageView::*)(cocos2d::ui::Widget*,int)>(&cocos2d::ui::PageView::insertPage));
mt.set_function("removePage",static_cast<void(cocos2d::ui::PageView::*)(cocos2d::ui::Widget*)>(&cocos2d::ui::PageView::removePage));
mt.set_function("removePageAtIndex",static_cast<void(cocos2d::ui::PageView::*)(ssize_t)>(&cocos2d::ui::PageView::removePageAtIndex));
mt.set_function("removeAllPages",static_cast<void(cocos2d::ui::PageView::*)()>(&cocos2d::ui::PageView::removeAllPages));
mt.set_function("scrollToPage",sol::overload(static_cast<void(cocos2d::ui::PageView::*)(ssize_t,float)>(&cocos2d::ui::PageView::scrollToPage),static_cast<void(cocos2d::ui::PageView::*)(ssize_t)>(&cocos2d::ui::PageView::scrollToPage)));
mt.set_function("scrollToItem",sol::overload(static_cast<void(cocos2d::ui::PageView::*)(ssize_t,float)>(&cocos2d::ui::PageView::scrollToItem),static_cast<void(cocos2d::ui::PageView::*)(ssize_t)>(&cocos2d::ui::PageView::scrollToItem)));
mt.set_function("getCurrentPageIndex",static_cast<ssize_t(cocos2d::ui::PageView::*)()>(&cocos2d::ui::PageView::getCurrentPageIndex));
mt.set_function("setCurrentPageIndex",static_cast<void(cocos2d::ui::PageView::*)(ssize_t)>(&cocos2d::ui::PageView::setCurrentPageIndex));
mt.set_function("addEventListener",static_cast<void(cocos2d::ui::PageView::*)(const std::function<void (cocos2d::Ref *, cocos2d::ui::PageView::EventType)>&)>(&cocos2d::ui::PageView::addEventListener));
mt.set_function("getDescription",static_cast<std::string(cocos2d::ui::PageView::*)()const>(&cocos2d::ui::PageView::getDescription));
mt.set_function("setIndicatorEnabled",static_cast<void(cocos2d::ui::PageView::*)(bool)>(&cocos2d::ui::PageView::setIndicatorEnabled));
mt.set_function("getIndicatorEnabled",static_cast<bool(cocos2d::ui::PageView::*)()const>(&cocos2d::ui::PageView::getIndicatorEnabled));
mt.set_function("setIndicatorPositionAsAnchorPoint",static_cast<void(cocos2d::ui::PageView::*)(const cocos2d::Vec2&)>(&cocos2d::ui::PageView::setIndicatorPositionAsAnchorPoint));
mt.set_function("getIndicatorPositionAsAnchorPoint",static_cast<const cocos2d::Vec2&(cocos2d::ui::PageView::*)()const>(&cocos2d::ui::PageView::getIndicatorPositionAsAnchorPoint));
mt.set_function("setIndicatorPosition",static_cast<void(cocos2d::ui::PageView::*)(const cocos2d::Vec2&)>(&cocos2d::ui::PageView::setIndicatorPosition));
mt.set_function("getIndicatorPosition",static_cast<const cocos2d::Vec2&(cocos2d::ui::PageView::*)()const>(&cocos2d::ui::PageView::getIndicatorPosition));
mt.set_function("setIndicatorSpaceBetweenIndexNodes",static_cast<void(cocos2d::ui::PageView::*)(float)>(&cocos2d::ui::PageView::setIndicatorSpaceBetweenIndexNodes));
mt.set_function("getIndicatorSpaceBetweenIndexNodes",static_cast<float(cocos2d::ui::PageView::*)()const>(&cocos2d::ui::PageView::getIndicatorSpaceBetweenIndexNodes));
mt.set_function("setIndicatorSelectedIndexColor",static_cast<void(cocos2d::ui::PageView::*)(const cocos2d::Color3B&)>(&cocos2d::ui::PageView::setIndicatorSelectedIndexColor));
mt.set_function("getIndicatorSelectedIndexColor",static_cast<const cocos2d::Color3B&(cocos2d::ui::PageView::*)()const>(&cocos2d::ui::PageView::getIndicatorSelectedIndexColor));
mt.set_function("setIndicatorIndexNodesColor",static_cast<void(cocos2d::ui::PageView::*)(const cocos2d::Color3B&)>(&cocos2d::ui::PageView::setIndicatorIndexNodesColor));
mt.set_function("getIndicatorIndexNodesColor",static_cast<const cocos2d::Color3B&(cocos2d::ui::PageView::*)()const>(&cocos2d::ui::PageView::getIndicatorIndexNodesColor));
mt.set_function("setIndicatorSelectedIndexOpacity",static_cast<void(cocos2d::ui::PageView::*)(uint8_t)>(&cocos2d::ui::PageView::setIndicatorSelectedIndexOpacity));
mt.set_function("getIndicatorSelectedIndexOpacity",static_cast<uint8_t(cocos2d::ui::PageView::*)()const>(&cocos2d::ui::PageView::getIndicatorSelectedIndexOpacity));
mt.set_function("setIndicatorIndexNodesOpacity",static_cast<void(cocos2d::ui::PageView::*)(uint8_t)>(&cocos2d::ui::PageView::setIndicatorIndexNodesOpacity));
mt.set_function("getIndicatorIndexNodesOpacity",static_cast<uint8_t(cocos2d::ui::PageView::*)()const>(&cocos2d::ui::PageView::getIndicatorIndexNodesOpacity));
mt.set_function("setIndicatorIndexNodesScale",static_cast<void(cocos2d::ui::PageView::*)(float)>(&cocos2d::ui::PageView::setIndicatorIndexNodesScale));
mt.set_function("setIndicatorIndexNodesTexture",sol::overload([](cocos2d::ui::PageView* obj,const std::string& arg0){return obj->setIndicatorIndexNodesTexture(arg0);},[](cocos2d::ui::PageView* obj,const std::string& arg0,cocos2d::ui::Widget::TextureResType arg1){return obj->setIndicatorIndexNodesTexture(arg0,arg1);}));
mt.set_function("getIndicatorIndexNodesScale",static_cast<float(cocos2d::ui::PageView::*)()const>(&cocos2d::ui::PageView::getIndicatorIndexNodesScale));
mt.set_function("setAutoScrollStopEpsilon",static_cast<void(cocos2d::ui::PageView::*)(float)>(&cocos2d::ui::PageView::setAutoScrollStopEpsilon));
mt.set_function("createInstance",static_cast<cocos2d::Ref*(*)()>(&cocos2d::ui::PageView::createInstance));
mt.set_function(sol::meta_function::construct,static_cast<cocos2d::ui::PageView*(*)()>(&cocos2d::ui::PageView::create));
RegisterLuaUIPageViewEventTypeAuto(lua);
RegisterLuaUIPageViewTouchDirectionAuto(lua);
}
