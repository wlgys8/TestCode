#ifndef __FRUIT_H__
#define __FRUIT_H__
#include "tooold.h"
#include "TCSprite.h"
#include "TCTouchComponent.h"
USING_NS_TC;

enum FruitType{
	FRUIT_APPLE,
	FRUIT_ORANGE,
	FRUIT_BOLO,
	FRUIT_CAOMEI,
	FRUTT_LANMEI,
	FRUIT_MANGGUO,
	FRUIT_PUTAO,
	FRUIT_XIGUA,
	FRUIT_YINTAO,
};
class Fruit:public AutoReleaseObject{

private:
	Sprite* _sprite;
	FruitType _type;
	bool onDown(const TCTouchEvent& evt);
	bool onClick(const TCTouchEvent& evt);
	static Fruit* _pickedFruit;
protected:
	Fruit(FruitType type);
	~Fruit();
	void init(const std::string& key);

	void onUpdate();
public:
	inline Sprite* sprite(){
		return _sprite;
	}

	inline FruitType type(){
		return _type;
	}

	static Fruit* alloc(FruitType type){
		Fruit* ret=new Fruit(type);
		ret->autoRelease();
		return ret;
	}
};
#endif