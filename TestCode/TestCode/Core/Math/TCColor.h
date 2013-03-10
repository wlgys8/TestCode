#ifndef __TC_COLOR_H__
#define __TC_COLOR_H__
#include "TCMacros.h"
NS_TC_BEGIN
class Color{
private:
	float _r;
	float _g;
	float _b;
	float _a;
public:

	Color():_r(1),_g(1),_b(1),_a(1){

	}
	Color(float r,float g,float b,float a)
	{
		this->_r=r;
		this->_g=g;
		this->_b=b;
		this->_a=a;
	}

	const float& r() const{
		return _r;
	}
	const float& g() const{
		return _g;
	}
	const float& b() const{
		return _b;
	}
	const float& a() const{
		return _a;
	}
	void set(float r,float g,float b,float a){
		_r=r;
		_g=g;
		_b=b;
		_a=a;
	}
	friend bool operator==(const Color& c1,const Color &c2){
		return c1._r==c2._r&&c1._g==c2._g&&c1._b==c2._b&&c1._a==c2._a;
	}
	friend bool operator!=(const Color& c1,const Color &c2){
		return !(c1==c2);
	}
};
NS_TC_END
#endif