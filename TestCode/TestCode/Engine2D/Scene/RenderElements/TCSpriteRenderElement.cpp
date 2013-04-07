#include "TCSpriteRenderElement.h"
#include "TCSceneRenderer.h"
#include "TextureRegion.h"
#include "TCRenderUtil.h"

NS_TC_BEGIN

static Vector2f vertex[4];
static Vector2f uvs[4];

SpriteRenderElement::SpriteRenderElement(TextureRegion* region){
	_region=region;
	if(region){
		region->retain();
	}
	_part=Rect(0,0,1,1);
}
void SpriteRenderElement::setTextureRegion(TextureRegion* region){
	if(_region){
		_region->release();
	}
	if(region){
		region->retain();
	}
	_region=region;
}

Vector2f SpriteRenderElement::rawSize(){
	if(!_region){
		return Vector2f::zero();
	}
	return Vector2f(_region->width(),_region->height());
}
void SpriteRenderElement::onRender(const TCMatrix3x3& localToWorldMatrix,const Paint& paint){
	if(!_region){
		return;
	}
	float width=_region->width()*_part.width();
	float height=_region->height()*_part.height();
	
	float left=-_region->width()/2+_part.xMin() *_region->width();
	float bottom=-_region->height()/2+_part.yMin()*_region->height();

	const Rect& rect=_region->region();

	float uvLeft=rect.xMin()+_part.xMin()*rect.width();
	float uvBottom=rect.yMin()+_part.yMin()*rect.height();
	float uvWidth=rect.width()*_part.width();
	float uvHeight=rect.height()*_part.height();
	RenderUtil::renderImage(_region->textureID(),Rect(left,bottom,width,height),Rect(uvLeft,uvBottom,uvWidth,uvHeight),localToWorldMatrix,paint);

}

SpriteRenderElement::~SpriteRenderElement(){
	if(_region){
		_region->release();
		_region=NULL;
	}
}

NS_TC_END