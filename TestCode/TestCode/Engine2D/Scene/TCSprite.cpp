#include "TCSprite.h"
#include "TCDrawer.h"
#include "RenderElements/TCSpriteRenderElement.h"
NS_TC_BEGIN

Sprite::Sprite(){

}

Sprite::Sprite(const std::string& imageName){
	initWithImageName(imageName);
}
void Sprite::initWithImageName(const std::string& imageName){
	TCDrawer* drawer=TCDrawer::alloc();
	TextureRegion* region=TextureRegionManager::instance()->get(imageName);
	RenderElement* e=SpriteRenderElement::alloc(region);
	drawer->setRenderElement(e);
	addComponent(drawer);
}

void Sprite::setImage(const std::string& imageName){
	TextureRegion* region=TextureRegionManager::instance()->get(imageName);
	SpriteRenderElement* re=(SpriteRenderElement*)(drawer()->renderElement());
	re->setTextureRegion(region);
}

Vector2f Sprite::size(){
	SpriteRenderElement* re=(SpriteRenderElement*)(drawer()->renderElement());
	return re->rawSize()*worldScale();
}

void Sprite::setPart(const Rect& part){
	SpriteRenderElement* re=(SpriteRenderElement*)(drawer()->renderElement());
	re->setPart(part);
}

Sprite::~Sprite(){

}

Sprite* Sprite::alloc(const std::string& key){
	Sprite* s=new Sprite(key);
	s->autoRelease();
	return s;
}
NS_TC_END