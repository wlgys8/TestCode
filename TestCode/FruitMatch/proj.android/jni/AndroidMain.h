#ifndef _TC_ANDROIDMAIN_H__
#define _TC_ANDROIDMAIN_H__
#include<jni.h>

#ifdef __cplusplus
	extern "C" {
#endif
	JNIEXPORT
	jint
	JNICALL																	  
	Java_com_testcode_fruitmatch_FruitMatchActivity_play( JNIEnv* env,
	jobject thiz );

#ifdef __cplusplus
}
#endif//!_cplusplus

#endif//!__TC_ANDROIDMAIN_H__