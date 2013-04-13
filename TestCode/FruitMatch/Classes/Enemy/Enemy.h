#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "TCSprite.h"

USING_NS_TC;

class Enemy:public Sprite{

private:
protected:
	Enemy();
	~Enemy();
public:
	void virtual invokeUpdate();
	void reset();
	static Enemy* alloc();

};

#endif