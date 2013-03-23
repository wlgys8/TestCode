#ifndef _TC_ANDROIDMAIN_H__
#define _TC_ANDROIDMAIN_H__

#include "TCMacros.h"


#if TC_TARGET_PLATFORM==TC_PLATFORM_ANDROID

#include<jni.h>

#ifdef __cplusplus
	extern "C" {
#endif
	JNIEXPORT
	jint
	JNICALL																	  
	Java_com_testcode_fruitmatch_FruitMatchActivity_play( JNIEnv* env,
	jobject thiz );

	JNIEXPORT
		void
		JNICALL																	  
		Java_com_testcode_library_TCRender_nativeInit( JNIEnv* env,
		jobject thiz,int width,int height );

	JNIEXPORT
		void
		JNICALL																	  
		Java_com_testcode_library_TCRender_nativeRender( JNIEnv* env,
		jobject thiz );

	void test();
	jint JNI_OnLoad(JavaVM *vm, void *reserved);

#ifdef __cplusplus
}
#endif//!_cplusplus

#endif

#endif//!__TC_ANDROIDMAIN_H__