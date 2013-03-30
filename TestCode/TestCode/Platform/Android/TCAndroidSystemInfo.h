#ifndef __TC_ANDROID_SYSTEM_INFO_H__
#define __TC_ANDROID_SYSTEM_INFO_H__

#include "TCCommon.h"
#include <string>

NS_TC_BEGIN

class AndroidSystemInfo{

private:
	static std::string _sourceDir;
public:
	static inline const std::string& sourceDir(){
		return _sourceDir;
	}
	static void init();

};

NS_TC_END

#endif