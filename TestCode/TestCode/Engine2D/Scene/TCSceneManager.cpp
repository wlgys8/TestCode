#include "TCSceneManager.h"
#include "TCDrawer.h"
#include "TCTouchComponent.h"
NS_TC_BEGIN

TCSceneManager::TCSceneManager(){
	_rootNode=BaseNode::alloc()->retain<BaseNode>();
	DebugLog("new scene manager");
}

TCSceneManager::~TCSceneManager(){
	_rootNode->release();
	_rootNode=NULL;
	DebugLog("delete scene manager");
}

void TCSceneManager::addChild(BaseNode* child){
	_rootNode->addChild(child);
}

void TCSceneManager::drawNode(BaseNode* node,const TCMatrix3x3& parentToWorldMatrix){
	TCDrawer* drawer= (TCDrawer*)(node->getComponment(ComponentDrawer));
	TCMatrix3x3 localToWorldMatrix=TCMatrix3x3(parentToWorldMatrix);
	localToWorldMatrix.mul(node->localToParentMatrix());
	if(drawer){
		drawer->draw(localToWorldMatrix);
	}
	for (int i=0;i<node-> size();i++)
	{
		drawNode(node->getChild(i),localToWorldMatrix);
	}	
}

void TCSceneManager::touchNode(BaseNode* node,TCTouchEvent& touchEvent,const TCMatrix3x3& worldToParentMatrix){
	TCMatrix3x3 worldToLocal=TCMatrix3x3(node->parentToLocalMatrix());
	worldToLocal.mul(worldToParentMatrix);
	touchEvent.setLocalPosition(worldToLocal.mulWithPoint(touchEvent.position()));
	vector<BaseNode*> list= node->childList();//a list copy
	vector<BaseNode*>::reverse_iterator rv_it;
	for(rv_it=list.rbegin();rv_it!=list.rend();rv_it++){
		touchNode(*rv_it,touchEvent,worldToLocal);
	}
	TCTouchComponent* tc=(TCTouchComponent*)node->getComponment(ComponentTouch);
	if(tc){
		tc->onDispatchTouch(touchEvent);
	}
}

static void updateNode(BaseNode* node){
	node->invokeUpdate();
	vector<BaseNode*> list= node->childList();//a list copy
	vector<BaseNode*>::iterator it;
	for(it=list.begin();it!=list.end();it++){
		updateNode(*it);
	}
}
void TCSceneManager::loopUpdate(){
	
	updateNode(_rootNode);
}
void TCSceneManager::loopDraw(){
	drawNode(_rootNode,TCMatrix3x3());
}

void TCSceneManager::dispatchTouch( TCTouchEvent& event){
	touchNode(_rootNode,event,TCMatrix3x3());
}

TCSceneManager* TCSceneManager::instance(){
	static TCSceneManager _instance;
	return &_instance;
}

NS_TC_END