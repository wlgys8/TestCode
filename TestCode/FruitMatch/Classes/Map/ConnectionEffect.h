#ifndef __CONNECTION_EFFECT_H__
#define __CONNECTION_EFFECT_H__
#include "BaseNode.h"
#include <vector>
#include "ParticleSystem/TCParticleSystem.h"
#include <list>
USING_NS_TC;

class PSNode:public BaseNode{

protected:
	PSNode();

	void onAnimationEnd(float time);

	~PSNode();
public:
	void StartMove( std::list<Vector2f>& path);
	ParticleSystem* ps();

	static PSNode* alloc();
};

class ConnectionEffect{
	typedef vector<PSNode*> PSList;
private:
	BaseNode* _spaceNode;
	PSList _freeList;
	PSList _busyList;

protected:
	ConnectionEffect():_spaceNode(0){

	}
	~ConnectionEffect();
public:
	inline void setSpaceNode(BaseNode* node){
		_spaceNode=node;
		_spaceNode->retain();
	}
	void returnPSNode(PSNode* node);

	void generateConnection( std::list<Vector2f>& path);

	static ConnectionEffect* instance();

};
#endif