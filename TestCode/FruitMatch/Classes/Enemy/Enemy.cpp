#include "Enemy/Enemy.h"

Enemy::Enemy(EnemyType type):_hp(25){
	if(type==Enemy_Snake){
		Sprite::initWithImageName("enemy_snake.png");
	}
	initBloodBar();
}

void Enemy::initBloodBar(){
	Sprite* red=Sprite::alloc("bloodbar_red.png");
	Sprite* green=Sprite::alloc("bloodbar_green.png");
	addChild(red);
	addChild(green);
	red->setLocalPosition(Vector2f(-10,50));
	green->setLocalPosition(Vector2f(-10,50));
	_greenBar=green->retain<Sprite>();
	_greenBar->drawer()->setPart(Rect(0,0,1,1));
}
void Enemy::hurt(){
	_hp--;
	_greenBar->drawer()->setPart(Rect(0,0,_hp/25,1));
}
Enemy::~Enemy(){

}

Enemy* Enemy::alloc(EnemyType type){
	Enemy* ret=new Enemy(type);
	ret->autoRelease();
	return ret;
}