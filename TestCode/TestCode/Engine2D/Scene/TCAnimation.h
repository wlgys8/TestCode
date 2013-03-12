#ifndef __TC_ANIMATION_H__
#define __TC_ANIMATION_H__
#include "BaseComponent.h"
#include "TCAnimationCurve.h"
#include "BaseNode.h"
NS_TC_BEGIN

typedef bool (AutoReleaseObject::*delegateAnimationEvent)(float time);
#define animationEventSelector(_SELECTOR) (delegateAnimationEvent)(&_SELECTOR)

class AnimationContainer;

class Animation:public AutoReleaseObject{
	friend class AnimationContainer;
protected:
	virtual bool invokeUpdate(BaseNode* target,float time)=0;
	virtual void reset()=0;
};

class TranslateAnimation:public Animation{
private:
	AnimationCurve _xCurve;
	AnimationCurve _yCurve;
	float _time;

	AutoReleaseObject* _target;
	delegateAnimationEvent _evt;

public:
	TranslateAnimation(const AnimationCurve& x,const AnimationCurve& y,float time){
		_xCurve=x;
		_yCurve=y;
		_time=time;
		_evt=0;
		_target=0;
	}

	inline void registerAnimationEndEvent(AutoReleaseObject* target,delegateAnimationEvent evt){
		_target=target;//weak ref
		_evt=evt;
	}

	bool invokeUpdate(BaseNode* target,float time);
	
	void reset();

	static TranslateAnimation* alloc(const AnimationCurve& x,const AnimationCurve& y,float time);

};
class AnimationContainer:public BaseComponent{
	friend class BaseNode;
private:
	Animation* _animation;

	void invokeUpdate(BaseNode* target);

	bool _isPlaying;
	float _currentTime;
	AnimationContainer();
	~AnimationContainer();
public:
	inline enum ComponentType type(){
		return ComponentAnimation;
	}
	void play(Animation* anim);

	void play();

	void stop();

	void pause();

	static AnimationContainer* alloc();

};

NS_TC_END
#endif