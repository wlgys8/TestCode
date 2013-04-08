#include "TCSceneManager.h"
#include "TCDrawer.h"
#include "TCTouchComponent.h"
NS_TC_BEGIN

TCSceneManager::TCSceneManager(){

}

TCSceneManager::~TCSceneManager(){
	CameraMap::iterator it;
	for(it=_cameraMap.begin();it!=_cameraMap.end();it++){
		it->second->release();
	}
	_cameraMap.clear();
}

void TCSceneManager::loopUpdate(){
	CameraMap::iterator it;
	for(it=_cameraMap.begin();it!=_cameraMap.end();it++){
		it->second->update();
	}
}
void TCSceneManager::loopDraw(){
	CameraMap::iterator it;
	for(it=_cameraMap.begin();it!=_cameraMap.end();it++){
		it->second->render();
	}
}

void TCSceneManager::dispatchTouch( TCTouchEvent& event){
	CameraMap::iterator it;
	for(it=_cameraMap.begin();it!=_cameraMap.end();it++){
		it->second->dispatchTouch(event);
	}
}

Camera* TCSceneManager::createCamera(const std::string& name){
	Camera* ret=findCamera(name);
	if(ret){
		DebugLog("Camera named by %s has existed.",name.c_str());
		return ret;
	}
	ret=new Camera(name);
	_cameraMap[name]=ret;
	return ret;
}

Camera* TCSceneManager::findCamera(const std::string& name){
	CameraMap::iterator it=_cameraMap.find(name);
	if(it!=_cameraMap.end()){
		return it->second;
	}
	return 0;
}
TCSceneManager* TCSceneManager::instance(){
	static TCSceneManager _instance;
	return &_instance;
}

NS_TC_END