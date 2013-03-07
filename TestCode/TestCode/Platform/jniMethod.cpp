#include "jniMethod.h"
#include "TCRender.h"
#include "TCFileUtils.h"
#if (TC_TARGET_PLATFORM==TC_PLATFORM_ANDROID)


NS_TC_BEGIN

	static char* jstringTostring(JNIEnv* env, jstring jstr) 
{ 
	char* rtn = NULL; 
	jclass clsstring = env->FindClass("java/lang/String"); 
	jstring strencode = env->NewStringUTF("utf-8"); 
	jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B"); 
	jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr, mid, strencode); 
	jsize alen = env->GetArrayLength(barr); 
	jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE); 
	if (alen > 0) 
	{ 
		rtn = (char*)malloc(alen + 1); 
		memcpy(rtn, ba, alen); 
		rtn[alen] = 0; 
	} 
	env->ReleaseByteArrayElements(barr, ba, 0); 
	return rtn; 
}

JNIEXPORT jint JNICALL	Java_com_zilch_testcode_TCRender_nativeInit( JNIEnv* env,jobject thiz ){
	TCRender::instance()->onResize(480,854);
	return 0;
}
JNIEXPORT
	jint
	JNICALL																	  
	Java_com_zilch_testcode_TCRender_nativeRender( JNIEnv* env,
	jobject thiz ){
		TCRender::instance()->onRender();
		return 0;
}

JNIEXPORT
	jint
	JNICALL																	  
	Java_com_zilch_testcode_TestCodeActivity_nativeSetRootPath( JNIEnv* env,
	jobject thiz,jstring path){
		char* pathStr=jstringTostring(env,path);
		DebugLog(pathStr);
		TCFileUtils::setApkPath(pathStr);

}



NS_TC_END

#endif