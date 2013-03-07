#ifndef __TC_TOUCHEVENT_H__
#define __TC_TOUCHEVENT_H__
#include "TCVector2f.h"
NS_TC_BEGIN

enum TouchEventType{
	LeftMouseDown,
	LeftMouseUp,
	RightMouseDown,
	RightMouseUp,
	Move,
};
class TCTouchEvent{

private:
	TouchEventType _type;
	Vector2f _position;
	Vector2f _localPosition;
public:
	inline TouchEventType type()const {
		return _type;
	}
	inline Vector2f position()const {
		return _position;
	}

	inline void setLocalPosition(Vector2f localPosition){
		_localPosition=localPosition;
	}
	
	inline Vector2f localPosition() const{
		return _localPosition;
	}
	inline void set(TouchEventType type,Vector2f vect){
		_type=type;
		_position=vect;
	}
};

NS_TC_END

#endif