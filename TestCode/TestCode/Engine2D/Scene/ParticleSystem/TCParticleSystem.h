#ifndef __TC_PARTICLE_H__
#define __TC_PARTICLE_H__
#include "BaseNode.h" 
class ParticleSystem:public BaseNode{


private:

	void GenerateParticle();


public:

	void setIsInLocalSpace(bool isLocalSpace);

	void setFireRate(int particleCountPerSecond);

	void setStartV(float vx,float vy);


};

#endif