#ifndef __TC_TEXTURE_H__
#define __TC_TEXTURE_H__
#include <string>
#include "TCCommon.h"
#include "TCBitmap.h"
#include "Rect.h"
#include "AutoReleaseObject.h"

NS_TC_BEGIN
class TCBitmap;

class TCTexture:public AutoReleaseObject{
//=======static======//
private:
	static float _vertexArray[8];
	static float _textureArray[8];
	static unsigned short _indices[6];
public:
	static TCTexture* createTextureFromBitmap(TCBitmap* bitmap);
//=======class======//
private:
	std::string _filename;
	unsigned int _texId;
	int _width;
	int _height;
private:
	TCTexture();
	~TCTexture();
public:
	//return an autoRelease texture!!

	inline int width() const{
		return _width;
	}
	inline int height() const{
		return _height;
	}
	inline unsigned int id() const{
		return _texId;
	}
	inline bool isRecycled() const{
		return _texId==0;
	}
	void recycle();//
	void drawAt(float x,float y, const Rect& src);
};

NS_TC_END
#endif