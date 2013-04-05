#ifndef __TC_TCDRAWER_H__
#define __TC_TCDRAWER_H__
#include "TextureRegion.h"
#include "BaseComponent.h"
#include "TCPaint.h"


NS_TC_BEGIN

class RenderElement;

class TCDrawer:public BaseComponent{

private:
	Paint _paint;
	RenderElement* _renderElement;

private:
	~TCDrawer();
	TCDrawer();

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

	void setRenderElement(RenderElement* e);

	inline RenderElement* renderElement(){
		return _renderElement;
	}

	void draw(const TCMatrix3x3& matrix);


	static TCDrawer* alloc();
};

NS_TC_END
#endif