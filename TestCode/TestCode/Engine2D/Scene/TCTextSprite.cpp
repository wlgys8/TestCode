#include "TCTextSprite.h"
#include "RenderElements/TCImageListRenderElement.h"
#include "TCDrawer.h"
#include "Font/TCCustomFont.h"
NS_TC_BEGIN


TextSprite::TextSprite(){
	_font=0;
}
void TextSprite::init(){
	TCDrawer* drawer=TCDrawer::alloc();
	ImageListRenderElement* e=ImageListRenderElement::alloc();
	drawer->setRenderElement(e);
	addComponent(drawer);
}

void TextSprite::setFont(CustomFont* font){
	if(_font){
		_font->autoRelease();
	}
	if(font){
		font->retain();
	}
	_font=font;
}
TCDrawer* TextSprite::drawer(){
	return (TCDrawer*) getComponment(ComponentDrawer);
}

void TextSprite::setAlgin(TextAlgin algin){
	ImageListRenderElement* e=(ImageListRenderElement*)drawer()->renderElement();
	if(algin==AlginLeft){
		e->setOffset(Vector2f::zero());
	}else if(algin==AlginMiddle){
		Vector2f size=e->rawSize();
		e->setOffset(Vector2f(-size.x/2,0));
	}else if(algin==AlginRight){
		Vector2f size=e->rawSize();
		e->setOffset(Vector2f(size.x/2,0));
	}
	_algin=algin;
}
void TextSprite::setText(const std::string& text){
	if(!_font){
		return;
	}
	ImageListRenderElement* e=(ImageListRenderElement*)drawer()->renderElement();
	e->clearList();
	_text=text;
	for(int i=0;i<text.length();i++){
		TextureRegion* region=_font->indexOf(text.substr(i,1));
		e->append(region);
	}
	setAlgin(_algin);
}

const std::string& TextSprite::text(){
	return _text;
}

TextSprite::~TextSprite(){
	if(_font){
		_font->release();
		_font=0;
	}
}

TextSprite* TextSprite::alloc(){
	TextSprite* ret=new TextSprite();
	ret->init();
	ret->autoRelease();
	return ret;
}

NS_TC_END