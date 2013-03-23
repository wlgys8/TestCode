#include "TCAndroidClass.h"

#if TC_TARGET_PLATFORM==TC_PLATFORM_ANDROID

AndroidClass::AndroidClass(const std::string& className):_className(className){
	_clazz=JNIHelper::getStaticClass(className);
}

#endif