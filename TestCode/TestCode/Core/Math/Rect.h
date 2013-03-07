#ifndef __TC_RECT_H__
#define __TC_RECT_H__
#include "TCMacros.h"
#include "TCVector2f.h"
NS_TC_BEGIN
class Rect{
private:
	float _x;
	float _y;
	float _width;
	float _height;
public:
	Rect(float x=0,float y=0,float width=0,float height=0){
		_x=x;
		_y=y;
		_width=width;
		_height=height;
	}

	float inline width() const{
		return _width;
	}
	float inline height() const{
		return _height;
	}
	float  inline xMin() const{
		return _x;
	}
	float inline xMax() const{
		return _x+_width;
	}
	float inline yMin() const{
		return _y;
	}
	float inline yMax() const{
		return _y+_height;
	}
	bool inline contains(float x,float y) const{
		return x>xMin()&&x<xMax()&&y>yMin()&&y<yMax();
	}

	bool inline contains(const Vector2f& v) const {
		return contains(v.x,v.y);
	}
};
NS_TC_END
#endif