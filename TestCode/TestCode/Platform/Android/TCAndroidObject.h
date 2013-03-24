#ifndef __TC_ANDROID_OBJECT_H__
#define __TC_ANDROID_OBJECT_H__

#include "TCMacros.h"
#include "JNIHelper.h"
#include <string>
NS_TC_BEGIN

#if TC_TARGET_PLATFORM==TC_PLATFORM_ANDROID
class AndroidObject{
private:
	std::string _className;
	jobject _rawObject;
public:
	AndroidObject(const std::string& className,jobject rawObject){
		_className=className;
		_rawObject=rawObject;
	}
	 const std::string& className(){
		return _className;
	}

	 inline jobject rawObject(){
		 return _rawObject;
	 }
};

#endif

NS_TC_END
#endif