#include <string.h>
#include "TCMatrix3x3.h"
#include <math.h>
NS_TC_BEGIN
#define PI 3.14159265
TCMatrix3x3::TCMatrix3x3(){
	setIdentity();
}
TCMatrix3x3::TCMatrix3x3(float matrix[9]){
	memcpy(_matrix,matrix,9*sizeof(float));
}
TCMatrix3x3::~TCMatrix3x3(){

}
void TCMatrix3x3::setIdentity(){
	_matrix[0] = 1;
	_matrix[1] = 0;
	_matrix[2] = 0;
	_matrix[3] = 0;
	_matrix[4] = 1;
	_matrix[5] = 0; 
	_matrix[6] = 0;
	_matrix[7] = 0;
	_matrix[8] = 1;
}

void TCMatrix3x3::mul(const float pmat[9]){
	float dm00 = _matrix[0] * pmat[0] + _matrix[1] * pmat[3] + _matrix[2]
	* pmat[6];
	float dm01 = _matrix[0] * pmat[1] + _matrix[1] * pmat[4] + _matrix[2]
	* pmat[7];
	float dm02 = _matrix[0] * pmat[2] + _matrix[1] * pmat[5] + _matrix[2]
	* pmat[8];
	float dm10 = _matrix[3] * pmat[0] + _matrix[4] * pmat[3] + _matrix[5]
	* pmat[6];
	float dm11 = _matrix[3] * pmat[1] + _matrix[4] * pmat[4] + _matrix[5]
	* pmat[7];
	float dm12 = _matrix[3] * pmat[2] + _matrix[4] * pmat[5] + _matrix[5]
	* pmat[8];
	float dm20 = _matrix[6] * pmat[0] + _matrix[7] * pmat[3] + _matrix[8]
	* pmat[6];
	float dm21 = _matrix[6] * pmat[1] + _matrix[7] * pmat[4] + _matrix[8]
	* pmat[7];
	float dm22 = _matrix[6] * pmat[2] + _matrix[7] * pmat[5] + _matrix[8]
	* pmat[8];
	_matrix[0] = dm00;
	_matrix[1] = dm01;
	_matrix[2] = dm02;
	_matrix[3] = dm10;
	_matrix[4] = dm11;
	_matrix[5] = dm12;
	_matrix[6] = dm20;
	_matrix[7] = dm21;
	_matrix[8] = dm22;
}

void TCMatrix3x3::mul(const TCMatrix3x3& mat){
	mul(mat._matrix);
}

void TCMatrix3x3::apply(float result[3], const float vect[3]) const{
	result[0] = _matrix[0] * vect[0] + _matrix[1] * vect[1] + _matrix[2]*vect[2];
	result[1] = _matrix[3] * vect[0] + _matrix[4] * vect[1] + _matrix[5]*vect[2];
	result[2]=_matrix[6]*vect[0]+_matrix[7]*vect[1]+_matrix[8]*vect[2];
}



Vector2f TCMatrix3x3::mulWithPoint(const Vector2f& point)const{
	Vector2f ret;
	ret.x = _matrix[0] * point.x+ _matrix[1] * point.y+_matrix[2];
	ret.y = _matrix[3] * point.x + _matrix[4] *point.y + _matrix[5];
	return ret;
}
Vector2f TCMatrix3x3::mulWithVector(const Vector2f& vector)const{
	Vector2f ret;
	ret.x = _matrix[0] * vector.x+ _matrix[1] * vector.y;
	ret.y = _matrix[3] * vector.x + _matrix[4] *vector.y;
	return ret;
}

//static method
TCMatrix3x3 TCMatrix3x3::matrixWithTranslate(float x,float y){
	float mat[9]={1, 0, x, 0, 1, y, 0, 0, 1};
	TCMatrix3x3 ret=TCMatrix3x3(mat);
	return ret;
}

TCMatrix3x3 TCMatrix3x3::matrixWithRotation(float degree){

	float a = (float) (degree * PI / 180);
	float dm00 = cos(a);
	float dm01 = -sin(a);
	float dm10 = -dm01;
	float dm11 = dm00;
	float mat[9]={dm00, dm01, 0, dm10, dm11, 0, 0, 0, 1};
	TCMatrix3x3 ret=TCMatrix3x3(mat);
	return ret;
}

TCMatrix3x3 TCMatrix3x3::matrixWithScale(float scaleX,float scaleY){
	float mat[9]={scaleX, 0, 0, 0, scaleY, 0, 0, 0, 1};
	TCMatrix3x3 ret=TCMatrix3x3(mat);
	return ret;
}
NS_TC_END