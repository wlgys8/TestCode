#ifndef __TC_RENDERELEMENT_H__
#define __TC_RENDERELEMENT_H__

#include "Math/TCMatrix3x3.h"
#include "AutoReleaseObject.h"
#include "TCPaint.h"

NS_TC_BEGIN

class RenderElement:public AutoReleaseObject{


public:

	virtual void onRender(const TCMatrix3x3& localToWorldMatrix,const Paint& paint)=0;

	virtual Vector2f rawSize()=0;
};

NS_TC_END

#endif