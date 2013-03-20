#ifndef __JNI_HELPER_H__
#define __JNI_HELPER_H__
#include "TCMacros.h"
#include "TCCommon.h"
#include <jni.h>
NS_TC_BEGIN



#if TC_TARGET_PLATFORM==TC_PLATFORM_ANDROID


class JNIHelper{

private:
	static JavaVM* _javavm;
public:
	static void setJavaVM(JavaVM *javaVM);
	static JavaVM* getJavaVM();
	static JNIEnv* getEnv();
	static jclass getStaticClass(const char *className);

	static jmethodID getStaticMethod(jclass clazz,const char* methodName,const char* paramCode);


};


#endif//!TC_PLATFORM_ANDROID

NS_TC_END

#endif//!__JNI_HELPER_H__