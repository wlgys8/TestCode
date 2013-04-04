#ifndef __TC_ANDROIDCLASS_H__
#define __TC_ANDROIDCLASS_H__

#include "TCCommon.h"
#include <string>
#if TC_TARGET_PLATFORM==TC_PLATFORM_ANDROID

#include <JNIHelper.h>

class AndroidClass{

private:
	std::string _className;
	jclass _clazz;
public:
	AndroidClass(const std::string& className);

	inline const std::string& className(){
		return _className;
	}
	template<class T1,class T2,class T3,class T4>
	void callStaticVoidMethod(const std::string& methodName,T1 p1,T2 p2,T3 p3,T4 p4);
};

template<class T1,class T2,class T3,class T4>
void AndroidClass::callStaticVoidMethod(const std::string& methodName,T1 p1,T2 p2,T3 p3,T4 p4){
	JNIHelper::callStaticVoidMethod(_clazz,methodName,p1,p2,p3,p4);
}

#endif//!TC_TARGET_PLATFORM==TC_PLATFORM_ANDROID



#endif