#include "RenderElements/TCRectRenderElement.h"
#include "TCSceneRenderer.h"

NS_TC_BEGIN

static Vector2f vertex[4];

RectRenderElement::RectRenderElement(){

}

Vector2f RectRenderElement::rawSize(){
	return _rawSize;
}

void RectRenderElement::onRender(const TCMatrix3x3& localToWorldMatrix,const Paint& paint){
	float width=_rawSize.x;
	float height=_rawSize.y;
	float left=-width/2;
	float right=width/2;
	float bottom=-height/2;
	float top=height/2;
	vertex[0]=localToWorldMatrix.mulWithPoint(Vector2f(left,bottom));
	vertex[1]=localToWorldMatrix.mulWithPoint(Vector2f(right,bottom));
	vertex[2]=localToWorldMatrix.mulWithPoint(Vector2f(right,top));
	vertex[3]=localToWorldMatrix.mulWithPoint(Vector2f(left,top));
	TCSceneRenderer::instance()->renderSolidRect(vertex,paint);
}

void RectRenderElement::setRawSize(const Vector2f& rawSize){
	_rawSize=rawSize;
}

RectRenderElement::~RectRenderElement(){


}
NS_TC_END