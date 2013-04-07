#ifndef __TC_BATCHUTIL_H__
#define __TC_BATCHUTIL_H__
#include "TCMatrix3x3.h"
#include "TCPaint.h"
#include "Rect.h"
NS_TC_BEGIN

class RenderUtil{

public:

	static void renderImage(const int& textureID,const Rect& frame,const Rect& uv,const TCMatrix3x3& localToWorldMatrix,const Paint& paint);
};

NS_TC_END

#endif