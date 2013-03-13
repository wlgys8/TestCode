#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "TCSprite.h"

USING_NS_TC;

enum EnemyType{
	Enemy_Snake,

};
class Enemy:public Sprite{

private:
	float _hp;
	Sprite* _greenBar;
	void initBloodBar();
protected:

	Enemy(EnemyType type);
	~Enemy();

public:
	void hurt();
	static Enemy* alloc(EnemyType type);

};

#endif