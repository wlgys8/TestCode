#ifndef __TC_TEXTURE_REGION_H__
#define __TC_TEXTURE_REGION_H__
#include "TCCommon.h"
#include "AutoReleaseObject.h"
#include "TCTexture.h"
#include "TCTextureRegionManager.h"
NS_TC_BEGIN

class TextureRegion:public AutoReleaseObject{
	friend class TextureRegionManager;
public:

private:
	Rect _region;
	TCTexture* _texture;
	std::string _name;
	TextureRegion(const std::string& name,TCTexture* tex,float left,float bottom,float width,float height):AutoReleaseObject(){
		_texture=tex;
		_region=Rect(left,bottom,width,height);
		_texture->retain();
		_name=name;
	//	DebugLog("new TextureRegion"); 
	}
	~TextureRegion(){
		if(_texture){
			_texture->release();
			_texture=0;
		}
//		DebugLog("delete a TextureRegion");
	}
public: 
	inline int textureID() const{
		return _texture->id();
	}
	inline const std::string& name() const{
		return _name;
	}
	inline float width() const{
		return _texture->width()*_region.width();
	}
	inline float height() const{
		return _texture->height()*_region.height();
	}
	inline const Rect& region() const{
		return _region;
	}
	//only for debug
	void drawAt(float x,float y){
		_texture->drawAt(x,y,_region);
	}


};
NS_TC_END
#endif