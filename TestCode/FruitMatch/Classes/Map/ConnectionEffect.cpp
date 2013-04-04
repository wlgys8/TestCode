#include "ConnectionEffect.h"
#include "ParticleSystem/TCParticleSystem.h"
#include "TCAnimation.h"


static ParticleSystem* createPS(){
	ParticleSystem* pt=ParticleSystem::alloc();
	pt->setFireRate(20);
	pt->setStartLiftTime(1.0f);
	pt->setStartVelocity(Vector2f(-30,-30),Vector2f(30,30));
	pt->setEnableScale(true);
	pt->setStartSize(1,1);
	pt->setImageName("wp.png");
	AnimationCurve sizeCurve=AnimationCurve();
	sizeCurve.addKey(0,1);
	sizeCurve.addKey(1,0);
	pt->setOverLifeTimeSize(sizeCurve);
	return pt;
}

PSNode* PSNode::alloc(){
	PSNode* ret=new PSNode();
	ret->autoRelease();
	return ret;
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
void PSNode::StartMove( std::list<Vector2f>& path){
	AnimationCurve curvX;
	AnimationCurve curvY;
	curvX.setWrapMode(CurveWrapClamp);
	curvY.setWrapMode(CurveWrapClamp);
	std::list<Vector2f>::iterator it;
	float t=0;
	float step=1.0f/path.size();
	for(it=path.begin();it!=path.end();it++){
		curvX.addKey(t,(*it).x);
		curvY.addKey(t,(*it).y);
		t+=step;
	}
	TranslateAnimation* trans=TranslateAnimation::alloc(curvX,curvY,1.0f);
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


void ConnectionEffect::generateConnection( std::list<Vector2f>& path){
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
	node->StartMove(path);
}

ConnectionEffect* ConnectionEffect::instance(){
	static ConnectionEffect _instance;
	return &_instance;
}