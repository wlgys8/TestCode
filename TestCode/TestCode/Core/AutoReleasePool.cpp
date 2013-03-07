#include "AutoReleasePool.h"
NS_TC_BEGIN

AutoReleasePool::AutoReleasePool(){

}
AutoReleasePool::~AutoReleasePool(){
	DebugLog("start destroy AutoReleasePool");
	removeAll();
	DebugLog("end destroy AutoReleasePool");
}
void AutoReleasePool::add(AutoReleaseObject* obj){
	_pool.push_back(obj);
}
bool AutoReleasePool::contains(const AutoReleaseObject* obj){
	if(obj==0||_pool.empty()){
		return false;
	}
	Iterator it;
	for(it==_pool.begin();it!=_pool.end();it++){
		if((*it)==obj){
			return true;
		}
	}
	 return false;
}
bool AutoReleasePool::remove(AutoReleaseObject* obj){
	if(obj==0||_pool.empty()){
		return false;
	}
	Iterator it;
	for(it==_pool.begin();it!=_pool.end();it++){
		if((*it)==obj){
			_pool.erase(it);
			return false;
		}
	}
	return true;
}

void AutoReleasePool::removeAll(){
	_pool.clear();
}

void AutoReleasePool::releaseAll(){
	if(_pool.empty()){
		return;
	}
	Iterator it;
	for(it=_pool.begin();it!=_pool.end();it++){
		(*it)->release();
	}
	_pool.clear();
}

NS_TC_END