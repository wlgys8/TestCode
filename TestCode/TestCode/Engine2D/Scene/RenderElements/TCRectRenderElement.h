#ifndef __TC_RECT_RENDER_ELEMENT_H__
#define __TC_RECT_RENDER_ELEMENT_H__


#include "RenderElements/TCRenderElement.h"

NS_TC_BEGIN

class RectRenderElement:public RenderElement{

private:
	Vector2f _rawSize;
private:

	RectRenderElement();
	~RectRenderElement();

public:
	//====override methoid begin====
	void onRender(const TCMatrix3x3& localToWorldMatrix,const Paint& paint);

	Vector2f rawSize();

	//====override method end====

	void setRawSize(const Vector2f& rawSize);

	static RectRenderElement* alloc(){
		RectRenderElement* ret=new RectRenderElement();
		ret->autoRelease();
		return ret;
	}

};

NS_TC_END
#endif