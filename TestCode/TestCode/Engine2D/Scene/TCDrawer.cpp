#include "TCDrawer.h"
#include "TCTransform.h"
#include "TCSceneRenderer.h"
#include "RenderElements/TCRenderElement.h"

NS_TC_BEGIN


void TCDrawer::draw(const TCMatrix3x3& localToWorldMatrix){
	if(!_renderElement){
		return;
	}
	_renderElement->onRender(localToWorldMatrix,_paint);
}

void TCDrawer::setRenderElement(RenderElement* e){
	if(_renderElement){
		_renderElement->autoRelease();
	}
	_renderElement=e;
	if(e){
		e->retain();
	}
}

TCDrawer::TCDrawer(){
	_renderElement=0;
}
TCDrawer::~TCDrawer(){
	if(_renderElement){
		_renderElement->release();
		_renderElement=0;
	}
}

TCDrawer* TCDrawer::alloc(){
	TCDrawer* ret=new TCDrawer();
	ret->autoRelease();
	return ret;
}
NS_TC_END