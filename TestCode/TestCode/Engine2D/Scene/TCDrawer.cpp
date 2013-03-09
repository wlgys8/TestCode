#include "TCDrawer.h"
#include "TCTransform.h"
#include "TCSceneRenderer.h"
NS_TC_BEGIN

void TCDrawer::draw(const TCMatrix3x3& localToWorldMatrix){
	if(!_region){
		return;
	}
	Vector2f* vertex=new Vector2f[4];
	float width=_region->width();
	float height=_region->height();
	Rect rect=_region->region();
	float x=0;
	float y=0;

	float result[3];
	{
		float point[3]={x-width/2,y-height/2,1};
		localToWorldMatrix.apply(result,point);
		vertex[0]=Vector2f(result[0],result[1]);
	}
	{
		float point[3]={x+width/2,y-height/2,1};
		localToWorldMatrix.apply(result,point);
		vertex[1]=Vector2f(result[0],result[1]);
	}
	{
		float point[3]={x+width/2,y+height/2,1};
		localToWorldMatrix.apply(result,point);
		vertex[2]=Vector2f(result[0],result[1]);
	}
	{
		float point[3]={x-width/2,y+height/2,1};
		localToWorldMatrix.apply(result,point);
		vertex[3]=Vector2f(result[0],result[1]);
	}

	Vector2f* uvs=new Vector2f[4];
	uvs[0]=Vector2f(rect.xMin(),rect.yMin());
	uvs[1]=Vector2f(rect.xMax(),rect.yMin());
	uvs[2]=Vector2f(rect.xMax(),rect.yMax());
	uvs[3]=Vector2f(rect.xMin(),rect.yMax());

	TCSceneRenderer::instance()->render(_region->textureID(),vertex,uvs,_paint);
	TC_DELETE_ARRAY(vertex);
	TC_DELETE_ARRAY(uvs);
}

TCDrawer::TCDrawer(TextureRegion* region){
	_region=region;
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