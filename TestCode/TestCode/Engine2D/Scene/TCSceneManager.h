#ifndef __TC_SCENEMANAGER_H__
#define __TC_SCENEMANAGER_H__

#include "TCSingleton.h"
#include "BaseNode.h"
#include "TCTouchEvent.h"
#include <map>
#include <string>
NS_TC_BEGIN
	class Camera;
class TCSceneManager{
	typedef std::map<std::string,Camera*> CameraMap;
private:
	CameraMap _cameraMap;
	
private:

	TCSceneManager();
	~TCSceneManager();

public:

	static TCSceneManager* instance();

	void dispatchTouch(TCTouchEvent& event);

	void loopUpdate();

	void loopDraw();
	
	Camera* findCamera(const std::string& name);
	Camera* createCamera(const std::string& name="main");

};
NS_TC_END
#endif