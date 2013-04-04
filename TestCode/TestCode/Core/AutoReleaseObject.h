#ifndef __AUTO_RELEASE_OBJECT_H__
#define __AUTO_RELEASE_OBJECT_H__
#include "TCCommon.h"
#include "AutoReleasePool.h"
#include "TCObject.h"
NS_TC_BEGIN
class AutoReleasePool;

class AutoReleaseObject:public TCObject{
private:
	int _referCount;
protected:
	virtual ~AutoReleaseObject(){
	}
public:
	AutoReleaseObject():_referCount(1){
		
	}

	inline AutoReleaseObject* retain(){
		_referCount++;
		return this;
	}
	template<class T>
	inline T* retain(){
		_referCount++;
		T* ret= dynamic_cast<T*>(this);
		assert(ret!=0);
		return ret;
	}
	inline virtual void release(){
		assert(_referCount>0);
		_referCount--;
		if(_referCount==0){
			delete this;
		}
	}

	inline int referCount(){
		return _referCount;
	}
	void autoRelease();
};

template<class T>
class AutoReleaseObjectTemplete:public AutoReleaseObject{


public:
	static T* alloc(){
		T* t=new T();
		t->autoRelease();
		return t;
	}
protected:
};

NS_TC_END
#endif