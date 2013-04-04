#ifndef __TC_CAMERA_H__
#define __TC_CAMERA_H__

#include "TCCommon.h"
#include "BaseNode.h"
#include <string>
#include "AutoReleaseObject.h"
#include "TCVector2f.h"
#include "Rect.h"
#include <map>
#include "TCTouchEvent.h"
NS_TC_BEGIN
class Camera:public AutoReleaseObject{

	friend class TCSceneManager;

private:
	BaseNode* _rootNode;
	Camera(const std::string& name);
	~Camera();
	std::string _name;
	Vector2f _orthoSize;
	Rect _viewPort;
	
public:

	inline void setViewport(float x,float y,float w,float h){
		_viewPort=Rect(x,y,w,h);
	}

	inline void setOrthof(float w,float h){
		_orthoSize=Vector2f(w,h);
	}

	BaseNode* rootNode();

	void dispatchTouch(TCTouchEvent& event);

	void update();

	void render();

	
};
NS_TC_END
#endif