#include "Animation/TCAnimationCurve.h"
#include "TCVector2f.h"
NS_TC_BEGIN

void AnimationCurve::addKey(float key,float value){
	CurveKey keyy=CurveKey(key,value,0,0);
	addKey(keyy);
}

void AnimationCurve::addKey(const CurveKey& key){
	_interpolations.push_back(key);
}

int AnimationCurve::keyNumbners(){
	return _interpolations.size();
}

float AnimationCurve::evaluate(float time){
	for(int i=1;i<_interpolations.size();i++){
		const CurveKey& key= _interpolations[i];
		const CurveKey& preKey=_interpolations[i-1];
		if(i==_interpolations.size()-1&&time>=key.time()){
			return key.value();
		}
		if(time>=preKey.time()&&time<key.time()){
			return HermiteInterpolation3::evaluate(
				preKey.time(),
				preKey.value(),
				preKey.outTangent(),
				key.time(),
				key.value(),
				key.inTangent(),
				time
				);
		}
	}
}

NS_TC_END