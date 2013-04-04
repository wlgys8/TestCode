#include "jni/JNIHelper.h"


USING_NS_TC;

#if TC_TARGET_PLATFORM==TC_PLATFORM_ANDROID

#define JAVAVM testCode::JNIHelper::getJavaVM()

JavaVM* JNIHelper::_javavm=0;

extern "C"{

static JNIEnv* getEnv_(){
	JNIEnv* pRet=0;
	if (JAVAVM->GetEnv((void**)&pRet, JNI_VERSION_1_4) != JNI_OK)
	{
		DebugLog("Failed to get the environment using GetEnv()");
		return 0;
	}

	if (JAVAVM->AttachCurrentThread(&pRet, 0) < 0)
	{
		DebugLog("Failed to get the environment using AttachCurrentThread()");
		return 0;
	}
	return pRet;

}

static jclass getClassID_(const char *className)
{
	JNIEnv *pEnv = getEnv_();
	if(!pEnv){
		return 0;
	}
	jclass clazz = 0;
	clazz = pEnv->FindClass(className);
	if(!clazz){
		DebugLog("Failed to find class of %s", className);
		return 0;
	}
	return clazz;
}

static jmethodID getStaticMethodIDByClazz_(jclass clazz,const char* methodName,const char* paramCode){
	JNIEnv *pEnv = getEnv_();
	if(!pEnv){
		return 0;
	}
	jmethodID ret=0;
	ret = pEnv->GetStaticMethodID(clazz, methodName, paramCode);
	if(!ret){
		DebugLog("Failed to find static method id of %s", methodName);
		return 0;
	}
	return ret;
}

static jmethodID getStaticMethodIDByName_(const char* className,const char* methodName,const char* paramCode){
	JNIEnv *pEnv = getEnv_();
	if(!pEnv){
		return 0;
	}
	jclass clazz=0;
	
	clazz = pEnv->FindClass(className);
	if(!clazz){
		DebugLog("Failed to find class of %s", className);
		return 0;
	}
	jmethodID methodID= pEnv->GetStaticMethodID(clazz, methodName, paramCode);
	if(!methodID){
		DebugLog("Failed to find static method id of %s", methodName);
		return 0;
	}
	return methodID;
}

}

NS_TC_BEGIN

void JNIHelper::setJavaVM(JavaVM* javaVM){
	_javavm=javaVM;
}

JavaVM* JNIHelper::getJavaVM(){
	return _javavm;
}

jclass JNIHelper::getStaticClass(const char *className){
	return getClassID_(className);
}

jmethodID JNIHelper::getStaticMethod(jclass clazz,const char* methodName,const char* paramCode){
	getStaticMethodIDByClazz_(clazz,methodName,paramCode);
}

JNIEnv* JNIHelper::getEnv(){
	return getEnv_();
}
jmethodID JNIHelper::getStaticMethod(const char* className,const char* methodName,const char* paramCode){
	return getStaticMethodIDByName_(className,methodName,paramCode);
}
void JNIHelper::callStaticVoidMethod(const char* className,const char* methodName){
	jclass clazz=getStaticClass(className);
	jmethodID methodID=getStaticMethod(clazz,methodName,"()V");
	getEnv()->CallStaticVoidMethod(clazz,methodID);
}

NS_TC_END

#endif//#if TC_TARGET_PLATFORM==TC_PLATFORM_ANDROID

