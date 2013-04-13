#include "IO/DirectoryUtil.h"

#ifdef _WINDOWS
#include <Windows.h>
#include <sstream>
#endif

NS_TC_BEGIN

#ifdef _WINDOWS
bool static createDirectory_(const std::string& path){
	std::wstringstream s;
	s<<path.c_str();
	return CreateDirectory(s.str().c_str(),0);
}

bool static existDirectory_(const std::string& path){
	DWORD ftyp = GetFileAttributesA(path.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!

	return false;    // this is not a directory!
}
#endif

bool DirectoryUtil::createDirectory(const std::string& path){
#ifdef _WINDOWS
	return createDirectory_(path);
#endif
	return false;
}

bool DirectoryUtil::exist(const std::string& path){
#ifdef _WINDOWS
	return existDirectory_(path);
#endif
	return false;
}

NS_TC_END