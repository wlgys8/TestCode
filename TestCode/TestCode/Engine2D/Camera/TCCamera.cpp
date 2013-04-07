#include "TCCamera.h"
#include "tcgles.h"
#include "TCScreen.h"
#include "TCDrawer.h"
#include "TCTouchEvent.h"
#include "TCTouchComponent.h"
NS_TC_BEGIN


Camera::Camera(const std::string& name):
_name(name),_orthoSize(Vector2f(Screen::width(),Screen::height())),_viewPort(0,0,Screen::width(),Screen::height())
{
	_rootNode=BaseNode::alloc()->retain<BaseNode>();
}
Camera::~Camera(){
	if(_rootNode){
		_rootNode->release();
		_rootNode=0;
	}
}

static bool touchNode(BaseNode* node,TCTouchEvent& touchEvent,const TCMatrix3x3& worldToParentMatrix){
	TCMatrix3x3 worldToLocal=TCMatrix3x3(node->parentToLocalMatrix());
	worldToLocal.mul(worldToParentMatrix);
	touchEvent.setLocalPosition(worldToLocal.mulWithPoint(touchEvent.position()));
	vector<BaseNode*> list= node->childList();//a list copy
	vector<BaseNode*>::reverse_iterator rv_it;
	for(rv_it=list.rbegin();rv_it!=list.rend();rv_it++){
		if(touchNode(*rv_it,touchEvent,worldToLocal)){
			return true;
		}
	}
	TCTouchComponent* tc=(TCTouchComponent*)node->getComponment(ComponentTouch);
	if(tc){
		return tc->onDispatchTouch(touchEvent);
	}
	return false;
}

void Camera::dispatchTouch(TCTouchEvent& event){
	TCMatrix3x3 mat=TCMatrix3x3::matrixWithScale(_orthoSize.x/Screen::width(),_orthoSize.y/Screen::height());
	mat.mul(TCMatrix3x3::matrixWithTranslate(-Screen::width()/2,-Screen::height()/2));
	mat.mul(TCMatrix3x3::matrixWithScale(Screen::width()/_viewPort.width(),Screen::height()/_viewPort.height()));
	mat.mul(TCMatrix3x3::matrixWithTranslate(-_viewPort.xMin(),-_viewPort.yMin()));
	Vector2f p=mat.mulWithPoint(event.screenPosition());
	event.setPosition(p);
	touchNode(_rootNode,event,TCMatrix3x3());
}
static void updateNode(BaseNode* node){
	node->invokeUpdate();
	vector<BaseNode*> list= node->childList();//a list copy
	vector<BaseNode*>::iterator it;
	for(it=list.begin();it!=list.end();it++){
		updateNode(*it);
	}
}
void Camera::update(){
	updateNode(_rootNode);
}

static void drawNode(BaseNode* node,const TCMatrix3x3& parentToWorldMatrix){
	TCDrawer* drawer= (TCDrawer*)(node->getComponment(ComponentDrawer));
	TCMatrix3x3 localToWorldMatrix=TCMatrix3x3(parentToWorldMatrix);
	localToWorldMatrix.mul(node->localToParentMatrix());
	if(drawer){
		drawer->draw(localToWorldMatrix);
	}
	for (int i=0;i<node-> childCount();i++)
	{
		drawNode(node->getChild(i),localToWorldMatrix);
	}	
}

void Camera::render(){
	glViewport(_viewPort.xMin(),_viewPort.yMin(),_viewPort.width(),_viewPort.height());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrthof(-_orthoSize.x/2,_orthoSize.x/2,-_orthoSize.y/2,_orthoSize.y/2,-100,100);	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
//	TCMatrix3x3 mat=_rootNode->parentToLocalMatrix();
//	mat.mul(_rootNode->parentToLocalMatrix());
	drawNode(_rootNode,TCMatrix3x3());
}


BaseNode* Camera::rootNode(){
	return _rootNode;
}

NS_TC_END