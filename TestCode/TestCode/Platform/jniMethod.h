#ifndef __JNI_METHOD_H__
#define __JNI_METHOD_H__

#include "TCCommon.h"

#if (TC_TARGET_PLATFORM==TC_PLATFORM_ANDROID)
#include <stdlib.h>
#include <string.h>
#include <jni.h>

NS_TC_BEGIN

#ifdef __cplusplus
	extern "C" {
#endif
		JNIEXPORT
			jint
			JNICALL																	  
			Java_com_zilch_testcode_TCRender_nativeInit( JNIEnv* env,
			jobject thiz );
		JNIEXPORT
			jint
			JNICALL																	  
			Java_com_zilch_testcode_TCRender_nativeRender( JNIEnv* env,
			jobject thiz );
		JNIEXPORT
			jint
			JNICALL																	  
			Java_com_zilch_testcode_TestCodeActivity_nativeSetRootPath( JNIEnv* env,
			jobject thiz,jstring path);
#ifdef __cplusplus
}
#endif

NS_TC_END

#endif
#endif
