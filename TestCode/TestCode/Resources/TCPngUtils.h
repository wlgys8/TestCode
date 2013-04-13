#ifndef __TC_PNG_UTILS_H__
#define __TC_PNG_UTILS_H__
#include "TCBitmap.h"
#include "DataStream.h"
NS_TC_BEGIN

typedef struct {
		png_byte* data;
		png_size_t size;
		int offset;
}ImageSource;

class TCPngUtils
{
public:
	static TCBitmap* decodePngByFileName(const char* filename);
	static TCBitmap* decodePngByFileData(const char* bitmapName,DataStream * pData);
	static TCBitmap* decodePngByFileNameInZip(const char* zipPath,const char* filename);
	
};

NS_TC_END
#endif