#include "BulletFactory.h"
#include "TCMacros.h"
BulletFactory::BulletFactory(){
	initWithCapacity(10);
}

void BulletFactory::initWithCapacity(int capacity){
	_freeList=BulletList();
	_busyList=BulletList();
	
}

Bullet* BulletFactory::createBullet(BulletType type){
	if(_freeList.size()>0){
		Bullet* ret=_freeList.front();
		_freeList.pop_front();
		_busyList.push_back(ret);
		return ret;
	}

	Bullet* bt=Bullet::alloc(type);
	bt->retain();
	_busyList.push_back(bt);
	bt->reset(0,0);
	DebugLog("new bullet");
	return bt;
}

void BulletFactory::recollectUnusedBullet(){
	BulletList::iterator it=_busyList.begin();
	while(it!=_busyList.end()){
		if((*it)->referCount()==1){
			_freeList.push_back(*it);
			it=_busyList.erase(it);
		}else{
			it++;
		}
	}
}

BulletFactory::~BulletFactory(){
	BulletList::iterator it;
	DebugLog("%d,%d",_busyList.size(),_freeList.size());
	for(it=_freeList.begin();it!=_freeList.end();it++){
		(*it)->release();
	}
	_freeList.clear();

	for(it=_busyList.begin();it!=_busyList.end();it++){
		(*it)->release();
	}
	_busyList.clear();
}