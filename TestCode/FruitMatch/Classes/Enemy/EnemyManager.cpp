#include "EnemyManager.h"
#include "Enemy/Enemy.h"
#include "Fruit/Bullet.h"
#include "Fruit/BulletFactory.h"

Enemy* EnemyManager::createEnemy(EnemyType type){
	Enemy* emy=Enemy::alloc(type);
	_enemyList.push_back(emy);
	emy->retain();
	return emy;
}

bool EnemyManager::checkWithBullet(Bullet* bullet){
	EnemyList::iterator it;
	for(it=_enemyList.begin();it!=_enemyList.end();it++){
		Vector2f enemyPos=(*it)->worldPosition();
		Vector2f bulletPos=bullet->worldPosition();
		if(bulletPos.x>enemyPos.x){
			(*it)->hurt();
		//	DebugLog("ref:%d",bullet->referCount());
			return true;
		}
	}
	return false;
	

}