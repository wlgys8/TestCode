#ifndef __TC_RECTANGLERGBA_H__
#define __TC_RECTANGLERGBA_H__
#include "BaseNode.h"

NS_TC_BEGIN
class TCDrawer;
class RectangleRGBA:public BaseNode{
protected:
	RectangleRGBA();
	~RectangleRGBA();
	void init();
public:
	TCDrawer* drawer();

	void setSize(const Vector2f& size);

	static RectangleRGBA* alloc();
};

NS_TC_END

#endif