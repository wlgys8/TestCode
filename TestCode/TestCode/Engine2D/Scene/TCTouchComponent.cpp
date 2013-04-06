#include "TCTouchComponent.h"
#include "TCDrawer.h"
#include "RenderElements/TCRenderElement.h"
NS_TC_BEGIN

TCTouchComponent::TCTouchComponent():_delegateDown(0),_delegateMove(0),_delegateUp(0),_delegateTarget(0),_delegateClick(0),
_isPressed(false)
{

}
TCTouchComponent::~TCTouchComponent(){
	_delegateTarget=0;
}
bool TCTouchComponent::onDispatchTouch(const TCTouchEvent& touchEvent){
	if(!_delegateTarget){
		return false;
	}
	TCDrawer* drawer=(TCDrawer*) node()->getComponment(ComponentDrawer);
	if(!drawer){
		return false;
	}
	RenderElement* re=drawer->renderElement();
	if(!re){
		return false;
	}
	Vector2f size= re->rawSize();
	Rect bounds=Rect(-size.x/2,-size.y/2,size.x,size.y);
	bool isContains=bounds.contains(touchEvent.localPosition());
	bool ret=false;
	switch(touchEvent.type()){
	case LeftMouseDown:
		if(_delegateDown){
			if(!_isPressed&&isContains){
				ret=(_delegateTarget->*_delegateDown)(touchEvent);
				_isPressed=true;
			}
			break;
		}
	case RightMouseDown:
		break;
	case LeftMouseUp:
		if(_delegateUp){
			ret=(_delegateTarget->*_delegateUp)(touchEvent);
		}
		if(_isPressed){
			if(_delegateClick){
				ret=(_delegateTarget->*_delegateClick)(touchEvent);
			}
			_isPressed=false;
		}
		break;
	case RightMouseUp:
		break;
	case Move:
		if(_delegateMove){
			ret=(_delegateTarget->*_delegateMove)(touchEvent);
		}
		if(_isPressed&&!isContains){
			if(_delegateUp){
				ret=(_delegateTarget->*_delegateUp)(touchEvent);
				_isPressed=false;
			}
		}
		break;
	}
	return ret;

}

void TCTouchComponent::registerDownEvent(delegateTouch evt){
	_delegateDown=evt;
}

void TCTouchComponent::registerMoveEvent(delegateTouch evt){
	_delegateMove=evt;
}

void TCTouchComponent::registerUpEvent(delegateTouch evt){
	_delegateUp=evt;
}
void TCTouchComponent::registerClickEvent(delegateTouch evt){
	_delegateClick=evt;
}
NS_TC_END