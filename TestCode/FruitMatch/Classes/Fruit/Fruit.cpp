#include "Fruit.h"
#include "TCTime.h"
#include "Map/FruitMap.h"
Fruit::Fruit(FruitType type){
	if(type==FRUIT_APPLE){
		init("pingguo.png");
	}else if(type==FRUIT_ORANGE){
		init("juzi.png");
	}else if(type==FRUIT_BOLO){
		init("boluo.png");
	}else if(type==FRUIT_CAOMEI){
		init("caomei.png");
	}else if(type==FRUTT_LANMEI){
		init("lanmei.png");
	}else if(type==FRUIT_MANGGUO){
		init("mangguo.png");
	}else if(type==FRUIT_PUTAO){
		init("putao.png");
	}else if(type==FRUIT_XIGUA){
		init("xigua.png");
	}else if(type==FRUIT_YINTAO){
		init("yingtao.png");
	}
	_type=type;
}
void Fruit::init(const std::string& key){
	_sprite=Sprite::alloc(key)->retain<Sprite>();
	TCTouchComponent* tc= TCTouchComponent::alloc();
	tc->bindDelegateTarget(this);
	tc->registerDownEvent(touchSelector(Fruit::onClick));
	_sprite->addComponent(tc);
//	Paint p=Paint();
///	p.setBlendMode(BLEND_SRC_ALPHA,BLEND_ONE);
//	_sprite->drawer()->setPaint(p);
	//_sprite->registerUpdate(this,updateSelector( Fruit::onUpdate));
}

bool Fruit::onClick(const TCTouchEvent* evt){
	_sprite->rotate(45);
	Vector2 v=FruitMap::instance()->xy2ij(evt->position());
	int ret=FruitMap::instance()->select(v);
	if(ret==0){
		DebugLog("match");
	}
	return true;
}

void Fruit::onUpdate(){
	if(_sprite){
		_sprite->rotate(10*Time::deltaTime());
	}
}
Fruit::~Fruit(){
	_sprite->registerUpdate(0,0);//unregister the delegate function before deleted;
	_sprite->release();
	_sprite=0;
}