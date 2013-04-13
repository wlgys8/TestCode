#ifndef __TC_ANDROID_SYSTEM_INFO_H__
#define __TC_ANDROID_SYSTEM_INFO_H__

#include "TCCommon.h"
#include <string>

NS_TC_BEGIN

class AndroidSystemInfo{

private:
	static std::string _sourceDir;
	static std::string _cacheDir;
	static std::string _fileDir;
public:
	static inline const std::string& sourceDir(){
		return _sourceDir;
	}
	static inline const std::string& cacheDir(){
		return _cacheDir;
	}
	static inline const std::string& fileDir(){
		return _fileDir;
	}

	static void init();

};

NS_TC_END

#endif