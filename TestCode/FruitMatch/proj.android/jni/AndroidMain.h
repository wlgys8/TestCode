#ifndef _TC_ANDROIDMAIN_H__
#define _TC_ANDROIDMAIN_H__


#ifdef __cplusplus
	extern "C" {
#endif
	JNIEXPORT
	jint
	JNICALL																	  
	Java_com_zilch_testcode_TestCodeActivity_nativeCreate( JNIEnv* env,
	jobject thiz );

#ifdef __cplusplus
}
#endif//!_cplusplus

#endif//!__TC_ANDROIDMAIN_H__