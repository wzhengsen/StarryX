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
#include "network/CCConnection.h"
void RegisterLuaCoreMaterialAuto(cocos2d::extension::Lua& lua){
cocos2d::extension::Lua::Id2Meta[typeid(cocos2d::Material).name()] = sol::usertype_traits<cocos2d::Material*>::metatable();
auto dep=lua.new_usertype<cocos2d::Material>("deprecated.cocos2d::Material");
dep[sol::base_classes]=sol::bases<cocos2d::Ref,cocos2d::extension::LuaObject>();
sol::table mt=lua.NewClass(sol::usertype_traits<cocos2d::Material*>::metatable(),sol::usertype_traits<cocos2d::Ref*>::metatable());
lua["cc"]["Material"]=mt;
mt["__new__"] = [](){return nullptr;};
mt["static"]["CreateWithFilename"]=static_cast<cocos2d::Material*(*)(const std::string&)>(&cocos2d::Material::createWithFilename);
mt["static"]["CreateWithProgramState"]=static_cast<cocos2d::Material*(*)(cocos2d::backend::ProgramState*)>(&cocos2d::Material::createWithProgramState);
mt["static"]["CreateWithProperties"]=static_cast<cocos2d::Material*(*)(cocos2d::Properties*)>(&cocos2d::Material::createWithProperties);
mt["Draw"]=static_cast<void(cocos2d::Material::*)(cocos2d::MeshCommand*,float,cocos2d::backend::Buffer*,cocos2d::backend::Buffer*,cocos2d::CustomCommand::PrimitiveType,cocos2d::CustomCommand::IndexFormat,unsigned int,const cocos2d::Mat4&)>(&cocos2d::Material::draw);
mt["GetName"]=static_cast<std::string(cocos2d::Material::*)()const>(&cocos2d::Material::getName);
mt["get"]["Name"]=mt["GetName"];
mt["SetName"]=static_cast<void(cocos2d::Material::*)(const std::string&)>(&cocos2d::Material::setName);
mt["set"]["Name"]=mt["SetName"];
mt["GetTechniqueByName"]=static_cast<cocos2d::Technique*(cocos2d::Material::*)(const std::string&)>(&cocos2d::Material::getTechniqueByName);
mt["GetTechniqueByIndex"]=static_cast<cocos2d::Technique*(cocos2d::Material::*)(ssize_t)>(&cocos2d::Material::getTechniqueByIndex);
mt["GetTechnique"]=static_cast<cocos2d::Technique*(cocos2d::Material::*)()const>(&cocos2d::Material::getTechnique);
mt["get"]["Technique"]=mt["GetTechnique"];
mt["GetTechniques"]=static_cast<const cocos2d::Vector<cocos2d::Technique *>&(cocos2d::Material::*)()const>(&cocos2d::Material::getTechniques);
mt["get"]["Techniques"]=mt["GetTechniques"];
mt["GetTechniqueCount"]=static_cast<ssize_t(cocos2d::Material::*)()const>(&cocos2d::Material::getTechniqueCount);
mt["get"]["TechniqueCount"]=mt["GetTechniqueCount"];
mt["AddTechnique"]=static_cast<void(cocos2d::Material::*)(cocos2d::Technique*)>(&cocos2d::Material::addTechnique);
mt["SetTechnique"]=static_cast<void(cocos2d::Material::*)(const std::string&)>(&cocos2d::Material::setTechnique);
mt["set"]["Technique"]=mt["SetTechnique"];
mt["Clone"]=static_cast<cocos2d::Material*(cocos2d::Material::*)()const>(&cocos2d::Material::clone);
mt["GetStateBlock"]=static_cast<cocos2d::RenderState::StateBlock&(cocos2d::Material::*)()>(&cocos2d::Material::getStateBlock);
mt["get"]["StateBlock"]=mt["GetStateBlock"];
mt["SetStateBlock"]=static_cast<void(cocos2d::Material::*)(const cocos2d::RenderState::StateBlock&)>(&cocos2d::Material::setStateBlock);
mt["set"]["StateBlock"]=mt["SetStateBlock"];
mt["GetRenderState"]=static_cast<cocos2d::RenderState*(cocos2d::Material::*)()>(&cocos2d::Material::getRenderState);
mt["get"]["RenderState"]=mt["GetRenderState"];
}
void RegisterLuaCorePassAuto(cocos2d::extension::Lua& lua){
cocos2d::extension::Lua::Id2Meta[typeid(cocos2d::Pass).name()] = sol::usertype_traits<cocos2d::Pass*>::metatable();
auto dep=lua.new_usertype<cocos2d::Pass>("deprecated.cocos2d::Pass");
dep[sol::base_classes]=sol::bases<cocos2d::Ref,cocos2d::extension::LuaObject>();
sol::table mt=lua.NewClass(sol::usertype_traits<cocos2d::Pass*>::metatable(),sol::usertype_traits<cocos2d::Ref*>::metatable());
lua["cc"]["Pass"]=mt;
mt["static"]["CreateWithProgramState"]=static_cast<cocos2d::Pass*(*)(cocos2d::Technique*,cocos2d::backend::ProgramState*)>(&cocos2d::Pass::createWithProgramState);
mt["__new__"]=static_cast<cocos2d::Pass*(*)(cocos2d::Technique*)>(&cocos2d::Pass::create);
mt["GetProgramState"]=static_cast<cocos2d::backend::ProgramState*(cocos2d::Pass::*)()const>(&cocos2d::Pass::getProgramState);
mt["get"]["ProgramState"]=mt["GetProgramState"];
mt["Draw"]=static_cast<void(cocos2d::Pass::*)(cocos2d::MeshCommand*,float,cocos2d::backend::Buffer*,cocos2d::backend::Buffer*,cocos2d::CustomCommand::PrimitiveType,cocos2d::MeshCommand::IndexFormat,unsigned int,const cocos2d::Mat4&)>(&cocos2d::Pass::draw);
mt["SetVertexAttribBinding"]=static_cast<void(cocos2d::Pass::*)(cocos2d::VertexAttribBinding*)>(&cocos2d::Pass::setVertexAttribBinding);
mt["set"]["VertexAttribBinding"]=mt["SetVertexAttribBinding"];
mt["GetVertexAttributeBinding"]=static_cast<cocos2d::VertexAttribBinding*(cocos2d::Pass::*)()const>(&cocos2d::Pass::getVertexAttributeBinding);
mt["get"]["VertexAttributeBinding"]=mt["GetVertexAttributeBinding"];
mt["SetName"]=static_cast<void(cocos2d::Pass::*)(const std::string&)>(&cocos2d::Pass::setName);
mt["set"]["Name"]=mt["SetName"];
mt["GetName"]=static_cast<const std::string&(cocos2d::Pass::*)()const>(&cocos2d::Pass::getName);
mt["get"]["Name"]=mt["GetName"];
mt["GetStateBlock"]=static_cast<cocos2d::RenderState::StateBlock&(cocos2d::Pass::*)()>(&cocos2d::Pass::getStateBlock);
mt["get"]["StateBlock"]=mt["GetStateBlock"];
mt["Clone"]=static_cast<cocos2d::Pass*(cocos2d::Pass::*)()const>(&cocos2d::Pass::clone);
mt["SetTechnique"]=static_cast<void(cocos2d::Pass::*)(cocos2d::Technique*)>(&cocos2d::Pass::setTechnique);
mt["set"]["Technique"]=mt["SetTechnique"];
mt["UpdateMVPUniform"]=static_cast<void(cocos2d::Pass::*)(const cocos2d::Mat4&)>(&cocos2d::Pass::updateMVPUniform);
mt["SetUniformTexture"]=static_cast<void(cocos2d::Pass::*)(uint32_t,cocos2d::backend::TextureBackend*)>(&cocos2d::Pass::setUniformTexture);
mt["SetUniformNormTexture"]=static_cast<void(cocos2d::Pass::*)(uint32_t,cocos2d::backend::TextureBackend*)>(&cocos2d::Pass::setUniformNormTexture);
mt["SetUniformColor"]=static_cast<void(cocos2d::Pass::*)(const void*,size_t)>(&cocos2d::Pass::setUniformColor);
mt["SetUniformMatrixPalette"]=static_cast<void(cocos2d::Pass::*)(const void*,size_t)>(&cocos2d::Pass::setUniformMatrixPalette);
mt["SetUniformDirLightColor"]=static_cast<void(cocos2d::Pass::*)(const void*,size_t)>(&cocos2d::Pass::setUniformDirLightColor);
mt["SetUniformDirLightDir"]=static_cast<void(cocos2d::Pass::*)(const void*,size_t)>(&cocos2d::Pass::setUniformDirLightDir);
mt["SetUniformPointLightColor"]=static_cast<void(cocos2d::Pass::*)(const void*,size_t)>(&cocos2d::Pass::setUniformPointLightColor);
mt["SetUniformPointLightPosition"]=static_cast<void(cocos2d::Pass::*)(const void*,size_t)>(&cocos2d::Pass::setUniformPointLightPosition);
mt["SetUniformPointLightRangeInverse"]=static_cast<void(cocos2d::Pass::*)(const void*,size_t)>(&cocos2d::Pass::setUniformPointLightRangeInverse);
mt["SetUniformSpotLightColor"]=static_cast<void(cocos2d::Pass::*)(const void*,size_t)>(&cocos2d::Pass::setUniformSpotLightColor);
mt["SetUniformSpotLightPosition"]=static_cast<void(cocos2d::Pass::*)(const void*,size_t)>(&cocos2d::Pass::setUniformSpotLightPosition);
mt["SetUniformSpotLightDir"]=static_cast<void(cocos2d::Pass::*)(const void*,size_t)>(&cocos2d::Pass::setUniformSpotLightDir);
mt["SetUniformSpotLightInnerAngleCos"]=static_cast<void(cocos2d::Pass::*)(const void*,size_t)>(&cocos2d::Pass::setUniformSpotLightInnerAngleCos);
mt["SetUniformSpotLightOuterAngleCos"]=static_cast<void(cocos2d::Pass::*)(const void*,size_t)>(&cocos2d::Pass::setUniformSpotLightOuterAngleCos);
mt["SetUniformSpotLightRangeInverse"]=static_cast<void(cocos2d::Pass::*)(const void*,size_t)>(&cocos2d::Pass::setUniformSpotLightRangeInverse);
mt["SetUniformAmbientLigthColor"]=static_cast<void(cocos2d::Pass::*)(const void*,size_t)>(&cocos2d::Pass::setUniformAmbientLigthColor);
}
void RegisterLuaCoreRendererAuto(cocos2d::extension::Lua& lua){
cocos2d::extension::Lua::Id2Meta[typeid(cocos2d::Renderer).name()] = sol::usertype_traits<cocos2d::Renderer*>::metatable();
auto dep=lua.new_usertype<cocos2d::Renderer>("deprecated.cocos2d::Renderer");
sol::table mt=lua.NewClass(sol::usertype_traits<cocos2d::Renderer*>::metatable());
lua["cc"]["Renderer"]=mt;
mt["Init"]=static_cast<void(cocos2d::Renderer::*)()>(&cocos2d::Renderer::init);
mt["AddCommand"]=sol::overload(static_cast<void(cocos2d::Renderer::*)(cocos2d::RenderCommand*,int)>(&cocos2d::Renderer::addCommand),static_cast<void(cocos2d::Renderer::*)(cocos2d::RenderCommand*)>(&cocos2d::Renderer::addCommand));
mt["PushGroup"]=static_cast<void(cocos2d::Renderer::*)(int)>(&cocos2d::Renderer::pushGroup);
mt["PopGroup"]=static_cast<void(cocos2d::Renderer::*)()>(&cocos2d::Renderer::popGroup);
mt["CreateRenderQueue"]=static_cast<int(cocos2d::Renderer::*)()>(&cocos2d::Renderer::createRenderQueue);
mt["Render"]=static_cast<void(cocos2d::Renderer::*)()>(&cocos2d::Renderer::render);
mt["Clean"]=static_cast<void(cocos2d::Renderer::*)()>(&cocos2d::Renderer::clean);
mt["GetDrawnBatches"]=static_cast<ssize_t(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getDrawnBatches);
mt["get"]["DrawnBatches"]=mt["GetDrawnBatches"];
mt["AddDrawnBatches"]=static_cast<void(cocos2d::Renderer::*)(ssize_t)>(&cocos2d::Renderer::addDrawnBatches);
mt["GetDrawnVertices"]=static_cast<ssize_t(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getDrawnVertices);
mt["get"]["DrawnVertices"]=mt["GetDrawnVertices"];
mt["AddDrawnVertices"]=static_cast<void(cocos2d::Renderer::*)(ssize_t)>(&cocos2d::Renderer::addDrawnVertices);
mt["ClearDrawStats"]=static_cast<void(cocos2d::Renderer::*)()>(&cocos2d::Renderer::clearDrawStats);
mt["GetRenderTarget"]=static_cast<cocos2d::backend::RenderTarget*(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getRenderTarget);
mt["get"]["RenderTarget"]=mt["GetRenderTarget"];
mt["SetRenderTarget"]=static_cast<void(cocos2d::Renderer::*)(cocos2d::backend::RenderTarget*)>(&cocos2d::Renderer::setRenderTarget);
mt["set"]["RenderTarget"]=mt["SetRenderTarget"];
mt["GetDefaultRenderTarget"]=static_cast<cocos2d::backend::RenderTarget*(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getDefaultRenderTarget);
mt["get"]["DefaultRenderTarget"]=mt["GetDefaultRenderTarget"];
mt["Clear"]=static_cast<void(cocos2d::Renderer::*)(cocos2d::ClearFlag,const cocos2d::Color4F&,float,unsigned int,float)>(&cocos2d::Renderer::clear);
mt["GetClearColor"]=static_cast<const cocos2d::Color4F&(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getClearColor);
mt["get"]["ClearColor"]=mt["GetClearColor"];
mt["GetClearDepth"]=static_cast<float(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getClearDepth);
mt["get"]["ClearDepth"]=mt["GetClearDepth"];
mt["GetClearStencil"]=static_cast<unsigned int(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getClearStencil);
mt["get"]["ClearStencil"]=mt["GetClearStencil"];
mt["GetClearFlag"]=static_cast<cocos2d::ClearFlag(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getClearFlag);
mt["get"]["ClearFlag"]=mt["GetClearFlag"];
mt["GetRenderTargetFlag"]=static_cast<cocos2d::RenderTargetFlag(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getRenderTargetFlag);
mt["get"]["RenderTargetFlag"]=mt["GetRenderTargetFlag"];
mt["SetDepthTest"]=static_cast<void(cocos2d::Renderer::*)(bool)>(&cocos2d::Renderer::setDepthTest);
mt["set"]["DepthTest"]=mt["SetDepthTest"];
mt["SetDepthWrite"]=static_cast<void(cocos2d::Renderer::*)(bool)>(&cocos2d::Renderer::setDepthWrite);
mt["set"]["DepthWrite"]=mt["SetDepthWrite"];
mt["SetDepthCompareFunction"]=static_cast<void(cocos2d::Renderer::*)(cocos2d::backend::CompareFunction)>(&cocos2d::Renderer::setDepthCompareFunction);
mt["set"]["DepthCompareFunction"]=mt["SetDepthCompareFunction"];
mt["GetDepthTest"]=static_cast<bool(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getDepthTest);
mt["get"]["DepthTest"]=mt["GetDepthTest"];
mt["GetDepthWrite"]=static_cast<bool(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getDepthWrite);
mt["get"]["DepthWrite"]=mt["GetDepthWrite"];
mt["GetDepthCompareFunction"]=static_cast<cocos2d::backend::CompareFunction(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getDepthCompareFunction);
mt["get"]["DepthCompareFunction"]=mt["GetDepthCompareFunction"];
mt["SetStencilTest"]=static_cast<void(cocos2d::Renderer::*)(bool)>(&cocos2d::Renderer::setStencilTest);
mt["set"]["StencilTest"]=mt["SetStencilTest"];
mt["SetStencilCompareFunction"]=static_cast<void(cocos2d::Renderer::*)(cocos2d::backend::CompareFunction,unsigned int,unsigned int)>(&cocos2d::Renderer::setStencilCompareFunction);
mt["SetStencilOperation"]=static_cast<void(cocos2d::Renderer::*)(cocos2d::backend::StencilOperation,cocos2d::backend::StencilOperation,cocos2d::backend::StencilOperation)>(&cocos2d::Renderer::setStencilOperation);
mt["SetStencilWriteMask"]=static_cast<void(cocos2d::Renderer::*)(unsigned int)>(&cocos2d::Renderer::setStencilWriteMask);
mt["set"]["StencilWriteMask"]=mt["SetStencilWriteMask"];
mt["GetStencilTest"]=static_cast<bool(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getStencilTest);
mt["get"]["StencilTest"]=mt["GetStencilTest"];
mt["GetStencilFailureOperation"]=static_cast<cocos2d::backend::StencilOperation(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getStencilFailureOperation);
mt["get"]["StencilFailureOperation"]=mt["GetStencilFailureOperation"];
mt["GetStencilPassDepthFailureOperation"]=static_cast<cocos2d::backend::StencilOperation(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getStencilPassDepthFailureOperation);
mt["get"]["StencilPassDepthFailureOperation"]=mt["GetStencilPassDepthFailureOperation"];
mt["GetStencilDepthPassOperation"]=static_cast<cocos2d::backend::StencilOperation(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getStencilDepthPassOperation);
mt["get"]["StencilDepthPassOperation"]=mt["GetStencilDepthPassOperation"];
mt["GetStencilCompareFunction"]=static_cast<cocos2d::backend::CompareFunction(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getStencilCompareFunction);
mt["get"]["StencilCompareFunction"]=mt["GetStencilCompareFunction"];
mt["GetStencilReadMask"]=static_cast<unsigned int(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getStencilReadMask);
mt["get"]["StencilReadMask"]=mt["GetStencilReadMask"];
mt["GetStencilWriteMask"]=static_cast<unsigned int(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getStencilWriteMask);
mt["get"]["StencilWriteMask"]=mt["GetStencilWriteMask"];
mt["GetStencilReferenceValue"]=static_cast<unsigned int(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getStencilReferenceValue);
mt["get"]["StencilReferenceValue"]=mt["GetStencilReferenceValue"];
mt["SetDepthStencilDesc"]=static_cast<void(cocos2d::Renderer::*)(const cocos2d::backend::DepthStencilDescriptor&)>(&cocos2d::Renderer::setDepthStencilDesc);
mt["set"]["DepthStencilDesc"]=mt["SetDepthStencilDesc"];
mt["GetDepthStencilDesc"]=static_cast<const cocos2d::backend::DepthStencilDescriptor&(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getDepthStencilDesc);
mt["get"]["DepthStencilDesc"]=mt["GetDepthStencilDesc"];
mt["SetCullMode"]=static_cast<void(cocos2d::Renderer::*)(cocos2d::CullMode)>(&cocos2d::Renderer::setCullMode);
mt["set"]["CullMode"]=mt["SetCullMode"];
mt["GetCullMode"]=static_cast<cocos2d::CullMode(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getCullMode);
mt["get"]["CullMode"]=mt["GetCullMode"];
mt["SetWinding"]=static_cast<void(cocos2d::Renderer::*)(cocos2d::Winding)>(&cocos2d::Renderer::setWinding);
mt["set"]["Winding"]=mt["SetWinding"];
mt["GetWinding"]=static_cast<cocos2d::Winding(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getWinding);
mt["get"]["Winding"]=mt["GetWinding"];
mt["SetViewPort"]=static_cast<void(cocos2d::Renderer::*)(int,int,unsigned int,unsigned int)>(&cocos2d::Renderer::setViewPort);
mt["GetViewport"]=static_cast<const cocos2d::Viewport&(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getViewport);
mt["get"]["Viewport"]=mt["GetViewport"];
mt["SetScissorTest"]=static_cast<void(cocos2d::Renderer::*)(bool)>(&cocos2d::Renderer::setScissorTest);
mt["set"]["ScissorTest"]=mt["SetScissorTest"];
mt["SetScissorRect"]=static_cast<void(cocos2d::Renderer::*)(float,float,float,float)>(&cocos2d::Renderer::setScissorRect);
mt["GetScissorTest"]=static_cast<bool(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getScissorTest);
mt["get"]["ScissorTest"]=mt["GetScissorTest"];
mt["GetScissorRect"]=static_cast<const cocos2d::ScissorRect&(cocos2d::Renderer::*)()const>(&cocos2d::Renderer::getScissorRect);
mt["get"]["ScissorRect"]=mt["GetScissorRect"];
mt["CheckVisibility"]=static_cast<bool(cocos2d::Renderer::*)(const cocos2d::Mat4&,const cocos2d::Size&)>(&cocos2d::Renderer::checkVisibility);
mt["ReadPixels"]=static_cast<void(cocos2d::Renderer::*)(cocos2d::backend::RenderTarget*,std::function<void (const cocos2d::backend::PixelBufferDescriptor &)>)>(&cocos2d::Renderer::readPixels);
mt["get"]["VBO_SIZE"]=[](){return cocos2d::Renderer::VBO_SIZE;};;
mt["get"]["INDEX_VBO_SIZE"]=[](){return cocos2d::Renderer::INDEX_VBO_SIZE;};;
mt["get"]["BATCH_TRIAGCOMMAND_RESERVED_SIZE"]=[](){return cocos2d::Renderer::BATCH_TRIAGCOMMAND_RESERVED_SIZE;};;
mt["get"]["MATERIAL_ID_DO_NOT_BATCH"]=[](){return cocos2d::Renderer::MATERIAL_ID_DO_NOT_BATCH;};;
}
void RegisterLuaCoreTextureCacheAuto(cocos2d::extension::Lua& lua){
cocos2d::extension::Lua::Id2Meta[typeid(cocos2d::TextureCache).name()] = sol::usertype_traits<cocos2d::TextureCache*>::metatable();
auto dep=lua.new_usertype<cocos2d::TextureCache>("deprecated.cocos2d::TextureCache");
dep[sol::base_classes]=sol::bases<cocos2d::Ref,cocos2d::extension::LuaObject>();
sol::table mt=lua.NewClass(sol::usertype_traits<cocos2d::TextureCache*>::metatable(),sol::usertype_traits<cocos2d::Ref*>::metatable());
lua["cc"]["TextureCache"]=mt;
mt["__new__"]=[](){return new cocos2d::TextureCache();};
mt["static"]["SetETC1AlphaFileSuffix"]=static_cast<void(*)(const std::string&)>(&cocos2d::TextureCache::setETC1AlphaFileSuffix);
mt["static"]["set"]["ETC1AlphaFileSuffix"]=mt["SetETC1AlphaFileSuffix"];
mt["static"]["GetETC1AlphaFileSuffix"]=static_cast<std::string(*)()>(&cocos2d::TextureCache::getETC1AlphaFileSuffix);
mt["static"]["get"]["ETC1AlphaFileSuffix"]=mt["GetETC1AlphaFileSuffix"];
mt["GetDescription"]=static_cast<std::string(cocos2d::TextureCache::*)()const>(&cocos2d::TextureCache::getDescription);
mt["get"]["Description"]=mt["GetDescription"];
mt["AddImage"]=sol::overload(static_cast<cocos2d::Texture2D*(cocos2d::TextureCache::*)(cocos2d::Image*,const std::string&)>(&cocos2d::TextureCache::addImage),static_cast<cocos2d::Texture2D*(cocos2d::TextureCache::*)(const std::string&)>(&cocos2d::TextureCache::addImage));
mt["AddImageAsync"]=sol::overload(static_cast<void(cocos2d::TextureCache::*)(const std::string&,const std::function<void (cocos2d::Texture2D *)>&,const std::string&)>(&cocos2d::TextureCache::addImageAsync),static_cast<void(cocos2d::TextureCache::*)(const std::string&,const std::function<void (cocos2d::Texture2D *)>&)>(&cocos2d::TextureCache::addImageAsync));
mt["UnbindImageAsync"]=static_cast<void(cocos2d::TextureCache::*)(const std::string&)>(&cocos2d::TextureCache::unbindImageAsync);
mt["UnbindAllImageAsync"]=static_cast<void(cocos2d::TextureCache::*)()>(&cocos2d::TextureCache::unbindAllImageAsync);
mt["GetTextureForKey"]=static_cast<cocos2d::Texture2D*(cocos2d::TextureCache::*)(const std::string&)const>(&cocos2d::TextureCache::getTextureForKey);
mt["ReloadTexture"]=static_cast<bool(cocos2d::TextureCache::*)(const std::string&)>(&cocos2d::TextureCache::reloadTexture);
mt["RemoveAllTextures"]=static_cast<void(cocos2d::TextureCache::*)()>(&cocos2d::TextureCache::removeAllTextures);
mt["RemoveUnusedTextures"]=static_cast<void(cocos2d::TextureCache::*)()>(&cocos2d::TextureCache::removeUnusedTextures);
mt["RemoveTexture"]=static_cast<void(cocos2d::TextureCache::*)(cocos2d::Texture2D*)>(&cocos2d::TextureCache::removeTexture);
mt["RemoveTextureForKey"]=static_cast<void(cocos2d::TextureCache::*)(const std::string&)>(&cocos2d::TextureCache::removeTextureForKey);
mt["GetCachedTextureInfo"]=static_cast<std::string(cocos2d::TextureCache::*)()const>(&cocos2d::TextureCache::getCachedTextureInfo);
mt["get"]["CachedTextureInfo"]=mt["GetCachedTextureInfo"];
mt["WaitForQuit"]=static_cast<void(cocos2d::TextureCache::*)()>(&cocos2d::TextureCache::waitForQuit);
mt["GetTextureFilePath"]=static_cast<std::string(cocos2d::TextureCache::*)(cocos2d::Texture2D*)const>(&cocos2d::TextureCache::getTextureFilePath);
mt["RenameTextureWithKey"]=static_cast<void(cocos2d::TextureCache::*)(const std::string&,const std::string&)>(&cocos2d::TextureCache::renameTextureWithKey);
}
void RegisterLuaCoreDeviceAuto(cocos2d::extension::Lua& lua){
cocos2d::extension::Lua::Id2Meta[typeid(cocos2d::Device).name()] = sol::usertype_traits<cocos2d::Device*>::metatable();
auto dep=lua.new_usertype<cocos2d::Device>("deprecated.cocos2d::Device");
sol::table mt=lua.NewClass(sol::usertype_traits<cocos2d::Device*>::metatable());
lua["cc"]["Device"]=mt;
mt["__new__"] = [](){return nullptr;};
mt["static"]["GetDPI"]=static_cast<int(*)()>(&cocos2d::Device::getDPI);
mt["static"]["get"]["DPI"]=mt["GetDPI"];
mt["static"]["SetAccelerometerEnabled"]=static_cast<void(*)(bool)>(&cocos2d::Device::setAccelerometerEnabled);
mt["static"]["set"]["AccelerometerEnabled"]=mt["SetAccelerometerEnabled"];
mt["static"]["SetAccelerometerInterval"]=static_cast<void(*)(float)>(&cocos2d::Device::setAccelerometerInterval);
mt["static"]["set"]["AccelerometerInterval"]=mt["SetAccelerometerInterval"];
mt["static"]["SetKeepScreenOn"]=static_cast<void(*)(bool)>(&cocos2d::Device::setKeepScreenOn);
mt["static"]["set"]["KeepScreenOn"]=mt["SetKeepScreenOn"];
mt["static"]["Vibrate"]=static_cast<void(*)(float)>(&cocos2d::Device::vibrate);
}
void RegisterLuaCoreApplicationProtocolPlatformAuto(cocos2d::extension::Lua& lua) {
sol::table enumTable = lua.create_table_with(0,6);
enumTable["OS_WINDOWS"]=cocos2d::ApplicationProtocol::Platform::OS_WINDOWS;
enumTable["OS_LINUX"]=cocos2d::ApplicationProtocol::Platform::OS_LINUX;
enumTable["OS_MAC"]=cocos2d::ApplicationProtocol::Platform::OS_MAC;
enumTable["OS_ANDROID"]=cocos2d::ApplicationProtocol::Platform::OS_ANDROID;
enumTable["OS_IPHONE"]=cocos2d::ApplicationProtocol::Platform::OS_IPHONE;
enumTable["OS_IPAD"]=cocos2d::ApplicationProtocol::Platform::OS_IPAD;
lua["cc"]["ApplicationProtocol"]["static"]["Platform"]=lua.NewEnum(enumTable);
}
void RegisterLuaCoreApplicationProtocolAuto(cocos2d::extension::Lua& lua){
cocos2d::extension::Lua::Id2Meta[typeid(cocos2d::ApplicationProtocol).name()] = sol::usertype_traits<cocos2d::ApplicationProtocol*>::metatable();
auto dep=lua.new_usertype<cocos2d::ApplicationProtocol>("deprecated.cocos2d::ApplicationProtocol");
sol::table mt=lua.NewClass(sol::usertype_traits<cocos2d::ApplicationProtocol*>::metatable());
lua["cc"]["ApplicationProtocol"]=mt;
mt["__new__"] = [](){return nullptr;};
mt["ApplicationDidFinishLaunching"]=static_cast<bool(cocos2d::ApplicationProtocol::*)()>(&cocos2d::ApplicationProtocol::applicationDidFinishLaunching);
mt["ApplicationDidEnterBackground"]=static_cast<void(cocos2d::ApplicationProtocol::*)()>(&cocos2d::ApplicationProtocol::applicationDidEnterBackground);
mt["ApplicationWillEnterForeground"]=static_cast<void(cocos2d::ApplicationProtocol::*)()>(&cocos2d::ApplicationProtocol::applicationWillEnterForeground);
mt["SetAnimationInterval"]=static_cast<void(cocos2d::ApplicationProtocol::*)(float)>(&cocos2d::ApplicationProtocol::setAnimationInterval);
mt["set"]["AnimationInterval"]=mt["SetAnimationInterval"];
mt["InitGLContextAttrs"]=static_cast<void(cocos2d::ApplicationProtocol::*)()>(&cocos2d::ApplicationProtocol::initGLContextAttrs);
mt["GetCurrentLanguage"]=static_cast<cocos2d::LanguageType(cocos2d::ApplicationProtocol::*)()>(&cocos2d::ApplicationProtocol::getCurrentLanguage);
mt["get"]["CurrentLanguage"]=mt["GetCurrentLanguage"];
mt["GetCurrentLanguageCode"]=static_cast<const char*(cocos2d::ApplicationProtocol::*)()>(&cocos2d::ApplicationProtocol::getCurrentLanguageCode);
mt["get"]["CurrentLanguageCode"]=mt["GetCurrentLanguageCode"];
mt["GetTargetPlatform"]=static_cast<cocos2d::ApplicationProtocol::Platform(cocos2d::ApplicationProtocol::*)()>(&cocos2d::ApplicationProtocol::getTargetPlatform);
mt["get"]["TargetPlatform"]=mt["GetTargetPlatform"];
mt["GetVersion"]=static_cast<std::string(cocos2d::ApplicationProtocol::*)()>(&cocos2d::ApplicationProtocol::getVersion);
mt["get"]["Version"]=mt["GetVersion"];
mt["GetCompileVersion"]=static_cast<int64_t(cocos2d::ApplicationProtocol::*)()>(&cocos2d::ApplicationProtocol::GetCompileVersion);
mt["get"]["CompileVersion"]=mt["GetCompileVersion"];
mt["OpenURL"]=static_cast<bool(cocos2d::ApplicationProtocol::*)(const std::string&)>(&cocos2d::ApplicationProtocol::openURL);
mt["RestartLuaEngine"]=static_cast<bool(cocos2d::ApplicationProtocol::*)()>(&cocos2d::ApplicationProtocol::RestartLuaEngine);
mt["Dialog"]=sol::overload([](cocos2d::ApplicationProtocol* obj,const std::string& arg0,const std::string& arg1,const std::function<void ()>& arg2,const std::function<void ()>& arg3){return obj->Dialog(arg0,arg1,arg2,arg3);},[](cocos2d::ApplicationProtocol* obj,const std::string& arg0,const std::string& arg1,const std::function<void ()>& arg2){return obj->Dialog(arg0,arg1,arg2);},[](cocos2d::ApplicationProtocol* obj,const std::string& arg0,const std::string& arg1){return obj->Dialog(arg0,arg1);});
mt["Notify"]=sol::overload([](cocos2d::ApplicationProtocol* obj,const std::string& arg0,const std::string& arg1,const std::function<void ()>& arg2){return obj->Notify(arg0,arg1,arg2);},[](cocos2d::ApplicationProtocol* obj,const std::string& arg0,const std::string& arg1){return obj->Notify(arg0,arg1);});
RegisterLuaCoreApplicationProtocolPlatformAuto(lua);
}
void RegisterLuaCoreApplicationAuto(cocos2d::extension::Lua& lua){
cocos2d::extension::Lua::Id2Meta[typeid(cocos2d::Application).name()] = sol::usertype_traits<cocos2d::Application*>::metatable();
auto dep=lua.new_usertype<cocos2d::Application>("deprecated.cocos2d::Application");
dep[sol::base_classes]=sol::bases<cocos2d::ApplicationProtocol>();
sol::table mt=lua.NewClass(sol::usertype_traits<cocos2d::Application*>::metatable(),sol::usertype_traits<cocos2d::ApplicationProtocol*>::metatable());
lua["cc"]["Application"]=mt;
mt["__new__"] = [](){return nullptr;};
mt["Run"]=static_cast<int(cocos2d::Application::*)()>(&cocos2d::Application::run);
mt["static"]["GetInstance"]=static_cast<cocos2d::Application*(*)()>(&cocos2d::Application::getInstance);
mt["static"]["get"]["Instance"]=&cocos2d::Application::getInstance;
}
void RegisterLuaCoreGLViewImplAuto(cocos2d::extension::Lua& lua){
cocos2d::extension::Lua::Id2Meta[typeid(cocos2d::GLViewImpl).name()] = sol::usertype_traits<cocos2d::GLViewImpl*>::metatable();
auto dep=lua.new_usertype<cocos2d::GLViewImpl>("deprecated.cocos2d::GLViewImpl");
dep[sol::base_classes]=sol::bases<cocos2d::GLView,cocos2d::Ref,cocos2d::extension::LuaObject>();
sol::table mt=lua.NewClass(sol::usertype_traits<cocos2d::GLViewImpl*>::metatable(),sol::usertype_traits<cocos2d::GLView*>::metatable());
lua["cc"]["GLViewImpl"]=mt;
mt["__new__"]=static_cast<cocos2d::GLViewImpl*(*)(const std::string&)>(&cocos2d::GLViewImpl::create);
mt["static"]["CreateWithRect"]=sol::overload([](const std::string& arg0,cocos2d::Rect arg1,float arg2,bool arg3){return cocos2d::GLViewImpl::createWithRect(arg0,arg1,arg2,arg3);},[](const std::string& arg0,cocos2d::Rect arg1,float arg2){return cocos2d::GLViewImpl::createWithRect(arg0,arg1,arg2);},[](const std::string& arg0,cocos2d::Rect arg1){return cocos2d::GLViewImpl::createWithRect(arg0,arg1);});
mt["static"]["CreateWithFullScreen"]=static_cast<cocos2d::GLViewImpl*(*)(const std::string&)>(&cocos2d::GLViewImpl::createWithFullScreen);
}
void RegisterLuaCoreAnimationCacheAuto(cocos2d::extension::Lua& lua){
cocos2d::extension::Lua::Id2Meta[typeid(cocos2d::AnimationCache).name()] = sol::usertype_traits<cocos2d::AnimationCache*>::metatable();
auto dep=lua.new_usertype<cocos2d::AnimationCache>("deprecated.cocos2d::AnimationCache");
dep[sol::base_classes]=sol::bases<cocos2d::Ref,cocos2d::extension::LuaObject>();
sol::table mt=lua.NewClass(sol::usertype_traits<cocos2d::AnimationCache*>::metatable(),sol::usertype_traits<cocos2d::Ref*>::metatable());
lua["cc"]["AnimationCache"]=mt;
mt["__new__"]=[](){return new cocos2d::AnimationCache();};
mt["static"]["GetInstance"]=static_cast<cocos2d::AnimationCache*(*)()>(&cocos2d::AnimationCache::getInstance);
mt["static"]["DestroyInstance"]=static_cast<void(*)()>(&cocos2d::AnimationCache::destroyInstance);
mt["Init"]=static_cast<bool(cocos2d::AnimationCache::*)()>(&cocos2d::AnimationCache::init);
mt["AddAnimation"]=static_cast<void(cocos2d::AnimationCache::*)(cocos2d::Animation*,const std::string&)>(&cocos2d::AnimationCache::addAnimation);
mt["RemoveAnimation"]=static_cast<void(cocos2d::AnimationCache::*)(const std::string&)>(&cocos2d::AnimationCache::removeAnimation);
mt["GetAnimation"]=static_cast<cocos2d::Animation*(cocos2d::AnimationCache::*)(const std::string&)>(&cocos2d::AnimationCache::getAnimation);
mt["AddAnimationsWithDictionary"]=static_cast<void(cocos2d::AnimationCache::*)(const cocos2d::ValueMap&,const std::string&)>(&cocos2d::AnimationCache::addAnimationsWithDictionary);
mt["AddAnimations"]=static_cast<void(cocos2d::AnimationCache::*)(const std::string&)>(&cocos2d::AnimationCache::addAnimationsWithFile);
mt["static"]["get"]["Instance"]=&cocos2d::AnimationCache::getInstance;
mt["static"]["set"]["Instance"]=[](std::nullptr_t){cocos2d::AnimationCache::destroyInstance();};
}
void RegisterLuaCoreSpriteBatchNodeAuto(cocos2d::extension::Lua& lua){
cocos2d::extension::Lua::Id2Meta[typeid(cocos2d::SpriteBatchNode).name()] = sol::usertype_traits<cocos2d::SpriteBatchNode*>::metatable();
auto dep=lua.new_usertype<cocos2d::SpriteBatchNode>("deprecated.cocos2d::SpriteBatchNode");
dep[sol::base_classes]=sol::bases<cocos2d::Node,cocos2d::Ref,cocos2d::extension::LuaObject,cocos2d::TextureProtocol,cocos2d::BlendProtocol>();
sol::table mt=lua.NewClass(sol::usertype_traits<cocos2d::SpriteBatchNode*>::metatable(),sol::usertype_traits<cocos2d::Node*>::metatable(),sol::usertype_traits<cocos2d::TextureProtocol*>::metatable());
lua["cc"]["SpriteBatchNode"]=mt;
mt["static"]["CreateWithTexture"]=sol::overload([](cocos2d::Texture2D* arg0,ssize_t arg1){return cocos2d::SpriteBatchNode::createWithTexture(arg0,arg1);},[](cocos2d::Texture2D* arg0){return cocos2d::SpriteBatchNode::createWithTexture(arg0);});
mt["__new__"]=sol::overload([](const std::string& arg0,ssize_t arg1){return cocos2d::SpriteBatchNode::create(arg0,arg1);},[](const std::string& arg0){return cocos2d::SpriteBatchNode::create(arg0);});
mt["GetTextureAtlas"]=static_cast<cocos2d::TextureAtlas*(cocos2d::SpriteBatchNode::*)()>(&cocos2d::SpriteBatchNode::getTextureAtlas);
mt["get"]["TextureAtlas"]=mt["GetTextureAtlas"];
mt["SetTextureAtlas"]=static_cast<void(cocos2d::SpriteBatchNode::*)(cocos2d::TextureAtlas*)>(&cocos2d::SpriteBatchNode::setTextureAtlas);
mt["set"]["TextureAtlas"]=mt["SetTextureAtlas"];
mt["GetDescendants"]=static_cast<const std::vector<cocos2d::Sprite *, std::allocator<cocos2d::Sprite *> >&(cocos2d::SpriteBatchNode::*)()const>(&cocos2d::SpriteBatchNode::getDescendants);
mt["get"]["Descendants"]=mt["GetDescendants"];
mt["IncreaseAtlasCapacity"]=static_cast<void(cocos2d::SpriteBatchNode::*)()>(&cocos2d::SpriteBatchNode::increaseAtlasCapacity);
mt["RemoveChildAtIndex"]=static_cast<void(cocos2d::SpriteBatchNode::*)(ssize_t,bool)>(&cocos2d::SpriteBatchNode::removeChildAtIndex);
mt["AppendChild"]=static_cast<void(cocos2d::SpriteBatchNode::*)(cocos2d::Sprite*)>(&cocos2d::SpriteBatchNode::appendChild);
mt["RemoveSpriteFromAtlas"]=static_cast<void(cocos2d::SpriteBatchNode::*)(cocos2d::Sprite*)>(&cocos2d::SpriteBatchNode::removeSpriteFromAtlas);
mt["RebuildIndexInOrder"]=static_cast<ssize_t(cocos2d::SpriteBatchNode::*)(cocos2d::Sprite*,ssize_t)>(&cocos2d::SpriteBatchNode::rebuildIndexInOrder);
mt["HighestAtlasIndexInChild"]=static_cast<ssize_t(cocos2d::SpriteBatchNode::*)(cocos2d::Sprite*)>(&cocos2d::SpriteBatchNode::highestAtlasIndexInChild);
mt["LowestAtlasIndexInChild"]=static_cast<ssize_t(cocos2d::SpriteBatchNode::*)(cocos2d::Sprite*)>(&cocos2d::SpriteBatchNode::lowestAtlasIndexInChild);
mt["AtlasIndexForChild"]=static_cast<ssize_t(cocos2d::SpriteBatchNode::*)(cocos2d::Sprite*,int)>(&cocos2d::SpriteBatchNode::atlasIndexForChild);
mt["ReorderBatch"]=static_cast<void(cocos2d::SpriteBatchNode::*)(bool)>(&cocos2d::SpriteBatchNode::reorderBatch);
mt["InsertQuadFromSprite"]=static_cast<void(cocos2d::SpriteBatchNode::*)(cocos2d::Sprite*,ssize_t)>(&cocos2d::SpriteBatchNode::insertQuadFromSprite);
mt["AddSpriteWithoutQuad"]=static_cast<cocos2d::SpriteBatchNode*(cocos2d::SpriteBatchNode::*)(cocos2d::Sprite*,int,int)>(&cocos2d::SpriteBatchNode::addSpriteWithoutQuad);
mt["ReserveCapacity"]=static_cast<void(cocos2d::SpriteBatchNode::*)(ssize_t)>(&cocos2d::SpriteBatchNode::reserveCapacity);
}