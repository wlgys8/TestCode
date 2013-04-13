#ifndef __TC_FILEUTILS_H__
#define __TC_FILEUTILS_H__
#include "TCCommon.h"
#include "DataStream.h"
NS_TC_BEGIN
class TCFileUtils{
private:
public:
	static DataStream* getFileDataFromZip(const char* pszZipFilePath, const char* pszFileName);
	static DataStream* getFileData(const char* filePath);

};
NS_TC_END
#endif