#ifndef __ROLE_H__
#define __ROLE_H__

#include "AutoReleaseObject.h"
#include <string>
#include "TCSprite.h"
USING_NS_TC;
enum RoleType{
	Role_Xigua
};
class Role:public AutoReleaseObject{

private:
	Sprite* _sprite;
	RoleType _type;

protected:
	Role(RoleType type);
	~Role();
	void init(const std::string& imageName);
public:
	Sprite* sprite();

	void attack();

	static Role* alloc(RoleType roleType);
};

#endif