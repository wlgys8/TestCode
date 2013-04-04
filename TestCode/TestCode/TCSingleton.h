#ifndef __TC_SINGLETON_H__
#define __TC_SINGLETON_H__
#include "TCCommon.h"
#include <typeinfo>
NS_TC_BEGIN
	template<class T>
class TCSingleton{

private:
	TCSingleton(const TCSingleton& rhs);//UnCopyable
	TCSingleton& operator=(const TCSingleton& rhs);
protected:
	TCSingleton(){};
	virtual ~TCSingleton(){};
public:
	static  T*  instance();
};

template<class T>
T* TCSingleton<T>::instance(){
	static T t;
	return &t;
}
NS_TC_END
#endif
