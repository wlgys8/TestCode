#ifndef __TC_VECTOR2_H__
#define __TC_VECTOR2_H__
#include "TCCommon.h"
NS_TC_BEGIN

class Vector2{
public:
	int x;
	int y;
	Vector2():x(0),y(0){

	}
	Vector2(int x,int y){
		this->x=x;
		this->y=y;
	}
	const Vector2 operator+(const Vector2& v2) const{
		return Vector2(x+v2.x,y+v2.y);
	}
	const Vector2 operator-(const Vector2& v2) const{
		return Vector2(x-v2.x,y-v2.y);
	}
	const Vector2 operator*(const Vector2& v2) const {
		return Vector2(x*v2.x,y*v2.y);
	}
	const Vector2 operator*(const float& cons) const{
		return Vector2(x*cons,y*cons);
	}
	void operator+=(const Vector2& v){
		x+=v.x;
		y+=v.y;
	}
	void operator-=(const Vector2& v){
		x-=v.x;
		y-=v.y;
	}

	void operator*=(const Vector2& v){
		x*=v.x;
		y*=v.y;
	}
	void operator*=(const int& cons){
		x*=cons;
		y*=cons;
	}
	friend bool operator==(const Vector2& v1,const Vector2& v2){
		return v1.x==v2.x&&v1.y==v2.y;
	}

	friend bool operator!=(const Vector2& v1,const Vector2& v2){
		return !(v1==v2);
	}

public:
	static Vector2 zero(){
		return Vector2(0,0);
	}
	static Vector2 one(){
		return Vector2(1,1);
	}
};


class Vector2f{
public:
	float x;
	float y;
	Vector2f():x(0),y(0){

	}
	Vector2f(float x,float y){
		this->x=x;
		this->y=y;
	}
	const Vector2f operator+(const Vector2f& v2) const{
		return Vector2f(x+v2.x,y+v2.y);
	}
	const Vector2f operator-(const Vector2f& v2) const{
		return Vector2f(x-v2.x,y-v2.y);
	}
	const Vector2f operator*(const Vector2f& v2) const {
		return Vector2f(x*v2.x,y*v2.y);
	}
	const Vector2f operator*(const float& cons) const{
		return Vector2f(x*cons,y*cons);
	}
	void operator+=(const Vector2f& v){
		x+=v.x;
		y+=v.y;
	}
	void operator-=(const Vector2f& v){
		x-=v.x;
		y-=v.y;
	}

	void operator*=(const Vector2f& v){
		x*=v.x;
		y*=v.y;
	}
	void operator*=(const float& cons){
		x*=cons;
		y*=cons;
	}
	friend bool operator==(const Vector2f& v1,const Vector2f& v2){
		return v1.x==v2.x&&v1.y==v2.y;
	}

	friend bool operator!=(const Vector2f& v1,const Vector2f& v2){
		return !(v1==v2);
	}

public:
	static Vector2f zero(){
		return Vector2f(0,0);
	}
	static Vector2f one(){
		return Vector2f(1,1);
	}
};

NS_TC_END
#endif