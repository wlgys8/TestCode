#ifndef __TC_BITMAP_H__
#define __TC_BITMAP_H__


#include <stdlib.h>
#include <stdio.h>
#include <string>

#include "png.h"
#include "pngconf.h"
#include "TCCommon.h"
#include "TCTexture.h"
#include "AutoReleaseObject.h"
NS_TC_BEGIN
enum BitmapFormat{
	FORMAT_UNKNOWN=0,
	RGBA_8888=1,
	RGBA_4444=2,
	RGB_565=3,
};
class TCBitmap:AutoReleaseObject{
private:
	static std::string _resourcePath;
public:
	//default root path==$(project)/assets/
	//return an autoRelease bitmap!!
	static TCBitmap* decodeBitmap(std::string filePath,BitmapFormat format);
	static inline void setResourcePath(char* resPath){
		_resourcePath=resPath;
	}
	static inline bool checkIsPowerOf2(unsigned int value){
		while(value!=1){
			if(value%2!=0){
				return false;
			}
			value=value/2;
		}
		return true;
	}

	static inline unsigned char* convertRGBA8888ToRGBA4444(const unsigned char* pixels,unsigned int width,unsigned int height){
		unsigned char* ret = new unsigned char[width * height * 2];
		unsigned int* inPixel32 = (unsigned int*)pixels;
		unsigned short* outPixel16 = (unsigned short*)ret;

		unsigned int length = width * height;
		for(unsigned int i = 0; i < length; ++i, ++inPixel32)
		{
			*outPixel16++ = 
				((((*inPixel32 >> 0) & 0xFF) >> 4) << 12) | // R
				((((*inPixel32 >> 8) & 0xFF) >> 4) << 8) | // G
				((((*inPixel32 >> 16) & 0xFF) >> 4) << 4) | // B
				((((*inPixel32 >> 24) & 0xFF) >> 4) << 0); // A
		}
		return ret;
	}

	static inline unsigned char* convertRGBA8888ToRGB565(const unsigned char* pixels,unsigned int width,unsigned int height){
		unsigned char* ret = new unsigned char[width * height * 2];
		unsigned int* inPixel32 = (unsigned int*)pixels;
		unsigned short* outPixel16 = (unsigned short*)ret;

		unsigned int length = width * height;
		for(unsigned int i = 0; i < length; ++i, ++inPixel32)
		{
			*outPixel16++ = 
				((((*inPixel32 >> 0) & 0xFF) >> 3) << 11) |  // R
				((((*inPixel32 >> 8) & 0xFF) >> 2) << 5) |   // G
				((((*inPixel32 >> 16) & 0xFF) >> 3) << 0);   // B
		}
		return ret;
	}
private:
	png_byte* _pixelData;
	int _imageWidth;
	int _imageHeight;
	BitmapFormat _format;
	std::string _filename;

private:
	TCBitmap(const char* filename,png_byte* pixelData,int width,int height,BitmapFormat format);
	~TCBitmap();
public:
	friend class TCPngUtils;
	inline const unsigned char* pixelData(){
		return _pixelData;
	}
	inline int width(){
		return _imageWidth;
	}
	inline int height(){
		return _imageHeight;
	}

	inline const std::string &filename (){
		return _filename;
	}
	inline BitmapFormat format(){
		return _format;
	}
	inline bool isRecycled(){
		return _pixelData==NULL;
	}
	inline bool convertToRGBA4444(){
		if(_format==RGBA_8888){
			unsigned char* tempData=TCBitmap::convertRGBA8888ToRGBA4444(_pixelData,_imageWidth,_imageHeight);
			TC_DELETE_ARRAY(_pixelData);
			_pixelData=tempData;
			_format=RGBA_4444;
			return true;
		}
		else{
			DebugLog("Bitmap format is not RGBA8888,convert failed");
			return false;
		}
	}
	inline bool convertToRGB565(){
		if(_format==RGBA_8888){
			unsigned char* tempData=TCBitmap::convertRGBA8888ToRGB565(_pixelData,_imageWidth,_imageHeight);
			TC_DELETE_ARRAY(_pixelData);
			_pixelData=tempData;
			_format=RGB_565;
			return true;
		}
		else{
			DebugLog("Bitmap format is not RGB565,convert failed");
			return false;
		}
	}
};

NS_TC_END
#endif