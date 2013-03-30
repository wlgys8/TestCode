#ifndef __TC_SCENEMANAGER_H__
#define __TC_SCENEMANAGER_H__

#include "TCSingleton.h"
#include "BaseNode.h"
#include "TCTouchEvent.h"
NS_TC_BEGIN
class TCSceneManager{
//	friend class TCSingleton<TCSceneManager>;
private:
	BaseNode* _rootNode;
private:

	TCSceneManager();
	~TCSceneManager();
	void drawNode(BaseNode* node,const TCMatrix3x3& parentToWorldMatrix);

	void touchNode(BaseNode* node, TCTouchEvent& touchEvent,const TCMatrix3x3& worldToParentMatrix);

public:

	static TCSceneManager* instance();

	void addChild(BaseNode* childNode);

	void dispatchTouch(TCTouchEvent& event);

	void loopUpdate();

	void loopDraw();
	
};
NS_TC_END
#endif