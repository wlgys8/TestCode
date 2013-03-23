#ifndef __JNI_HELPER_H__
#define __JNI_HELPER_H__
#include "TCAndroidMacros.h"
#include "TCCommon.h"
#include <jni.h>
#include <string>
#include "Android/TCAndroidObject.h"
NS_TC_BEGIN

#if TC_TARGET_PLATFORM==TC_PLATFORM_ANDROID


template<class T1>
std::string JNI_SIGNATURE1(T1 p1){
	assert(0);
	return "";
}
#define DECLARE_JNI_SIGNATURE1(CLASSNAME,TYPEVALUE) \
template<> \
 std::string JNI_SIGNATURE1<CLASSNAME>(CLASSNAME p1){ \
	return TYPEVALUE; \
}

template<>
std::string JNI_SIGNATURE1<AndroidObject*>(AndroidObject* p1){ 
	return p1->className();
}

DECLARE_JNI_SIGNATURE1(int,"I");
DECLARE_JNI_SIGNATURE1(bool,"Z");
DECLARE_JNI_SIGNATURE1(char,"C");
DECLARE_JNI_SIGNATURE1(short,"S");
DECLARE_JNI_SIGNATURE1(long,"J");
DECLARE_JNI_SIGNATURE1(float,"F");
DECLARE_JNI_SIGNATURE1(double,"D");

#undef DECLARE_JNI_SIGNATURE1

template<class T1,class T2,class T3,class T4>
void  JNI_SIGNATURE(std::string* outSignature,T1 p1,T2 p2,T3 p3, T4 p4){
	const std::string& ps1=JNI_SIGNATURE1(p1);
	const std::string& ps2=JNI_SIGNATURE1(p2);
	const std::string& ps3=JNI_SIGNATURE1(p3);
	const std::string& ps4=JNI_SIGNATURE1(p4);
	*outSignature=(ps1+ps2+ps3+ps4);
}

template<class T>
struct JNI_VALUE{
	
};

template<>
struct JNI_VALUE<AndroidObject>{
	static jobject c2j(AndroidObject o){
		return o.rawObject();
	}
};

#define DECLARE_JNI_VALUE(CCLASS,JCLASS) \
	template<> \
	struct JNI_VALUE<CCLASS>{ \
		static JCLASS c2j(CCLASS o){ \
			return (JCLASS)(o); \
		} \
	};

DECLARE_JNI_VALUE(int,jint)
DECLARE_JNI_VALUE(float,jfloat)
DECLARE_JNI_VALUE(bool,jboolean)
DECLARE_JNI_VALUE(short,jshort)
DECLARE_JNI_VALUE(double,jdouble)
DECLARE_JNI_VALUE(long,jlong)


template<class R>
struct JNI_STATIC_METHOD_PTR{
	static int ptr(){
		assert(0);
		return 0;
	}
};



#define DECLARE_JNI_METHOD(RETURN_TYPE,METHOD_NAME) \
	typedef RETURN_TYPE (JNIEnv::*JNI_CallStatic##METHOD_NAME##MethodPrt)(jclass clazz,jmethodID id,...); \
	template<> \
	struct JNI_STATIC_METHOD_PTR<RETURN_TYPE>{ \
		static JNI_CallStatic##METHOD_NAME##MethodPrt ptr(){ \
			return (JNI_CallStatic##METHOD_NAME##MethodPrt)(&JNIEnv::CallStatic##METHOD_NAME##Method); \
		} \
	};

DECLARE_JNI_METHOD(jint,Int)
DECLARE_JNI_METHOD(jfloat,Float)
DECLARE_JNI_METHOD(jboolean,Boolean)
DECLARE_JNI_METHOD(jshort,Short)
DECLARE_JNI_METHOD(jdouble,Double)
DECLARE_JNI_METHOD(jlong,Long)
DECLARE_JNI_METHOD(jobject,Object)


class JNIHelper{

private:
	static JavaVM* _javavm;

public:
	static void setJavaVM(JavaVM *javaVM);
	static JavaVM* getJavaVM();
	static JNIEnv* getEnv();
	static jclass getStaticClass(const char *className);

	static jmethodID getStaticMethod(jclass clazz,const char* methodName,const char* paramCode);

	static jmethodID getStaticMethod(const char* className,const char* methodName,const char* paramCode);

	static void callStaticVoidMethod(const char* className,const char* methodName);

	template<class T1,class T2,class T3,class T4>
	static void callStaticVoidMethod(jclass clazz,const char* methodName,T1 p1,T2 p2,T3 p3,T4 p4);

	template<class T1,class T2,class T3,class T4>
	static void callStaticVoidMethod(const char* className,const char* methodName,T1 p1,T2 p2,T3 p3,T4 p4);


	template<class R,class T1,class T2,class T3,class T4>
	static R callStaticMethod(jclass clazz,const char* methodName,const std::string& returnSignature,T1 p1,T2 p2,T3 p3,T4 p4);

	template<class R,class T1,class T2,class T3,class T4>
	static R callStaticMethod(const char* className,const char* methodName,const std::string& returnSignature,T1 p1,T2 p2,T3 p3,T4 p4);
};

template<class T1,class T2,class T3,class T4>
void JNIHelper::callStaticVoidMethod(jclass clazz,const char* methodName,T1 p1,T2 p2,T3 p3,T4 p4){
	std::string signature;
	JNI_SIGNATURE<T1,T2,T3,T4>(&signature,p1,p2,p3,p4);
	signature="("+signature+")V";
	jmethodID methodID=JNIHelper::getStaticMethod(clazz,methodName,signature.c_str());

	JNIHelper::getEnv()->CallStaticVoidMethod(clazz,methodID,
		JNI_VALUE<T1>::c2j(p1),
		JNI_VALUE<T2>::c2j(p2),
		JNI_VALUE<T3>::c2j(p3),
		JNI_VALUE<T4>::c2j(p4));
}


template<class T1,class T2,class T3,class T4>
void JNIHelper::callStaticVoidMethod(const char* className,const char* methodName,T1 p1,T2 p2,T3 p3,T4 p4){
	jclass clazz=JNIHelper::getStaticClass(className);
	if(!clazz){
		return;
	}
	callStaticVoidMethod<T1,T2,T3,T4>(clazz,methodName,p1,p2,p3,p4);
}

template<class R,class T1,class T2,class T3,class T4>
R JNIHelper:: callStaticMethod(jclass clazz,const char* methodName,const std::string& returnSignature,T1 p1,T2 p2,T3 p3,T4 p4){
	std::string signature;
	JNI_SIGNATURE<T1,T2,T3,T4>(&signature,p1,p2,p3,p4);
	signature="("+signature+")"+returnSignature;
	jmethodID methodID=JNIHelper::getStaticMethod(clazz,methodName,signature.c_str());
	JNIEnv* env=JNIHelper::getEnv();
	R ret=(env->*JNI_STATIC_METHOD_PTR<jint>::ptr())(clazz,methodID,
		JNI_VALUE<T1>::c2j(p1),
		JNI_VALUE<T2>::c2j(p2),
		JNI_VALUE<T3>::c2j(p3),
		JNI_VALUE<T4>::c2j(p4)		
		);
	return ret;
}

template<class R,class T1,class T2,class T3,class T4>
R JNIHelper::callStaticMethod(const char* className,const char* methodName,const std::string& returnSignature,T1 p1,T2 p2,T3 p3,T4 p4){
	jclass clazz=JNIHelper::getStaticClass(className);
	if(!clazz){
		return 0;
	}
	return callStaticMethod<R,T1,T2,T3,T4>(clazz,methodName,returnSignature,p1,p2,p3,p4);
}
#endif//TC_TARGET_PLATFORM==TC_PLATFORM_ANDROID

NS_TC_END

#endif//!__JNI_HELPER_H__