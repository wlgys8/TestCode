#include "jni/JNIHelper.h"

USING_NS_TC;

#define JAVAVM testCode::JNIHelper::getJavaVM()

JavaVM* JNIHelper::_javavm=0;

extern "C"{
static bool getEnv_(JNIEnv **env)
{
	bool bRet = false;

	do 
	{
		if (JAVAVM->GetEnv((void**)env, JNI_VERSION_1_4) != JNI_OK)
		{
			DebugLog("Failed to get the environment using GetEnv()");
			break;
		}

		if (JAVAVM->AttachCurrentThread(env, 0) < 0)
		{
			DebugLog("Failed to get the environment using AttachCurrentThread()");
			break;
		}

		bRet = true;
	} while (0);		

	return bRet;
}

static jclass getClassID_(const char *className)
{
	JNIEnv *pEnv = 0;
	jclass ret = 0;

	do 
	{
		if (! pEnv)
		{
			if (! getEnv_(&pEnv))
			{
				break;
			}
		}

		ret = pEnv->FindClass(className);
		if (! ret)
		{
			DebugLog("Failed to find class of %s", className);
			break;
		}
	} while (0);

	return ret;
}

static jmethodID getStaticMethodID_(jclass clazz,const char* methodName,const char* paramCode){
	JNIEnv *pEnv = 0;
	jmethodID ret=0;
	if(!getEnv_(&pEnv)){
		return 0;
	}
	ret = pEnv->GetStaticMethodID(clazz, methodName, paramCode);
	if(!ret){
		DebugLog("Failed to find static method id of %s", methodName);
		return 0;
	}
	return ret;
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
	getStaticMethodID_(clazz,methodName,paramCode);
}
JNIEnv* JNIHelper::getEnv(){
	JNIEnv *pEnv = 0;
	if(!getEnv_(&pEnv)){
		return 0;
	}
	return pEnv;
}

NS_TC_END