#include "TCSprite.h"
#include "TCDrawer.h"
NS_TC_BEGIN

Sprite::Sprite(const std::string& key){
	TextureRegion* region= TextureRegionManager::instance()->get(key);
	//if not exist?
	addComponent(TCDrawer::alloc(region));
}

Sprite::~Sprite(){
	DebugLog("delete a sprite");
}

Sprite* Sprite::alloc(const std::string& key){
	Sprite* s=new Sprite(key);
	s->autoRelease();
	return s;
}
NS_TC_END