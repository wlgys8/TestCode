#ifndef __TC_PARTICLE_H__
#define __TC_PARTICLE_H__
#include "BaseNode.h" 
#include "TCVector2f.h"
#include "TCSprite.h"
#include <list>
#include <vector>
NS_TC_BEGIN
class Particle{

public:
	Particle():age(0),sprite(0),velocity(Vector2f(0,0)){

	}
	float age;
	Sprite* sprite;
	Vector2f velocity;
};
class Paint;
class ParticleSystem:public BaseComponent{

	typedef std::list<Particle> List;
	typedef std::vector<Particle> Array;

private:

	Vector2f _minStartVelocity;
	Vector2f _maxStartVelocity;
	Vector2f _startSize;
	Vector2f _startRotation;
	std::string  _imageName;
	List _freeList;
	Array _busyList;
	float _lifeTime;
	float _fireRate;

	float _time;

	Paint _paint;

	void GenerateParticle();

	void initParticle(Particle& pt);
protected:
	ParticleSystem();
	~ParticleSystem();
public:

	inline ComponentType type(){
		return ComponentParticleSystem;
	}

	void setImageName(const std::string& name){
		_imageName=name;
	}

	void setIsInLocalSpace(bool isLocalSpace);

	void setFireRate(int particleCountPerSecond){
		_fireRate=1.0f/particleCountPerSecond;
	}

	inline void setStartVelocity(const Vector2f& minSpeed,const Vector2f& maxSpeed){
		_minStartVelocity=minSpeed;
		_maxStartVelocity=maxSpeed;
	}

	void setStartSize(const float& minSize,const float& maxSize);

	void setStartRotation(const float& minRotation,const float& maxRotation);

	void setStartLiftTime(const float& liftTime){
		_lifeTime=liftTime;
	}

	void invokeUpdate();

	static ParticleSystem* alloc(){
		ParticleSystem* ret=new ParticleSystem();
	ret->autoRelease();
	return ret;
	}
};
NS_TC_END
#endif