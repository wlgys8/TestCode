#ifndef __TC_SPRITE_RENDER_ELEMENT_H__
#define __TC_SPRITE_RENDER_ELEMENT_H__

#include "RenderElements/TCRenderElement.h"

#include "Rect.h"


NS_TC_BEGIN
class TextureRegion;

class SpriteRenderElement:public RenderElement{

private:
	TextureRegion* _region;
	Rect _part;
private:

	SpriteRenderElement(TextureRegion* region);
	~SpriteRenderElement();

public:
	//====override methoid begin====
	void onRender(const TCMatrix3x3& localToWorldMatrix,const Paint& paint);


	Vector2f rawSize();

	//====override method end====
	void setTextureRegion(TextureRegion* region);

	inline const Rect& part() const{
		return _part;
	}
	inline void setPart(const Rect& part){
		_part=part;
	}

	static SpriteRenderElement* alloc(TextureRegion* region){
		SpriteRenderElement* ret=new SpriteRenderElement(region);
		ret->autoRelease();
		return ret;
	}
};

NS_TC_END

#endif


