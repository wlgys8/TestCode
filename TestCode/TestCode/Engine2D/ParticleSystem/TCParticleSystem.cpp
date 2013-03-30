#include "ParticleSystem/TCParticleSystem.h"
#include "TCRandom.h"
#include "TCTime.h"
#include "TCPaint.h"
NS_TC_BEGIN

ParticleSystem::ParticleSystem():
_time(0),_spaceNode(0),
_minStartSize(1),_maxStartSize(1),
_isScaleEnable(false),_isEmiting(false)
{
	_paint=Paint();
	_paint.setBlendMode(BLEND_ONE,BLEND_ONE);
	_paint.setColor(Color(1,0.5f,0.1f,1));

	_sizeOverLifeTime.addKey(0,1);
	_rotationOverLifeTime.addKey(0,0);
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
void ParticleSystem::setImageName(const std::string& name){
	_imageName=name;
}
void ParticleSystem::initParticle(Particle& pt){
	pt.age=0;
	pt.velocity=_minStartVelocity+(_maxStartVelocity-_minStartVelocity)*(Random::value());
	pt.size=Random::between(_minStartSize,_maxStartSize);
}
void ParticleSystem::GenerateParticle(){
	if(_freeList.size()>0){
		Particle p=_freeList.front();
		_freeList.pop_front();
		initParticle(p);
		
		_busyList.push_back(p);
		if(_spaceNode){
			_spaceNode->addChild(p.sprite);
		}else{
			node()->addChild(p.sprite);
		}
		p.sprite->setWorldPosition(node()->worldPosition());
	}else{
		Particle p=Particle();
		p.sprite=Sprite::alloc(_imageName)->retain<Sprite>();
		p.sprite->drawer()->setPaint(_paint);
		initParticle(p);
		
		_busyList.push_back(p);

		if(_spaceNode){
			_spaceNode->addChild(p.sprite);
		}else{
			node()->addChild(p.sprite);
		}
		p.sprite->setWorldPosition(node()->worldPosition());
	}
}

void ParticleSystem::invokeUpdate(){
	if(_isEmiting){
		if(_time>=_fireRate){
			GenerateParticle();
			_time-=_fireRate;
		}
		_time+=Time::deltaTime();
	}

	float deltaTime=Time::deltaTime();
	Array::iterator it=_busyList.begin();
	while(it!=_busyList.end()){
		Particle& pt=*it;
		pt.sprite->setLocalPosition(pt.sprite->localPosition()+(pt.velocity*deltaTime));
		
		if(_isScaleEnable){
			float scale=_sizeOverLifeTime.evaluate(pt.age/_lifeTime)*pt.size;
			pt.sprite->setLocalScale(Vector2f(scale,scale));
		}
		
		pt.age+=Time::deltaTime();
		if(pt.age>=_lifeTime){
			_freeList.push_back(pt);
			pt.sprite->removeSelf();
			it=_busyList.erase(it);
		}else{
			it++;
		}
	}
	
}

ParticleSystem* ParticleSystem::alloc(){
	ParticleSystem* ret=new ParticleSystem();
	ret->autoRelease();
	return ret;
}
NS_TC_END