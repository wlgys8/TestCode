#ifndef __TC_PARTICLE_H__
#define __TC_PARTICLE_H__
#include "BaseNode.h" 
#include "TCVector2f.h"
#include "TCSprite.h"
#include <list>
#include <vector>
#include "TCAnimationCurve.h"
NS_TC_BEGIN
class Particle{

public:
	Particle():age(0),sprite(0),velocity(Vector2f(0,0)),size(1){

	}
	float age;
	Sprite* sprite;
	Vector2f velocity;
	float size;
};
class Paint;
class ParticleSystem:public BaseComponent{

	typedef std::list<Particle> List;
	typedef std::vector<Particle> Array;

private:
	BaseNode* _spaceNode;

	Vector2f _minStartVelocity;
	Vector2f _maxStartVelocity;

	//scale
	float _minStartSize;
	float _maxStartSize;
	bool _isScaleEnable;
	AnimationCurve _sizeOverLifeTime;

	//rotation
	float _minStartRotation;
	float _maxStartRotation;
	bool _isRotationEnable;
	AnimationCurve _rotationOverLifeTime;

	std::string  _imageName;
	List _freeList;
	Array _busyList;
	float _lifeTime;
	float _fireRate;

	float _time;

	Paint _paint;

	bool _isEmiting;

	void GenerateParticle();

	void initParticle(Particle& pt);
protected:
	ParticleSystem();
	~ParticleSystem();
public:

	inline ComponentType type(){
		return ComponentParticleSystem;
	}

	inline void setImageName(const std::string& name){
		_imageName=name;
	}

	inline void setParticleSpace(BaseNode* spaceNode){
		_spaceNode=spaceNode;//weak ref
	}

	inline void setFireRate(int particleCountPerSecond){
		_fireRate=1.0f/particleCountPerSecond;
	}

	inline void setStartVelocity(const Vector2f& minSpeed,const Vector2f& maxSpeed){
		_minStartVelocity=minSpeed;
		_maxStartVelocity=maxSpeed;
	}

	inline void setStartSize(const float& minSize,const float& maxSize){
		_minStartSize=minSize;
		_maxStartSize=maxSize;
	}

	inline void setStartRotation(const float& minRotation,const float& maxRotation){
		_minStartRotation=minRotation;
		_maxStartRotation=maxRotation;
	}

	inline void setStartLiftTime(const float& liftTime){
		_lifeTime=liftTime;
	}

	inline void setOverLifeTimeSize(const AnimationCurve& curve){
		_sizeOverLifeTime=curve;
		_sizeOverLifeTime.normalized();
	}
	inline void setOverLifeTimeRotation(const AnimationCurve curve){
		_rotationOverLifeTime=curve;
		_rotationOverLifeTime.normalized();
	}
	inline void setEnableScale(const bool& isEnable){
		_isScaleEnable=isEnable;
	}
	inline const bool& isEnableScale() const {
		return _isScaleEnable;
	}

	inline void setEnableRotation(const bool& isEnable){
		_isRotationEnable=isEnable;
	}
	inline const bool& isEnableRotation() const{
		return _isRotationEnable;
	}
	inline void emit(){
		_isEmiting=true;
	}
	inline void stopEmit(){
		_isEmiting=false;
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