#ifndef __TC_ANIMATIONCURVE_H__
#define __TC_ANIMATIONCURVE_H__
#include "TCMacros.h"
#include "TCHermiteInterpolation3.h"
#include <vector>
#include "TCVector2f.h"
NS_TC_BEGIN
class CurveKey{
private:
	float _time;
	float _value;
	float _inTangent;
	float _outTangent;

public:
	CurveKey(){
		_time=0;
		_value=0;
		_inTangent=0;
		_outTangent=0;
	}
	CurveKey(float time,float value,float inTangent,float outTangent):
	_time(time),
	_value(value),
	_inTangent(inTangent),
	_outTangent(outTangent)
	{
	}
	inline void set(const float& time,const float& value,const float& inTangent,const float& outTangent){
		_time=time;
		_value=value;
		_inTangent=inTangent;
		_outTangent=outTangent;
	}

	inline void set(const float& time,const float& value){
		_time=time;
		_value=value;
	}

	inline const float& time() const{
		return _time;
	}

	inline const float& value() const{
		return _value;
	}

	inline const float & inTangent() const{
		return _inTangent;
	}

	inline const float& outTangent() const{
		return _outTangent;
	}
};
enum CurveWrapMode{
	CurveWrapLoop=0,
	CurveWrapPingPong=1,
	CurveWrapClamp,
};
//if key number is 0,curve always return 1;
class AnimationCurve{
	typedef std::vector<CurveKey> KeyList;
private:
	KeyList  _interpolations;
	CurveWrapMode _wrapMode;
public:
	AnimationCurve():_wrapMode(CurveWrapLoop){
	}

	inline const enum CurveWrapMode& wrapMode() const{
		return _wrapMode;
	}
	inline void setWrapMode(const CurveWrapMode& mode){
		_wrapMode=mode;
	}
	void normalized();//normalize time to (0,1)

	void addKey(float key,float value);
	//Smooth tangents are automatically computed for the key

	void addKey(const CurveKey& key);

	AnimationCurve operator* (const Vector2f& scale) const;

	float evaluate(float time);

	int keyNumbners();

};

NS_TC_END
#endif