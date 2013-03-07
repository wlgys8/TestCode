#ifndef __TC_TIME_H__
#define __TC_TIME_H__
#include "TCApplication_win32.h"
NS_TC_BEGIN
class Time{
	friend class TCApplication_win32;
private:
	static float _deltaTime;

public:
	static inline void set(float deltaTime){
		_deltaTime=deltaTime;
	}
	static inline float deltaTime(){
		return _deltaTime;
	}
};
NS_TC_END
#endif