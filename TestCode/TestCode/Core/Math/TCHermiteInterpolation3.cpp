#include "TCHermiteInterpolation3.h"

NS_TC_BEGIN

float HermiteInterpolation3::evaluate(float x){
	return HermiteInterpolation3::evaluate(_x0,_y0,_ty0,_x1,_y1,_ty1,x);
}

float HermiteInterpolation3::evaluate(float x0,float y0,float ty0,float x1,float y1,float ty1,float x){
	float dx=x1-x0;
	float d_x_x0=x-x0;
	float d_x_x1=x-x1;
	float a=(1+2*d_x_x0/dx)*(d_x_x1/dx)*(d_x_x1/dx);
	float b=(1-2*d_x_x1/dx)*(d_x_x0/dx)*(d_x_x0/dx);
	float c=d_x_x0*(d_x_x1/dx)*(d_x_x1/dx);
	float d=-dx*(d_x_x0/dx)*(d_x_x0/dx);
	return a*y0+b*y1+c*ty0+d*ty1;
}
NS_TC_END