#include "TCAnimation.h"
#include "TCTime.h"
NS_TC_BEGIN

bool TranslateAnimation::invokeUpdate(BaseNode* target,float ctime){
	bool ret=false;
	if(_time!=0&&ctime>=_time){
		ctime=_time;
		ret=true;
	}
	float x=_xCurve.evaluate(ctime);
	float y=_yCurve.evaluate(ctime);
	target->setLocalPosition(Vector2f(x,y));
	return ret;
}
void TranslateAnimation::reset(){
}
TranslateAnimation* TranslateAnimation::alloc(const AnimationCurve& x,const AnimationCurve& y,float time){
	TranslateAnimation* ret=new TranslateAnimation(x,y,time);
	ret->autoRelease();
	return ret;
}

AnimationContainer::AnimationContainer():_animation(0),
_isPlaying(false),_currentTime(0)
{

}
void AnimationContainer::invokeUpdate(BaseNode* target){
	if(_animation&&_isPlaying){
		if(_animation->invokeUpdate(target,_currentTime)){
			stop();
		}
		_currentTime+=Time::deltaTime();
	}
}

void AnimationContainer::play(Animation* animation){
	if(_animation){
		_animation->release();
	}
	_animation=animation;
	_animation->retain();
	_animation->reset();
	_currentTime=0;
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
	_currentTime=0;
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