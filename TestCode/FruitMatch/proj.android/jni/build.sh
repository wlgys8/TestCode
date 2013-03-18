NDK_ROOT_LOCAL=$NDKROOT

MY_TESTCODE_PATH=/cygdrive/d/developer/github/TestCode/TestCode/



export NDK_MODULE_PATH=$MY_TESTCODE_PATH/TestCode/third_part/android/prebuilt/:$MY_TESTCODE_PATH/:$NDKROOT/sources/cxx-stl/

HELLOWORLD_ROOT=$MY_TESTCODE_PATH/FruitMatch/proj.android/jni/
$NDK_ROOT_LOCAL/ndk-build clean
$NDK_ROOT_LOCAL/ndk-build -C $HELLOWORLD_ROOT
