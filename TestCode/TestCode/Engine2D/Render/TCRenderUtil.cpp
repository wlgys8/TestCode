#include "TCRenderUtil.h"
#include "TextureRegion.h"
#include "TCSceneRenderer.h"
NS_TC_BEGIN

static Vector2f vertex[4];
static Vector2f uvs[4];

void RenderUtil::renderImage(const int& textureID,const Rect& frame,const Rect& uv,const TCMatrix3x3& localToWorldMatrix,const Paint& paint){
	if(textureID<=0){
		return;
	}
	float left=frame.xMin();
	float right=frame.xMax();
	float bottom=frame.yMin();
	float top=frame.yMax();
	vertex[0]=localToWorldMatrix.mulWithPoint(Vector2f(left,bottom));
	vertex[1]=localToWorldMatrix.mulWithPoint(Vector2f(right,bottom));
	vertex[2]=localToWorldMatrix.mulWithPoint(Vector2f(right,top));
	vertex[3]=localToWorldMatrix.mulWithPoint(Vector2f(left,top));

	float uvLeft=uv.xMin();
	float uvRight=uv.xMax();
	float uvBottom=uv.yMin();
	float uvTop=uv.yMax();

	uvs[0]=Vector2f(uvLeft,uvBottom );
	uvs[1]=Vector2f(uvRight,uvBottom);
	uvs[2]=Vector2f(uvRight,uvTop);
	uvs[3]=Vector2f(uvLeft,uvTop);

	TCSceneRenderer::instance()->render(textureID,vertex,uvs,paint);
}

NS_TC_END