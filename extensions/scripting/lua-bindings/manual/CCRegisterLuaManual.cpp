#include "CCRegisterLuaManual.h"
#include "CCLuaConvertSol.hpp"
// lua socket.
#if __cplusplus
extern "C" {
#endif
#include "luasocket/luasocket.h"
#include "luasocket/luasocket_scripts.h"
#include "luasocket/mime.h"
#if __cplusplus
} // extern "C"
#endif

#include "2d/CCTMXXMLParser.h"
#include "platform/CCApplication.h"
#include "platform/CCDevice.h"
#include "2d/CCRenderTexture.h"
#include "2d/CCParallaxNode.h"
#include "base/ccCArray.h"
#include "renderer/backend/ProgramState.h"
#if CC_USE_PHYSICS
#include "physics/CCPhysicsBody.h"
#if CC_ENABLE_CHIPMUNK_INTEGRATION
#include "chipmunk/chipmunk_private.h"
#endif
#if CC_ENABLE_BOX2D_INTEGRATION
#include "box2d/box2d.h"
#endif
#endif
#include "CCDatas.h"
#include "ActionTimeline/CCSkeletonNode.h"

using namespace cocos2d;

static void RegisterLuaSocketManual(Lua& lua) {
    static constexpr luaL_Reg luax_exts[] = {
    {"socket.core", luaopen_socket_core},
    {"mime.core", luaopen_mime_core}
    };
    sol::table preload = lua["package"]["preload"];
    for (auto& iter : luax_exts) {
        preload[iter.name] = iter.func;
    }

    luaopen_luasocket_scripts(lua.lua_state());
}

static void RegisterLuaCoreTMXMapInfoManual(Lua& lua) {
    sol::usertype<TMXMapInfo> tmi = lua["cc"]["TMXMapInfo"];
    tmi["startElement"] = [](TMXMapInfo* tmi, const std::string_view& sv, const sol::table t) {
        const auto size = t.size();
        std::unique_ptr<const char* []> strs = std::make_unique<const char* []>(size + 1);
        std::vector<std::string> sVec = {};
        for (int i = 1; i <= size; i++) {
            std::string value = t[i];
            sVec.emplace_back(value);
        }
        strs[size] = nullptr;
        tmi->startElement(nullptr, sv.data(), strs.get());
    };
    tmi["endElement"] = [](TMXMapInfo* tmi, const std::string_view& sv) {
        tmi->endElement(nullptr, sv.data());
    };
}

static void RegisterLuaCoreApplicationManual(Lua& lua) {
    sol::usertype<Application> app = lua["cc"]["Application"];
#if CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID
    app["Dialog"] = [](Application* app, const std::string& title, const std::string& content, sol::variadic_args va) {
        const auto size = va.size();
        if (size == 0) {
            app->Dialog(title, content);
        }
        else if (size == 1) {
            sol::function f = va[0];
            app->Dialog(title, content, f);
        }
        else if (size == 2) {
            sol::function f1 = va[0];
            sol::object o = va[1];
            if (o.get_type() == sol::type::function) {
                sol::function f2 = o;
                app->Dialog(title, content, f1, f2);
            }
            else if (o.get_type() == sol::type::boolean) {
                app->Dialog(title, content, f1, o.as<bool>() ? []() {} : std::function<void()>(nullptr));
            }
            else if (o.get_type() == sol::type::nil) {
                sol::function f = va[0];
                app->Dialog(title, content, f);
            }
        }
    };
#endif
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
    app["Notify"] = [](Application* app, const std::string& title, const std::string& content, sol::variadic_args va) {
        app->Notify(title, content,
            va.size() == 0 ? std::function<void()>(nullptr) : va[0].as<sol::function>()
        );
    };
#endif
}

static void RegisterLuaCoreDeviceManual(Lua& lua) {
    sol::usertype<cocos2d::Device> device = lua["cc"]["Device"];
    device["getTextureDataForText"] = [](const std::string& text, const FontDefinition& fd, lua_Integer align) {
        int width = 0;
        int height = 0;
        bool hasPremultipliedAlpha = false;
        cocos2d::Data d = cocos2d::Device::getTextureDataForText(text.c_str(), fd, static_cast<cocos2d::Device::TextAlign>(align), width, height, hasPremultipliedAlpha);
        auto ret = std::string(reinterpret_cast<char*>(d.getBytes()), static_cast<size_t>(d.getSize()));
        return std::make_tuple(ret, width, height, hasPremultipliedAlpha);
    };
}

static void RegisterLuaCoreRenderTextureManual(Lua& lua) {
    sol::usertype<RenderTexture> renderTexture = lua["cc"]["RenderTexture"];
    renderTexture["newImage"] = [](RenderTexture* renderTexture, sol::function f, sol::variadic_args va) {
        renderTexture->newImage([f](RefPtr<Image> refPtr) {
            f(refPtr.get());
        }, va.size() == 0 ? false : va[0].as<bool>());
    };
}

static void RegisterLuaCoreParallaxNodeManual(Lua& lua) {
    sol::usertype<ParallaxNode> parallaxNode = lua["cc"]["ParallaxNode"];
    parallaxNode["setParallaxArray"] = [](ParallaxNode* parallaxNode, sol::table t) {
        const auto size = static_cast<ssize_t>(t.size());
        _ccArray* arr = ccArrayNew(size);

        lua_State* L = t.lua_state();// userdata table
        lua_pushnil(L);// userdata table nil
        while (lua_next(L, -2)) {// userdata table key? value?
            void** p = (void**)lua_touserdata(L, -1);// userdata table key value
            ccArrayAppendObject(arr, *reinterpret_cast<Ref**>(p));// userdata table key value
            lua_pop(L, 1);// userdata table key
        }
        parallaxNode->setParallaxArray(arr);
    };
    parallaxNode["getParallaxArray"] = [&lua](ParallaxNode* parallaxNode) {
        const _ccArray* const arr = parallaxNode->getParallaxArray();
        sol::table t = lua.create_table(static_cast<int>(arr->num));
        Ref* ref = nullptr;
        int i = 1;
        CCARRAYDATA_FOREACH(arr, ref) {
            t[i++] = ref;
        }
        return t;
    };
}

static void RegisterLuaBackendProgramStateManual(Lua& lua) {
    sol::usertype<backend::ProgramState> programState = lua["ccb"]["ProgramState"];
    programState["getCallbackUniforms"] = [&lua](backend::ProgramState* programState) {
        const auto& m = programState->getCallbackUniforms();
        sol::table t = lua.create_table(0, static_cast<int>(m.size()));
        for (const auto& it : m) {
            t[it.first] = it.second;
        }
        return t;
    };
    programState["getVertexUniformBuffer"] = [&lua](backend::ProgramState* programState) {
        char* outStr = nullptr;
        size_t size = 0;
        programState->getVertexUniformBuffer(&outStr, size);
        return std::string(outStr, size);
    };

    programState["getFragmentUniformBuffer"] = [&lua](backend::ProgramState* programState) {
        char* outStr = nullptr;
        size_t size = 0;
        programState->getFragmentUniformBuffer(&outStr, size);
        return std::string(outStr, size);
    };
}

static void RegisterLuaPhysicsPhysicsBodyManual(Lua& lua) {
#if CC_USE_PHYSICS
    sol::usertype<PhysicsBody> physicsBody = lua["cc"]["PhysicsBody"];
#if CC_ENABLE_CHIPMUNK_INTEGRATION
    physicsBody["getCPBody"] = &PhysicsBody::getCPBody;
#endif
#if CC_ENABLE_BOX2D_INTEGRATION
    // todo
    physicsBody["getB2DBody"] = []() {
        return 0;
    };
#endif
#endif
}

template<typename T, typename MT>
static void Cocos2dxVectorToTable(
    Lua& lua,
    const std::string_view& svNameSpace,
    const std::string_view& svClassName,
    const std::string_view& svMethodName,
    MT&& mt) {
    sol::usertype<T> cls = lua[svNameSpace][svClassName];
    cls[svMethodName] = sol::readonly_property([&lua, mt](T* obj) {
        // The returned table does not hold data.
        auto& dList = obj->*mt;
        sol::table t = lua.create_table(static_cast<int>(dList.size()));
        int i = 1;
        for (auto& data : dList) {
            t[i++] = data;
        }
        return t;
    });
}

template<typename T, typename MT>
static void Cocos2dxMapToTable(
    Lua& lua,
    const std::string_view& svNameSpace,
    const std::string_view& svClassName,
    const std::string_view& svMethodName,
    MT&& mt) {
    sol::usertype<T> cls = lua[svNameSpace][svClassName];
    cls[svMethodName] = sol::readonly_property([&lua, mt](T* obj) {
        // The returned table does not hold data.
        auto& dMap = obj->*mt;
        sol::table t = lua.create_table(0, static_cast<int>(dMap.size()));
        for (auto& data : dMap) {
            t[data.first] = data.second;
        }
        return t;
    });
}

inline static void RegisterLuaStudioBoneDataManual(Lua& lua) {
    Cocos2dxVectorToTable<cocostudio::BoneData>(lua, "ccs", "BoneData", "displayDataList", &cocostudio::BoneData::displayDataList);
}

inline static void RegisterLuaStudioArmatureDataManual(Lua& lua) {
    Cocos2dxMapToTable<cocostudio::ArmatureData>(lua, "ccs", "ArmatureData", "boneDataDic", &cocostudio::ArmatureData::boneDataDic);
}

inline static void RegisterLuaStudioMovementBoneDataManual(Lua& lua) {
    Cocos2dxVectorToTable<cocostudio::MovementBoneData>(lua, "ccs", "MovementBoneData", "frameList", &cocostudio::MovementBoneData::frameList);
}

static void RegisterLuaStudioSkeletonNodeManual(Lua& lua) {
    sol::usertype<cocostudio::timeline::SkeletonNode> skeletonNode = lua["ccs"]["SkeletonNode"];
    skeletonNode["getAllSubBonesMap"] = [&lua](cocostudio::timeline::SkeletonNode* skeletonNode) {
        // The returned table does not hold data.
        auto& sMap = skeletonNode->getAllSubBonesMap();
        sol::table t = lua.create_table(0, static_cast<int>(sMap.size()));
        for (auto& data : sMap) {
            t[data.first] = data.second;
        }
    };
}

inline static void RegisterLuaStudioAnimationDataManual(Lua& lua) {
    Cocos2dxMapToTable<cocostudio::AnimationData>(lua, "ccs", "AnimationData", "movementDataDic", &cocostudio::AnimationData::movementDataDic);
}

inline static void RegisterLuaStudioTextureDataManual(Lua& lua) {
    Cocos2dxVectorToTable<cocostudio::TextureData>(lua, "ccs", "TextureData", "contourDataList", &cocostudio::TextureData::contourDataList);
}

inline static void RegisterLuaStudioMovementDataManual(Lua& lua) {
    Cocos2dxMapToTable<cocostudio::MovementData>(lua, "ccs", "MovementData", "movBoneDataDic", &cocostudio::MovementData::movBoneDataDic);
}

void RegisterLuaManual(Lua& lua) {
    RegisterLuaSocketManual(lua);
    RegisterLuaCoreTMXMapInfoManual(lua);
    RegisterLuaCoreApplicationManual(lua);
    RegisterLuaCoreDeviceManual(lua);
    RegisterLuaCoreRenderTextureManual(lua);
    RegisterLuaCoreParallaxNodeManual(lua);
    RegisterLuaBackendProgramStateManual(lua);
    RegisterLuaPhysicsPhysicsBodyManual(lua);
    RegisterLuaStudioBoneDataManual(lua);
    RegisterLuaStudioArmatureDataManual(lua);
    RegisterLuaStudioMovementBoneDataManual(lua);
    RegisterLuaStudioSkeletonNodeManual(lua);
    RegisterLuaStudioAnimationDataManual(lua);
    RegisterLuaStudioTextureDataManual(lua);
    RegisterLuaStudioMovementDataManual(lua);
}