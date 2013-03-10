#ifndef __TC_TCDRAWER_H__
#define __TC_TCDRAWER_H__
#include "TextureRegion.h"
#include "BaseComponent.h"
#include "TCPaint.h"
NS_TC_BEGIN

class TCDrawer:public BaseComponent{

private:
	TextureRegion* _region;
	Paint _paint;
private:
	~TCDrawer();
	TCDrawer(TextureRegion* region);

public:
	inline virtual enum ComponentType type(){
		return ComponentDrawer;
	}
	inline void setPaint(const Paint& paint){
		_paint=paint;
	}
	inline Paint& paint() {
		return _paint;
	}  
	void draw(const TCMatrix3x3& matrix);

	Vector2f size(){
		if(!_region){
			return Vector2f();
		}
		return Vector2f(_region->width(),_region->height());
	}
	inline void setTextureRegion(TextureRegion* region){
		if(_region){
			_region->release();
		}
		if(region){
			region->retain();
		}
		_region=region;
	}
	static TCDrawer* alloc(TextureRegion* region);
};

NS_TC_END
#endif