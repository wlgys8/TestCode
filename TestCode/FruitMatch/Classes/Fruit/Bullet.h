#ifndef __Bullet_H__
#define __Bullet_H__
#include "TCSprite.h"
USING_NS_TC;

enum BulletType{
	Bullet_Juzi,

};
class Bullet:public Sprite{
protected:
	Bullet(BulletType type);
	~Bullet();
public:
	void reset(float x,float y,BulletType type=Bullet_Juzi);

	void invokeUpdate();

	static Bullet* alloc(BulletType type);

};
#endif