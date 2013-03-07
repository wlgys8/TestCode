#ifndef __TC_FILEUTILS_H__
#define __TC_FILEUTILS_H__
#include "TCCommon.h"
NS_TC_BEGIN
class TCFileUtils{
private:
	static char* _apkPath; //android apk path
public:
	static unsigned char* getFileDataFromZip(const char* pszZipFilePath, const char* pszFileName, unsigned long * pSize);
	static unsigned char* getFileData(const char* filePath,unsigned long* size);
	static inline void setApkPath( char* path){
		TCFileUtils::_apkPath=path;
	}
	static inline const char* apkPath(){
		return _apkPath;
	}
};
NS_TC_END
#endif