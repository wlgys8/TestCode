#ifndef __TC_ARRAYLIST_H__
#define __TC_ARRAYLIST_H__
#include "AutoReleaseObject.h"
#include <vector>

NS_TC_BEGIN
template<class T>
class TCArrayList:public AutoReleaseObject{
private:
	typedef std::vector<T> array_t;
	typedef typename array_t::iterator iterator_t;
	array_t _arrayList;
	~TCArrayList(){
		removeAll();
	}
public:
	TCArrayList(int capacity=0){
		_arrayList=array_t(capacity);
	}
	void add(T  element){
		_arrayList.push_back(element);
	}
	T removeAt(int index){
		int size=_arrayList.size();
		if(index<0||index>size-1){
			DebugLog("index exceed the bounds:index=%d",index);
			assert(false);
			return NULL;
		}
		AutoReleaseObject* ret=_arrayList[index];
		remove((T)ret);
		return (T)ret;
	}
	void remove(T  element){
		if(element==0||_arrayList.empty()){
			return;
		}
		iterator_t it;

		for(it=_arrayList.begin();it!=_arrayList.end();it++){
			if(*it==element){
				_arrayList.erase(it);
				return;
			}
		}
	}
	void removeAll(){
		_arrayList.clear();
	}

	T get(int index){
		return _arrayList[index];
	}

	inline int size(){
		return _arrayList.size();
	}

};

NS_TC_END
#endif