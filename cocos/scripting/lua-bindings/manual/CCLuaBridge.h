/****************************************************************************
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

#ifndef __LUA_BRIDGE_H_
#define __LUA_BRIDGE_H_

#include <string>
#include <map>
#include "scripting/lua-bindings/manual/CCLuaEngine.h"

extern "C" {
#include "lua.h"
}

using namespace std;
/**
 * @addtogroup lua
 * @{
 */

NS_CC_BEGIN
/** LuaBridge Error enum, with inline docs. */
typedef enum {
    kLuaBridgeErrorOk                   = 0,  /** &lt; value 0 */
    kLuaBridgeErrorInvalidParameters    = -1, /** &lt; value -1 */
    kLuaBridgeErrorClassNotFound        = -2, /** &lt; value -2 */
    kLuaBridgeErrorMethodNotFound       = -3, /** &lt; value -3 */
    kLuaBridgeErrorExceptionOccurred    = -4, /** &lt; value -4 */
    kLuaBridgeErrorMethodSignature      = -5, /** &lt; value -5 */
    kLuaBridgeErrorJavaVMError          = -6, /** &lt; value -6 */
} LuaBridgeError;

#define LUA_BRIDGE_REGISTRY_FUNCTION    "lua_bridge_function_id"        // table[function] = id

/**
 * Build bridge between ObjC and Lua.
 * It makes Lua and ObjC can call each other conveniently.
 *
 * @lua NA
 * @js NA
 */
class LuaBridge
{
public:
    static void releaseLuaFunction(int functionId);

    /**
     * Call the Lua function corresponding to the functionId with the string pointer arg.
     *
     * @param functionId the values corresponding to the Lua function.
     * @param arg the string pointer point to the argument.
     * @return a number value returned from the Lua function when call successfully, otherwise return -1 or the opposite number for one of the three numbers LUA_ERRRUN, LUA_ERRMEM and LUA_ERRERR.
     *
     * @lua NA
     * @js NA
     */
    static int callLuaFunction(int functionId, const char *arg);

    /**
     * Call the Lua function corresponding to the functionId with int64 arg.
     *
     * @param functionId the values corresponding to the Lua function.
     * @param arg int64 to the argument.
     * @return a number value returned from the Lua function when call successfully, otherwise return -1 or the opposite number for one of the three numbers LUA_ERRRUN, LUA_ERRMEM and LUA_ERRERR.
     *
     * @lua NA
     * @js NA
     */
    static int callLuaFunction(int functionId, int64_t arg);

    /**
     * Call the Lua function corresponding to the functionId with boolean arg.
     *
     * @param functionId the values corresponding to the Lua function.
     * @param arg boolean to the argument.
     * @return a number value returned from the Lua function when call successfully, otherwise return -1 or the opposite number for one of the three numbers LUA_ERRRUN, LUA_ERRMEM and LUA_ERRERR.
     *
     * @lua NA
     * @js NA
     */
    static int callLuaFunction(int functionId, bool arg);

    /**
     * Call the Lua function corresponding to the functionId with the std::map<string,string> arg.
     *
     * @param functionId the values corresponding to the Lua function.
     * @param arg the std::map<string,string> to the argument.
     * @return a number value returned from the Lua function when call successfully, otherwise return -1 or the opposite number for one of the three numbers LUA_ERRRUN, LUA_ERRMEM and LUA_ERRERR.
     *
     * @lua NA
     * @js NA
     */
    static int callLuaFunction(int functionId, const std::map<std::string,std::string>& arg);

    /**
     * Call the Lua function corresponding to the functionId.
     *
     * @param functionId the values corresponding to the Lua function.
     * @return a number value returned from the Lua function when call successfully, otherwise return -1 or the opposite number for one of the three numbers LUA_ERRRUN, LUA_ERRMEM and LUA_ERRERR.
     *
     * @lua NA
     * @js NA
     */
    static int callLuaFunction(int functionId);

    /**
     * Call a global Lua function named functionName with the string pointer arg.
     *
     * @param functionName the name of global function.
     * @param arg the string pointer point to the argument.
     * @return a number value returned from the Lua function when call successfully, otherwise return -1 or the opposite number for one of the three numbers LUA_ERRRUN, LUA_ERRMEM and LUA_ERRERR.
     *
     * @lua NA
     * @js NA
     */
    static int callLuaGlobalFunction(const char *functionName, const char *arg);

protected:
    static int retainLuaFunction(int functionIndex);
    static int increaseIdLevel;
    static void SetLua(lua_State*);
    static lua_State* L;
};

NS_CC_END

// end group
/// @}

#endif // __LUA_BRIDGE_H_
