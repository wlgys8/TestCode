#include "TCDrawer.h"
#include "TCTransform.h"
#include "TCSceneRenderer.h"
NS_TC_BEGIN

static Vector2f vertex[4];
static Vector2f uvs[4];

void TCDrawer::draw(const TCMatrix3x3& localToWorldMatrix){
	if(!_region){
		return;
	}
	float width=_region->width();
	float height=_region->height();
	const Rect& rect=_region->region();
	float left=-width/2+_part.xMin() *width;
	float right=-width/2+_part.xMax()*width;
	float bottom=-height/2+_part.yMin()*height;
	float top=-height/2+_part.yMax()*height;
	vertex[0]=localToWorldMatrix.mulWithPoint(Vector2f(left,bottom));
	vertex[1]=localToWorldMatrix.mulWithPoint(Vector2f(right,bottom));
	vertex[2]=localToWorldMatrix.mulWithPoint(Vector2f(right,top));
	vertex[3]=localToWorldMatrix.mulWithPoint(Vector2f(left,top));

	float uvLeft=rect.xMin()+_part.xMin()*rect.width();
	float uvRight=rect.xMin()+_part.xMax()*rect.width();
	float uvBottom=rect.yMin()+_part.yMin()*rect.height();
	float uvTop=rect.yMin()+_part.yMax()*rect.height();
	uvs[0]=Vector2f(uvLeft,uvBottom );
	uvs[1]=Vector2f(uvRight,uvBottom);
	uvs[2]=Vector2f(uvRight,uvTop);
	uvs[3]=Vector2f(uvLeft,uvTop);

	TCSceneRenderer::instance()->render(_region->textureID(),vertex,uvs,_paint);
}

TCDrawer::TCDrawer(TextureRegion* region){
	_region=region;
	_part=Rect(0,0,1,1);
	if(region){
		region->retain();
		return;
	}

}
TCDrawer::~TCDrawer(){
	if(_region){
		_region->release();
		_region=NULL;
	}
}

TCDrawer* TCDrawer::alloc(TextureRegion* region){
	TCDrawer* ret=new TCDrawer(region);
	ret->autoRelease();
	return ret;
}
NS_TC_END