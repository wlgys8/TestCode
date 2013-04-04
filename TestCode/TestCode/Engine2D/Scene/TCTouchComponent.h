#ifndef __TC_TOUCHCOMPONENT_H__
#define __TC_TOUCHCOMPONENT_H__
#include "BaseComponent.h"
#include "TCTouchEvent.h"
#include "AutoReleaseObject.h"
NS_TC_BEGIN
typedef bool (TCObject::*delegateTouch)(const TCTouchEvent& evt);
#define touchSelector(_SELECTOR) (delegateTouch)(&_SELECTOR)
class TCTouchComponent:public BaseComponent{
	
private:
	delegateTouch _delegateDown;
	delegateTouch _delegateUp;
	delegateTouch _delegateMove;
	delegateTouch _delegateClick;
	~TCTouchComponent();
	TCTouchComponent();
private:
	TCObject* _delegateTarget;//weak ref
	bool _isPressed;
public:

	void onDispatchTouch(const TCTouchEvent& touchEvent);

	inline void bindDelegateTarget(TCObject* target){
		_delegateTarget=target;
	}
	void registerDownEvent(delegateTouch evt);

	void registerMoveEvent(delegateTouch evt);

	void registerUpEvent(delegateTouch evt);

	void registerClickEvent(delegateTouch evt);

	ComponentType type(){
		return ComponentTouch;
	}
	static TCTouchComponent* alloc(){
		TCTouchComponent* ret=new TCTouchComponent();
		ret->autoRelease();
		return ret;
	}
};
NS_TC_END
#endif