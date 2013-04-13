#include "Enemy/Enemy.h"
#include "TCTime.h"

Enemy::Enemy(){
	Sprite::initWithImageName("enemy_snake.png");
}

static float speed=400.0f/60;

void Enemy::reset(){
	setLocalPosition(Vector2f(200,370));
}
void Enemy::invokeUpdate(){
	setLocalPosition(localPosition()+Vector2f(-speed*Time::deltaTime(),0));
	Sprite::invokeUpdate();
}

Enemy::~Enemy(){
}

Enemy* Enemy::alloc(){
	Enemy* ret=new Enemy();
	ret->autoRelease();
	return ret;
}