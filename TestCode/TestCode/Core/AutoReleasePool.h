#ifndef __AUTO_RELEASE_POOL_H__
#define __AUTO_RELEASE_POOL_H__
#include "AutoReleaseObject.h"
#include "TCSingleton.h"
#include <vector>
NS_TC_BEGIN
class AutoReleaseObject;

class AutoReleasePool:public TCSingleton<AutoReleasePool>{
	friend class  TCSingleton<AutoReleasePool>;
	typedef std::vector<AutoReleaseObject*> Array;
	typedef  Array::iterator Iterator;
private:
	Array _pool;
private:
	AutoReleasePool();
	~AutoReleasePool();
	bool remove(AutoReleaseObject* obj);
	void removeAll();	
public:
	void add(AutoReleaseObject* obj);
	bool contains(const AutoReleaseObject* obj);
	void releaseAll();
};

NS_TC_END;
#endif