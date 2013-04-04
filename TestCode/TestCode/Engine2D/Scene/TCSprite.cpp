#include "TCSprite.h"
#include "TCDrawer.h"
NS_TC_BEGIN

Sprite::Sprite(){
	init();
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


Vector2f Sprite::size(){
	return drawer()->size()*worldScale();
}
Sprite::~Sprite(){

}

Sprite* Sprite::alloc(const std::string& key){
	Sprite* s=new Sprite();
	s->initWithImageName(key);
	s->autoRelease();
	return s;
}
NS_TC_END