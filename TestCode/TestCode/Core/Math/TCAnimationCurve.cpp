#include "TCAnimationCurve.h"
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
void AnimationCurve::normalized(){
	const int& size=keyNumbners();
	if(size==0){
		return;
	}
	if(size==1){
		CurveKey& key= _interpolations[0];
		key.set(0,key.value());
	}
	float firstTime=_interpolations[0].time();
	float endTime=_interpolations[size-1].time();
	float len=endTime-firstTime;
	float offset=_interpolations[0].time();
	KeyList::iterator it;
	for(it=_interpolations.begin();it!=_interpolations.end();it++){
		CurveKey& key= *it;
		key.set((key.time()-offset)/len,key.value());
	}
	
}
float AnimationCurve::evaluate(float time){
	int size=keyNumbners();
	if(size==0){
		return 1;
	}
	if(size==1){
		return _interpolations[0].value();
	}
	float firstTime=_interpolations[0].time();
	float endTime=_interpolations[size-1].time();
	float deltaTime=endTime-firstTime;
	if(time>endTime||time<firstTime){
		if(_wrapMode==CurveWrapLoop){
			if(time<firstTime){
				int s=(int)((endTime-time)/(deltaTime));
				time+=s*deltaTime;
			}else if(time>endTime){
				int s=(int)((time-firstTime)/deltaTime);
				time-=s*deltaTime;
			}
		}else if(_wrapMode==CurveWrapPingPong){
			if(time<firstTime){
				int s=(int)((endTime-time)/(deltaTime));
				time+=s*deltaTime;
				if(s%2==1){
					time=deltaTime-time;
				}
			}else if(time>endTime){
				int s=(int)((time-firstTime)/deltaTime);
				time-=s*deltaTime;
				if(s%2==1){
					time=deltaTime-time;
				}
			}
		}else if(_wrapMode==CurveWrapClamp){
			if(time>endTime){
				return _interpolations[size-1].value();
			}else if(time<firstTime){
				return _interpolations[0].value();
			}
		}
	}
	for(unsigned int i=1;i<_interpolations.size();i++){
		const CurveKey& key= _interpolations[i];
		const CurveKey& preKey=_interpolations[i-1];
		if(i==_interpolations.size()-1&&time==key.time()){
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

	return 0;
}

NS_TC_END