#ifndef __TC_DIRECTORY_UTIL_H__
#define __TC_DIRECTORY_UTIL_H__
#include <string>
#include "TCCommon.h"
NS_TC_BEGIN
class DirectoryUtil{

public:
	static bool createDirectory(const std::string& path);
	static bool exist(const std::string& path);
};
NS_TC_END
#endif