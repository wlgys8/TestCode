#ifndef __BULLETFACTORY_H__
#define __BULLETFACTORY_H__
#include "TCSingleton.h"
#include <list>
#include "Bullet.h"
USING_NS_TC;
class BulletFactory:public TCSingleton<BulletFactory>{
	friend class TCSingleton<BulletFactory>;
public:
	typedef std::list<Bullet*> BulletList;
private:
	BulletList _freeList;
	BulletList _busyList;
	BulletFactory();
	~BulletFactory();
	void initWithCapacity(int capacity);
public:
	Bullet* createBullet(BulletType type);
	void recollectUnusedBullet();

	inline const BulletList& bulletList(){
		return _busyList;
	}
};
#endif