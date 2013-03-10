#include "Role/Role.h"
#include "Fruit/BulletFactory.h"
Role::Role(RoleType type):_type(type){
	if(type==Role_Xigua){
		init("role_xigua.png");
	//	init("white_point.png");
	}
}
void Role::init(const std::string& imageName){
	_sprite=Sprite::alloc(imageName);
	_sprite->retain();
}
Sprite* Role::sprite(){
	return _sprite;
}
void Role::attack(){
	Bullet* bt= BulletFactory::instance()->createBullet(Bullet_Juzi);
	sprite()->addChild(bt);
	bt->setLocalPosition(Vector2f(10,0));
}
Role::~Role(){
	if(_sprite){
		_sprite->release();
	}
}

Role* Role::alloc(RoleType roleType){
	Role* ret=new Role(roleType);
	ret->retain();
	return ret;
}