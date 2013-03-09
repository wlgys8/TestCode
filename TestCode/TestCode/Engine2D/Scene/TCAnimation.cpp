#include "TCAnimation.h"
#include "TCTime.h"
NS_TC_BEGIN

bool TranslateAnimation::invokeUpdate(BaseNode* target){
	bool ret=false;
	if(_currentTime>=_time){
		_currentTime=_time;
		ret=true;
	}
	float x=_xCurve.evaluate(_currentTime);
	float y=_yCurve.evaluate(_currentTime);
	target->setLocalPosition(Vector2f(x,y));
	_currentTime+=Time::deltaTime();
	return ret;
}
void TranslateAnimation::reset(){
	_currentTime=0;
}
TranslateAnimation* TranslateAnimation::alloc(const AnimationCurve& x,const AnimationCurve& y,float time){
	TranslateAnimation* ret=new TranslateAnimation(x,y,time);
	ret->autoRelease();
	return ret;
}

AnimationContainer::AnimationContainer():_animation(0),
_isPlaying(false)
{

}
void AnimationContainer::invokeUpdate(BaseNode* target){
	if(_animation&&_isPlaying){
		if(_animation->invokeUpdate(target)){
			stop();
		}
	}
}

void AnimationContainer::play(Animation* animation){
	if(_animation){
		_animation->release();
	}
	_animation=animation;
	_animation->retain();
	_animation->reset();
	_isPlaying=true;
}

void AnimationContainer::play(){
	_isPlaying=true;
}

void AnimationContainer::pause(){
	_isPlaying=false;
}

void AnimationContainer::stop(){
	_isPlaying=false;
	_animation->reset();
}

AnimationContainer::~AnimationContainer(){
	if(_animation){
		_animation->release();
		_animation=0;
	}
}

AnimationContainer* AnimationContainer::alloc(){
	AnimationContainer* ret=new AnimationContainer();
	ret->autoRelease();
	return ret;
}
NS_TC_END