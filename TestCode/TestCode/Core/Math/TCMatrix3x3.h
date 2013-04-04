#ifndef __TC_MATRIX3X3_H__
#define __TC_MATRIX3X3_H__
#include "TCMacros.h"
#include "TCVector2f.h"
NS_TC_BEGIN
class TCMatrix3x3{
private:
	float _matrix[9];
public:
	TCMatrix3x3();
	TCMatrix3x3(float matrix[9]);
		~TCMatrix3x3();
	void setIdentity();

	void mul(const float matrix[9]);

	void mul(const TCMatrix3x3& mat);

	void apply(float result[3], const float vect[3]) const;

	Vector2f mulWithPoint(const Vector2f& point) const;

	Vector2f mulWithVector(const Vector2f& vector)const;

	inline const float* array() const{
		return _matrix;
	}
	static TCMatrix3x3 matrixWithTranslate(float x,float y);

	static TCMatrix3x3 matrixWithRotation(float rot);

	static TCMatrix3x3 matrixWithScale(float scaleX,float scaleY);
};
NS_TC_END
#endif