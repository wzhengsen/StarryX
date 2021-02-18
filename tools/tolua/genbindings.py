#!/usr/bin/env python3

# This script is used to generate luabinding glue codes.

import sys
import os, os.path
import shutil
import subprocess
import re
from contextlib import contextmanager


def _check_ndk_root_env():
    ''' Checking the environment ANDROID_NDK, which will be used for building
    '''

    try:
        ANDROID_NDK = os.environ['ANDROID_NDK']
    except Exception:
        print("ANDROID_NDK not defined. Please define ANDROID_NDK in your environment.")
        sys.exit(1)

    return ANDROID_NDK

def _check_python_bin_env():
    ''' Checking the environment PYTHON_BIN, which will be used for building
    '''

    try:
        PYTHON_BIN = os.environ['PYTHON_BIN']
    except Exception:
        print("PYTHON_BIN not defined, use current python.")
        PYTHON_BIN = sys.executable

    return PYTHON_BIN

def _find_first_file_in_dir(dir, fn):
    if os.path.isfile(dir):
        if os.path.basename(dir) == fn:
            return os.path.join(os.path.dirname(dir), fn)
        else :
            return None
    elif os.path.isdir(dir):
      for subdir in os.listdir(dir):
          searchPath = _find_first_file_in_dir(os.path.join(dir, subdir), fn)
          if searchPath is not None:
              return searchPath
    else:
        return None

def _find_all_files_match(dir, cond, all):
    if cond(dir):
        all.append(dir)
    elif os.path.isdir(dir):
        for subdir in os.listdir(dir):
            _find_all_files_match(os.path.join(dir, subdir), cond, all)


def _find_toolchain_include_path():
    '''
    Search gcc prebuilt include path
    for instance: "$ANDROID_NDK/toolchains/arm-linux-androideabi-4.9/prebuilt/windows-x86_64/lib/gcc/arm-linux-androideabi/4.9.x/include"
    '''
    foundFiles = []
    _find_all_files_match(os.path.join(_check_ndk_root_env(), "toolchains"), lambda x : os.path.basename(x) == "stdarg.h" and "arm-linux-androideabi" in x , foundFiles)
    if len(foundFiles) == 0:
        return ""
    else:
        return "-I" + os.path.dirname(foundFiles[0])

def _find_llvm_include_path():
    '''
    Search llvm prebuilt include path.
    for instance: "$ANDROID_NDK/toolchains/llvm/prebuilt/windows-x86_64/lib64/clang/6.0.2/include"
    '''
    versionFile = _find_first_file_in_dir(_check_ndk_root_env(), "AndroidVersion.txt")
    if versionFile is None:
        return ""
    versionDir = os.path.dirname(versionFile)
    includeDir = _find_first_file_in_dir(versionDir, "stdarg.h")
    llvmIncludePath = os.path.dirname(includeDir)
    return "-I"+llvmIncludePath


def _defaultIncludePath():
    '''default include path for libclang, llvm & gcc include path
    '''
    llvmInclude = _find_llvm_include_path()
    toolchainInclude = _find_toolchain_include_path()
    exactIncludes =  llvmInclude + " " + toolchainInclude
    return exactIncludes


class CmdError(Exception):
    pass


@contextmanager
def _pushd(newDir):
    previousDir = os.getcwd()
    os.chdir(newDir)
    yield
    os.chdir(previousDir)

def _run_cmd(command):
    ret = subprocess.call(command, shell=True)
    if ret != 0:
        message = "Error running command"
        raise CmdError(message)

def main():

    cur_platform= '??'
    llvm_path = '??'
    ndk_root = _check_ndk_root_env()
    python_bin = _check_python_bin_env()
    # del the " in the path
    ndk_root = re.sub(r"\"", "", ndk_root)

    platform = sys.platform
    if platform == 'win32':
        cur_platform = 'windows'
    elif platform == 'darwin':
        cur_platform = platform
    elif 'linux' in platform:
        cur_platform = 'linux'
    else:
        print('Your platform is not supported!')
        sys.exit(1)

    x86_llvm_path = ""
    x64_llvm_path = os.path.abspath(os.path.join(ndk_root, 'toolchains/llvm/prebuilt', '%s-%s' % (cur_platform, 'x86_64')))
    if not os.path.exists(x64_llvm_path):
        x86_llvm_path = os.path.abspath(os.path.join(ndk_root, 'toolchains/llvm/prebuilt', '%s' % (cur_platform)))
    if not os.path.exists(x86_llvm_path):
        x86_llvm_path = os.path.abspath(os.path.join(ndk_root, 'toolchains/llvm/prebuilt', '%s-%s' % (cur_platform, 'x86')))

    if os.path.isdir(x64_llvm_path):
        llvm_path = x64_llvm_path
    elif os.path.isdir(x86_llvm_path):
        llvm_path = x86_llvm_path
    else:
        print('llvm toolchain not found!')
        print('path: %s or path: %s are not valid! ' % (x86_llvm_path, x64_llvm_path))
        sys.exit(1)

    x86_gcc_toolchain_path = ""
    x64_gcc_toolchain_path = os.path.abspath(os.path.join(ndk_root, 'toolchains/arm-linux-androideabi-4.9/prebuilt', '%s-%s' % (cur_platform, 'x86_64')))
    if not os.path.exists(x64_gcc_toolchain_path):
        x86_gcc_toolchain_path = os.path.abspath(os.path.join(ndk_root, 'toolchains/arm-linux-androideabi-4.9/prebuilt', '%s' % (cur_platform)))
    if not os.path.exists(x86_gcc_toolchain_path):
        x86_gcc_toolchain_path = os.path.abspath(os.path.join(ndk_root, 'toolchains/arm-linux-androideabi-4.9/prebuilt', '%s-%s' % (cur_platform, 'x86')))

    if os.path.isdir(x64_gcc_toolchain_path):
        gcc_toolchain_path = x64_gcc_toolchain_path
    elif os.path.isdir(x86_gcc_toolchain_path):
        gcc_toolchain_path = x86_gcc_toolchain_path
    else:
        print('gcc toolchain not found!')
        print('path: %s or path: %s are not valid! ' % (x64_gcc_toolchain_path, x86_gcc_toolchain_path))
        sys.exit(1)


    project_root = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
    cocos_root = os.path.abspath(os.path.join(project_root, ''))
    cxx_generator_root = os.path.abspath(os.path.join(project_root, 'tools/bindings-generator'))

    extraFlags = _defaultIncludePath()

    # save config to file
    if(sys.version_info.major >= 3):
        import configparser # import ConfigParser
        config = configparser.ConfigParser()
    else:
        import ConfigParser
        config = ConfigParser.ConfigParser()

    config.set('DEFAULT', 'androidndkdir', ndk_root)
    config.set('DEFAULT', 'clangllvmdir', llvm_path)
    config.set('DEFAULT', 'gcc_toolchain_dir', gcc_toolchain_path)
    config.set('DEFAULT', 'cocosdir', cocos_root)
    config.set('DEFAULT', 'cxxgeneratordir', cxx_generator_root)
    config.set('DEFAULT', 'extra_flags', extraFlags)

    conf_ini_file = os.path.abspath(os.path.join(os.path.dirname(__file__), 'userconf.ini'))

    print('generating userconf.ini...')
    with open(conf_ini_file, 'w') as configfile:
      config.write(configfile)


    # set proper environment variables
    if 'linux' in platform or platform == 'darwin':
        os.putenv('LD_LIBRARY_PATH', '%s/libclang' % cxx_generator_root)
    if platform == 'win32':
        path_env = os.environ['PATH']
        os.putenv('PATH', r'%s;%s\libclang;%s\tools\win32;' % (path_env, cxx_generator_root, cxx_generator_root))


    try:

        tolua_root = '%s/tools/tolua' % project_root
        output_dir = '%s/extensions/scripting/lua-bindings/auto' % project_root

        cmd_args = {
                    'cocos2dx.ini' : ('Core', 'CCRegisterLuaCoreAuto'), \
                    'cocos2dx_backend.ini' : ('Backend', 'CCRegisterLuaBackendAuto'), \
                    'cocos2dx_extension.ini' : ('Extension', 'CCRegisterLuaExtensionAuto'), \
                    'cocos2dx_ui.ini' : ('UI', 'CCRegisterLuaUIAuto'), \
                    'cocos2dx_studio.ini' : ('Studio', 'CCRegisterLuaStudioAuto'), \
                    'cocos2dx_spine.ini' : ('Spine', 'CCRegisterLuaSpineAuto'), \
                    'cocos2dx_physics.ini' : ('Physics', 'CCRegisterLuaPhysicsAuto'), \
                    'cocos2dx_videoplayer.ini' : ('VideoPlayer', 'CCRegisterLuaVideoPlayerAuto'), \
                    'cocos2dx_controller.ini' : ('Controller', 'CCRegisterLuaControllerAuto'), \
                    'cocos2dx_3d.ini': ('3D', 'CCRegisterLua3DAuto'), \
                    'cocos2dx_audioengine.ini': ('AudioEngine', 'CCRegisterLuaAudioEngineAuto'), \
                    'cocos2dx_csloader.ini' : ('CSLoader', 'CCRegisterLuaCSLoaderAuto'), \
                    'cocos2dx_webview.ini' : ('WebView', 'CCRegisterLuaWebViewAuto'), \
                    'cocos2dx_physics3d.ini' : ('Physics3d', 'CCRegisterLuaPhysics3DAuto'), \
                    'cocos2dx_navmesh.ini' : ('NavMesh', 'CCRegisterLuaNavMeshAuto'), \
                    }
        target = 'lua'
        generator_py = '%s/generator.py' % cxx_generator_root
        for key in cmd_args.keys():
            args = cmd_args[key]
            cfg = '%s/%s' % (tolua_root, key)
            print('Generating bindings for %s...' % (key[:-4]))
            command = '%s %s %s -s %s -t %s -o %s -n %s' % (python_bin, generator_py, cfg, args[0], target, output_dir, args[1])
            print(command)
            _run_cmd(command)

        print('---------------------------------')
        print('Generating lua bindings succeeds.')
        print('---------------------------------')

    except Exception as e:
        if e.__class__.__name__ == 'CmdError':
            print('---------------------------------')
            print('Generating lua bindings fails.')
            print('---------------------------------')
            sys.exit(1)
        else:
            raise


# -------------- main --------------
if __name__ == '__main__':
    main()
