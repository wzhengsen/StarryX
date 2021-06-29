#!/bin/bash

# exit this script if any commmand fails
set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ADXE_ROOT="$DIR"/../..
COCOSFILE_PATH="$ADXE_ROOT/templates/cocos2dx_files.json"
CPU_CORES=4

function do_retry()
{
	cmd=$@
	retry_times=5
	retry_wait=3
	c=0
	while [ $c -lt $((retry_times+1)) ]; do
		c=$((c+1))
		echo "Executing \"$cmd\", try $c"
		$cmd && return $?
		if [ ! $c -eq $retry_times ]; then
			echo "Command failed, will retry in $retry_wait secs"
			sleep $retry_wait
		else
			echo "Command failed, giving up."
			return 1
		fi
	done
}

function build_linux()
{
    echo "Building tests ..."
    # source ../environment.sh
    cd $ADXE_ROOT
    set -x
    cmake . -G "Unix Makefiles" -Bbuild -DCMAKE_BUILD_TYPE=Release
    cmake --build build --target cpp-tests -- -j `nproc`
    set +x
}

function build_osx()
{
    NUM_OF_CORES=`getconf _NPROCESSORS_ONLN`

    # pushd $ADXE_ROOT
    # python -u tools/console/bin/adxe.py --agreement n new -l cpp -p my.pack.qqqq cocos_new_test
    # popd
    # cd $ADXE_ROOT/cocos_new_test
    cd $ADXE_ROOT
    mkdir -p build
    cmake -S . -B build -GXcode -DBUILD_EXTENSION_IMGUIEXT=ON -DBUILD_EXT_ALSOFT=ON
    cmake --build build --config Release --target cpp-tests -- -quiet
    #xcodebuild -project adxe.xcodeproj -alltargets -jobs $NUM_OF_CORES build  | xcpretty
    ##the following commands must not be removed
    #xcodebuild -project adxe.xcodeproj -alltargets -jobs $NUM_OF_CORES build
    exit 0
}

function build_ios()
{
    NUM_OF_CORES=`getconf _NPROCESSORS_ONLN`

    # pushd $ADXE_ROOT
    # python -u tools/console/bin/adxe.py --agreement n new -l cpp -p my.pack.qqqq cocos_new_test
    # popd
    # cd $ADXE_ROOT/cocos_new_test
    cd $ADXE_ROOT
    # mkdir -p build

    cmake -S . -B build -GXcode -DCMAKE_TOOLCHAIN_FILE=cmake/ios.mini.cmake -DCMAKE_OSX_ARCHITECTURES=x86_64 -DBUILD_EXT_ALSOFT=ON
    # cmake .. -GXcode -DCMAKE_TOOLCHAIN_FILE=../cmake/ios.toolchain.cmake -DCMAKE_SYSTEM_NAME=iOS -DPLATFORM=OS -DENABLE_ARC=0   # too much logs on console when "cmake --build ."
    cmake --build build --config Release --target cpp-tests -- -quiet -jobs $NUM_OF_CORES -destination "platform=iOS Simulator,name=iPhone Retina (4-inch)" 

    #xcodebuild -project adxe.xcodeproj -alltargets -jobs $NUM_OF_CORES  -destination "platform=iOS Simulator,name=iPhone Retina (4-inch)" build  | xcpretty
    ##the following commands must not be removed
    #xcodebuild -project adxe.xcodeproj -alltargets -jobs $NUM_OF_CORES  -destination "platform=iOS Simulator,name=iPhone Retina (4-inch)" build
    exit 0
}

function build_android()
{
    # Build all samples
    echo "Building Android samples ..."
    source ../environment.sh

    # build cpp-tests
    pushd $ADXE_ROOT/tests/cpp-tests/proj.android
    
    do_retry ./gradlew assembleRelease -PPROP_BUILD_TYPE=cmake -PPROP_APP_ABI=$BUILD_ARCH --parallel --info
    popd
}

function build_android_lua()
{
    # Build all samples
    echo "Building Android samples lua ..."
    source ../environment.sh

    # build lua-tests
    pushd $ADXE_ROOT/tests/lua-tests/project/proj.android
    do_retry ./gradlew assembleDebug -PPROP_BUILD_TYPE=cmake -PPROP_APP_ABI=arm64-v8a --parallel --info
    popd

}

function genernate_binding_codes()
{
    if [ $TRAVIS_OS_NAME == "linux" ]; then
        # print some log for libstdc++6
        strings /usr/lib/x86_64-linux-gnu/libstdc++.so.6 | grep GLIBC
        ls -l /usr/lib/x86_64-linux-gnu/libstdc++*
        dpkg-query -W libstdc++6
        ldd $ADXE_ROOT/tools/bindings-generator/libclang/libclang.so
    fi

    source ../environment.sh

    # Generate binding glue codes

    echo "Create auto-generated luabinding glue codes."
    pushd "$ADXE_ROOT/tools/tolua"
    # python ./genbindings.py
    popd
}

# generate cocos_files.json and check diff
function update_cocos_files()
{
    # Don't exit on non-zero return value
    set +e
    echo "Updates cocos_files.json"
    $ADXE_ROOT/tools/travis-scripts/generate-template-files.py
    git diff FETCH_HEAD --stat --exit-code "$COCOSFILE_PATH"
    COCOSFILE_DIFF_RETVAL=$?
    echo $COCOSFILE_DIFF_RETVAL

    # Exit on error
    set -e
}

function generate_pull_request_for_binding_codes_and_cocosfiles()
{
    local COCOS_ROBOT_REMOTE="https://${GH_USER}:${GH_PASSWORD}@github.com/${GH_USER}/adxe.git"
    local LUA_AUTO_GENERATE_SCRIPT_PATH="$ADXE_ROOT/extensions/scripting/lua-bindings/auto"
    local ELAPSEDSECS=`date +%s`
    local COCOS_BRANCH="update_lua_bindings_$ELAPSEDSECS"
    local COMMITTAG="[ci skip][AUTO]: updating luabinding & cocos_file.json automatically"
    local PULL_REQUEST_REPO="https://api.github.com/repos/cocos2d/cocos2d-x/pulls"

    pushd "$ADXE_ROOT"
    #Set git user for cocos2d-lua repo
    # git config user.email ${GH_EMAIL}
    # git config user.name ${GH_USER}#Set remotes
    # git remote add upstream "$COCOS_ROBOT_REMOTE" 2> /dev/null > /dev/null

    # Run status to record the output in the log
    git status

    echo
    echo Comparing with origin HEAD ...
    echo
    git fetch origin "$TRAVIS_BRANCH"

    # Don't exit on non-zero return value
    set +e
    git diff FETCH_HEAD --stat --exit-code "$LUA_AUTO_GENERATE_SCRIPT_PATH"
    local lua_binding_codes_diff=$?

    # generate cocos_files.json and check diff
    local cocos_file_diff=$(update_cocos_files)
    if [ $lua_binding_codes_diff -eq 0 ] && [ $cocos_file_diff -eq 0 ]; then
        echo "lua binding codes and cocos file are not differences"
        exit 0
    fi


    # Exit on error
    set -e

    # git add -f --all "$LUA_AUTO_GENERATE_SCRIPT_PATH"
    # git add -f --all "$COCOSFILE_PATH"
    # git checkout -b "$COCOS_BRANCH"
    # git commit -m "$COMMITTAG"

    echo "Pushing to Robot's repo ..."
    # git fetch --unshallow origin
    # git push -f upstream "$COCOS_BRANCH"

    echo "Sending Pull Request to base repo ..."
    # curl --user "${GH_USER}:${GH_PASSWORD}" --request POST --data "{ \"title\": \"$COMMITTAG\", \"body\": \"\", \"head\": \"${GH_USER}:${COCOS_BRANCH}\", \"base\": \"${TRAVIS_BRANCH}\"}" "${PULL_REQUEST_REPO}" 2> /dev/null > /dev/null

    popd
}

function run_pull_request()
{
    echo "Building pull request ..."

    if [ "$BUILD_TARGET" == "android_cocos_new_test" ]; then
        source ../environment.sh
        pushd $ADXE_ROOT
        update_cocos_files
        python -u tools/console/bin/adxe.py --agreement n new -l cpp -p my.pack.qqqq cocos_new_test
        popd
        pushd $ADXE_ROOT/cocos_new_test/proj.android
        do_retry ./gradlew build
        popd
        exit 0
    fi

    if [ "$BUILD_TARGET" == "linux_cocos_new_test" ]; then
        export PATH=$PATH:$ADXE_ROOT/tools/console/bin
        genernate_binding_codes
        pushd $ADXE_ROOT
        update_cocos_files
        python -u tools/console/bin/adxe.py --agreement n new -l lua -p my.pack.qqqq cocos_new_test
        popd
        echo "Building tests ..."

        set -x
        cd $ADXE_ROOT/cocos_new_test
        mkdir -p linux-build
        cd linux-build
        cmake .. -G"Unix Makefiles"
        cmake --build . -- -j `nproc`
        exit 0
    fi

    if [ "$BUILD_TARGET" == "ios_cocos_new_lua_test" ]; then
        export PATH=$PATH:$ADXE_ROOT/tools/console/bin
        #NUM_OF_CORES=`getconf _NPROCESSORS_ONLN`
        genernate_binding_codes
        pushd $ADXE_ROOT
        echo "Creating tests ..."

        set -x
        cocos --agreement n new -l lua ios_new_lua_proj
        cd ios_new_lua_proj
        mkdir build
        cd build
        cmake .. -GXcode -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_SYSROOT=iphonesimulator
        cmake --build . --config Release -- -quiet
        popd
        exit 0
    fi

    if [ "$BUILD_TARGET" == "ios_cocos_new_cpp_test" ]; then
        export PATH=$PATH:$ADXE_ROOT/tools/console/bin
        #NUM_OF_CORES=`getconf _NPROCESSORS_ONLN`
        genernate_binding_codes
        pushd $ADXE_ROOT
        echo "Creating tests ..."

        set -x
        cocos --agreement n new -l cpp ios_new_cpp_proj
        cd ios_new_cpp_proj
        mkdir build
        cd build
        echo "Building tests ..."
        cmake .. -GXcode -DCMAKE_SYSTEM_NAME=iOS -DCMAKE_OSX_SYSROOT=iphonesimulator
        cmake --build . --config Release -- -quiet 
        popd
        exit 0
    fi
    
    if [ $BUILD_TARGET == 'osx' ]; then
        # genernate_binding_codes
        set -x
        build_osx
        exit 0
    fi

    if [ $BUILD_TARGET == 'ios' ]; then
        # genernate_binding_codes
        set -x
        build_ios
        exit 0
    fi

    # linux
    if [ $BUILD_TARGET == 'linux' ]; then
        # genernate_binding_codes
        build_linux
    fi

    # android
    if [ $BUILD_TARGET == 'android' ]; then
        build_android
    fi

    # android_lua
    if [ $BUILD_TARGET == 'android_lua' ]; then
        genernate_binding_codes
        build_android_lua
    fi
}

function run_after_merge()
{
    echo "Building merge commit ..."
    # Re-generation of the javascript bindings can perform push of the new
    # version back to github.  We don't do this for pull requests, or if
    # GH_USER/GH_EMAIL/GH_PASSWORD environment variables are not set correctly
    # by the encoded variables in the .travis.yml file.  (e.g. if cloned repo's
    # want to use travis).
    # if [ -z "${GH_EMAIL}" ]; then
    #     echo "GH_EMAIL not set"
    #     exit 1
    # fi
    # if [ -z "${GH_USER}" ]; then
    #     echo "GH_USER not set"
    #     exit 1
    # fi
    # if [ -z "${GH_PASSWORD}" ]; then
    #     echo "GH_USER not set"
    #     exit 1
    # fi

    genernate_binding_codes
    generate_pull_request_for_binding_codes_and_cocosfiles
}

# build pull request
if [ "$TRAVIS_PULL_REQUEST" != "false" ]; then
    run_pull_request
fi

# run after merging
# - make cocos robot to send PR to cocos2d-x for new binding codes
# - generate cocos_files.json for template
if [ "$TRAVIS_PULL_REQUEST" == "false" ]; then
    # only one job need to send PR, linux virtual machine has better performance
    if [ $TRAVIS_OS_NAME == "linux" ] && [ x$GEN_BINDING_AND_COCOSFILE == x"true" ]; then
        run_after_merge
    fi
fi
