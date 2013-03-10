#include "Enemy/Enemy.h"

Enemy::Enemy(EnemyType type){
	if(type==Enemy_Snake){
		Sprite::initWithImageName("enemy_snake.png");
	}
}
Enemy::~Enemy(){

}

Enemy* Enemy::alloc(EnemyType type){
	Enemy* ret=new Enemy(type);
	ret->autoRelease();
	return ret;
}