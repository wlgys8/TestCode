#include "TCSprite.h"
#include "TCDrawer.h"
NS_TC_BEGIN

Sprite::Sprite(){
	addComponent(TCDrawer::alloc(NULL));
}
void Sprite::initWithImageName(const std::string& imageName){
	init();
	setImage(imageName);
}

void Sprite::init(){
	addComponent(TCDrawer::alloc(NULL));
}

void Sprite::setImage(const std::string& imageName){
	TextureRegion* region=TextureRegionManager::instance()->get(imageName);
	drawer()->setTextureRegion(region);
}
Sprite::~Sprite(){
	DebugLog("delete a sprite");
}

Sprite* Sprite::alloc(const std::string& key){
	Sprite* s=new Sprite();
	s->initWithImageName(key);
	s->autoRelease();
	return s;
}
NS_TC_END