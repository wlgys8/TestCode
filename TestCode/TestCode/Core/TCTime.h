#ifndef __TC_TIME_H__
#define __TC_TIME_H__
#include "TCCommon.h"

#if TC_TARGET_PLATFORM==TC_PLATFORM_WIN32
 #include "TCApplication_win32.h"
#endif

NS_TC_BEGIN

class Time{
#if TC_TARGET_PLATFORM==TC_PLATFORM_WIN32
	friend class TCApplication_win32;
#endif
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