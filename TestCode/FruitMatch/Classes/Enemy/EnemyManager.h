#ifndef __ENEMYMANAGER_H__
#define __ENEMYMANAGER_H__
#include "TCSingleton.h"
#include <list>
#include "Enemy/Enemy.h"

USING_NS_TC;
class Bullet;
class EnemyManager:public TCSingleton<EnemyManager>{
	typedef std::list<Enemy*> EnemyList;
private:
	EnemyList _enemyList;
public:

	Enemy* createEnemy(EnemyType type);

	bool checkWithBullet(Bullet* bullet);
};
#endif