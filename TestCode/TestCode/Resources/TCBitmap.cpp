#include "TCBitmap.h"
#include "TCFileUtils.h"
#include "TCPngUtils.h"
#if TC_TARGET_PLATFORM==TC_PLATFORM_ANDROID
#include "TCAndroidSystemInfo.h"
#endif
NS_TC_BEGIN

TCBitmap::TCBitmap(const char* filename,png_byte* pixelData,int width,int height,BitmapFormat format){
	_filename=std::string(filename);
	_pixelData=pixelData;
	_imageWidth=width;
	_imageHeight=height;
	_format=format;
}
TCBitmap::~TCBitmap(){
	TC_DELETE_ARRAY(_pixelData);
	DebugLog("Destroy bitmap:%s",_filename.c_str());
}
TCBitmap* TCBitmap::decodeBitmap(std::string filePath,BitmapFormat format){
	std::string fullPath(filePath);

	TCBitmap* ret=NULL;
#if TC_TARGET_PLATFORM==TC_PLATFORM_ANDROID//!android的apk是一个zip文件，必须从apk里读取图片
	ret =TCPngUtils::decodePngByFileNameInZip(AndroidSystemInfo::sourceDir().c_str(),fullPath.c_str());
#else
	ret=TCPngUtils::decodePngByFileName(fullPath.c_str());
#endif
	if(ret==0){
		DebugLog("decode bitmap failed!!!!,%s",filePath.c_str());
		return 0;
	}
	if(format==RGBA_8888){
		return ret;
	}
	else if(format==RGBA_4444){
		DebugLog("convert bitmap to rgba4444");
		ret->convertToRGBA4444();
		return ret;
	}
	else if(format==RGB_565){
		DebugLog("convert bitmap to rgb565");
		ret->convertToRGB565();
		return ret;
	}
	DebugLog("convert bitmap failed:unknown format");
	return ret;
}


NS_TC_END