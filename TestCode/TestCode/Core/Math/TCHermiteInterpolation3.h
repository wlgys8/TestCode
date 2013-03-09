#ifndef __TC_HERMITE_INTERPOLATION3_H__
#define __TC_HERMITE_INTERPOLATION3_H__
#include "TCMacros.h"
NS_TC_BEGIN
class HermiteInterpolation3{

private:
	float _x0;
	float _y0;
	float _ty0;//tangent

	float _x1;
	float _y1;
	float _ty1;//tangent

public:
	HermiteInterpolation3(float x0,float y0,float ty0,float x1,float y1,float ty1):
	_x0(x0),
	_y0(y0),
	_ty0(ty0),
	_x1(x1),
	_y1(y1),
	_ty1(ty1)
	{
	};

	inline void set(float x0,float y0,float ty0,float x1,float y1,float ty1){
		_x0=x0;
		_y0=y0;
		_ty0=ty0;
		_x1=x1; 
		_y1=y1;
		_ty1=ty1;		
	}
	float evaluate(float x);

	static float evaluate(float x0,float y0,float ty0,float x1,float y1,float ty1,float t);
};

NS_TC_END
#endif

