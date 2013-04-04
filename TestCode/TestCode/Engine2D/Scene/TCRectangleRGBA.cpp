#include "TCRectangleRGBA.h"
#include "TCDrawer.h"
#include "RenderElements/TCRectRenderElement.h"
NS_TC_BEGIN

RectangleRGBA::RectangleRGBA(){
}

void RectangleRGBA::init(){
	TCDrawer* drawer=TCDrawer::alloc();
	RenderElement* e=RectRenderElement::alloc();
	drawer->setRenderElement(e);
	addComponent(drawer);
}

TCDrawer* RectangleRGBA::drawer(){
	return (TCDrawer*) getComponment(ComponentDrawer);
}

void RectangleRGBA::setSize(const Vector2f& size){
	RectRenderElement* re=(RectRenderElement*)( drawer()->renderElement());
	re->setRawSize(size);
}

RectangleRGBA::~RectangleRGBA(){

}

RectangleRGBA* RectangleRGBA::alloc(){
	RectangleRGBA* ret=new RectangleRGBA();
	ret->init();
	ret->autoRelease();
	return ret;
}



NS_TC_END