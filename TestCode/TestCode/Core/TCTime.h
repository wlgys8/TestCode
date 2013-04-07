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
	static float _timeScale;

public:
	static inline void set(float deltaTime){
		_deltaTime=deltaTime;
	}
	static inline float deltaTime(){
		return _deltaTime*_timeScale;
	}

	static inline float realDeltaTime(){
		return _deltaTime;
	}

	static inline void setTimeScale(float scale){
		_timeScale=scale;
	}
	static inline float timeScale(){
		return _timeScale;
	}
};
NS_TC_END
#endif