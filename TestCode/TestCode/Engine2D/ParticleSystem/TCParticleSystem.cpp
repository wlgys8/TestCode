#include "ParticleSystem/TCParticleSystem.h"
#include "TCRandom.h"
#include "TCTime.h"
#include "TCPaint.h"
NS_TC_BEGIN

ParticleSystem::ParticleSystem():
_time(0),_spaceNode(0)
{
	_paint=Paint();
	_paint.setBlendMode(BLEND_ONE,BLEND_ONE);
	_paint.setColor(Color(1,0.5f,0.1f,1));
}
ParticleSystem::~ParticleSystem(){
	List::iterator it;
	for(it=_freeList.begin();it!=_freeList.end();it++){
		(*it).sprite->release();
	}
	_freeList.clear();

	Array::iterator ait;
	for(ait=_busyList.begin();ait!=_busyList.end();ait++){
		(*ait).sprite->release();
	}
	_busyList.clear();
}

void ParticleSystem::initParticle(Particle& pt){
	pt.age=0;
	pt.velocity=_minStartVelocity+(_maxStartVelocity-_minStartVelocity)*(Random::value());
}
void ParticleSystem::GenerateParticle(){
	if(_freeList.size()>0){
		Particle p=_freeList.front();
		_freeList.pop_front();
		initParticle(p);
		p.sprite->setWorldPosition(node()->worldPosition());
		_busyList.push_back(p);
		if(_spaceNode){
			_spaceNode->addChild(p.sprite);
		}else{
			node()->addChild(p.sprite);
		}
		
	}else{
		Particle p=Particle();
		p.sprite=Sprite::alloc(_imageName)->retain<Sprite>();
		p.sprite->drawer()->setPaint(_paint);
		initParticle(p);
		p.sprite->setWorldPosition(node()->worldPosition());
		_busyList.push_back(p);
		
		if(_spaceNode){
			_spaceNode->addChild(p.sprite);
		}else{
			node()->addChild(p.sprite);
		}
		
	}
}


void ParticleSystem::setStartRotation(const float& minRotation,const float& maxRotation){

}

void ParticleSystem::setStartSize(const float& minSize,const float& maxSize){

}


void ParticleSystem::invokeUpdate(){
	if(_time>=_fireRate){
		GenerateParticle();
		_time-=_fireRate;
	}

	Array::iterator it=_busyList.begin();
	while(it!=_busyList.end()){
		Particle& pt=*it;
		pt.sprite->setLocalPosition(pt.sprite->localPosition()+(pt.velocity*Time::deltaTime()));
		
		pt.age+=Time::deltaTime();
		if(pt.age>=_lifeTime){
			_freeList.push_back(pt);
			pt.sprite->removeSelf();
			it=_busyList.erase(it);
		}else{
			it++;
		}
	}
	_time+=Time::deltaTime();
}
NS_TC_END