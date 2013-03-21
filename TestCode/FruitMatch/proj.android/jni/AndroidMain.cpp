#include "AndroidMain.h"
#include "Audio/AudioManager.h"
#include "TCMacros.h"
#include "JNIHelper.h"
#if TC_TARGET_PLATFORM==TC_PLATFORM_ANDROID

USING_NS_TC;
JNIEXPORT
	jint
	JNICALL																	  
	Java_com_testcode_fruitmatch_FruitMatchActivity_play( JNIEnv* env,
	jobject thiz ){
	AudioManager::instance()->load("/sdcard/helloworld.wav");
	AudioManager::instance()->play("/sdcard/helloworld.wav");
	test();
	return 0;
}

extern "C"{
	void test(){
		jclass clazz=JNIHelper::getStaticClass("com/testcode/fruitmatch/FruitMatchActivity");
		jmethodID method= JNIHelper::getStaticMethod(clazz,"test","()V");
		JNIEnv* env= JNIHelper::getEnv();
		env->CallStaticVoidMethod(clazz,method);
	}
	jint JNI_OnLoad(JavaVM *vm, void *reserved){
		JNIHelper::setJavaVM(vm);
		return JNI_VERSION_1_4;
	}
}
#endif





