#include "Bullet.h"
#include "TCTime.h"
#include "TCScreen.h"
Bullet::Bullet(BulletType type){
	if(type==Bullet_Juzi){
		Sprite::initWithImageName("bullet_jz.png");
	}else{
		Sprite::init();
	}
}
void Bullet::reset(float x,float y,BulletType type){
	setLocalPosition(Vector2f(x,y));
	setImage("bullet_jz.png");
}
void Bullet::invokeUpdate(){
	Sprite::invokeUpdate();
	setLocalPosition(localPosition()+Vector2f(100*Time::deltaTime(),0));
	if(worldPosition().x>Screen::width()/2){
		removeSelf();
	}
}
Bullet::~Bullet(){

}
Bullet* Bullet::alloc(BulletType type){
	Bullet* bt=new Bullet(type);
	bt->autoRelease();
	return bt;
}