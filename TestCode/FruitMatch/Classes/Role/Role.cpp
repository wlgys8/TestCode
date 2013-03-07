#include "Role/Role.h"

Role::Role(RoleType type):_type(type){
	if(type==Role_Xigua){
		init("role_xigua.png");
	}
}
void Role::init(const std::string& imageName){
	_sprite=Sprite::alloc(imageName);
	_sprite->retain();
}
Sprite* Role::sprite(){
	return _sprite;
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