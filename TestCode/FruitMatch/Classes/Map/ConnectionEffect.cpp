#include "ConnectionEffect.h"
#include "ParticleSystem/TCParticleSystem.h"
#include "TCAnimation.h"


static ParticleSystem* createPS(){
	ParticleSystem* pt=ParticleSystem::alloc();
	pt->setImageName("wp.png");
	pt->setFireRate(10);
	pt->setStartLiftTime(2);
	pt->setStartVelocity(Vector2f(-30,-30),Vector2f(30,30));
	pt->setEnableScale(true);
	pt->setStartSize(1,1);

	AnimationCurve sizeCurve=AnimationCurve();
	sizeCurve.addKey(0,1);
	sizeCurve.addKey(1,0);
	pt->setOverLifeTimeSize(sizeCurve);
	return pt;
}


PSNode::PSNode(){
	ParticleSystem* ps=createPS();
	addComponent(ps);
}
PSNode::~PSNode(){

}
ParticleSystem* PSNode::ps(){
	return (ParticleSystem*)getComponment(ComponentParticleSystem);
}
void PSNode::onAnimationEnd(float time){
	ps()->stopEmit();
	ConnectionEffect::instance()->returnPSNode(this);
}
void PSNode::StartMove(const Vector2f& from,const Vector2f& to){
	AnimationCurve curvX;
	AnimationCurve curvY;
	curvX.addKey(0,from.x);
	curvX.addKey(1,to.x);
	curvY.addKey(0,from.y);
	curvY.addKey(1,to.y);
	TranslateAnimation* trans=TranslateAnimation::alloc(curvX,curvY,1);
	trans->registerAnimationEndEvent(this,animationEventSelector(PSNode::onAnimationEnd));
	ps()->emit();
	animation()->play(
		trans
		);

}

ConnectionEffect::~ConnectionEffect(){
	if(_spaceNode){
		_spaceNode->release();
		_spaceNode=0;
	}

	PSList::iterator it;
	for(it=_freeList.begin();it!=_freeList.end();it++){
		(*it)->release();
	}
	_freeList.clear();

	for(it=_busyList.begin();it!=_busyList.end();it++){
		(*it)->release();
	}
	_freeList.clear();
}

void ConnectionEffect::returnPSNode(PSNode* node){
	PSList::iterator it;
	for(it=_busyList.begin();it!=_busyList.end();it++){
		if(*it==node){
			_freeList.push_back(node);
			_busyList.erase(it);
			return;
		}
	}
	assert(0);
}


void ConnectionEffect::generateConnection(const Vector2f& from,const Vector2f& to){
	PSNode* node=0;
	if(_freeList.size()==0){
		node=PSNode::alloc();
		node->retain();
		node->ps()->setParticleSpace(_spaceNode);
		_spaceNode->addChild(node);
	}else{
		node=_freeList.back();
		_freeList.pop_back();
	}
	_busyList.push_back(node);
	node->StartMove(from,to);
}