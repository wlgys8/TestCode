#include "BaseNode.h"
#include "TCDrawer.h"
#include "TCAnimation.h"
NS_TC_BEGIN

BaseNode::BaseNode():_parent(NULL),_rotation(0),_position(Vector2f()),
_updateTarget(0),
_delegateUpdate(0)
{
	_childrenList=ArrayList();
	_componentMap=map<ComponentType,BaseComponent*>();
}
BaseNode::~BaseNode(){
	DebugLog("delete a node");
	removeAllComponement();
	removeAllChildren();
}
void BaseNode::addChild(BaseNode* child){
	if(child->_parent){
		child->removeSelf();
	}
	_childrenList.push_back(child);
	child->_parent=this;
	child->retain();
}
bool BaseNode::removeChild(BaseNode* child){
	iterator it;
	for(it=_childrenList.begin();it!=_childrenList.end();it++){
		if((*it)==child){
			_childrenList.erase(it);
			child->_parent=NULL;
			child->autoRelease();
			return true;
		}
	}
	return false;
}
BaseNode* BaseNode::getChild(int index){
	return _childrenList.at(index);
}
void BaseNode::removeAllChildren(){
	iterator it;
	for(it=_childrenList.begin();it!=_childrenList.end();it++){
		(*it)->_parent=NULL;
		(*it)->release();
	}
	_childrenList.clear();
}

void BaseNode::addComponent(BaseComponent* component){
	component->retain();
	component->attachToNode(this);
	_componentMap[component->type()]=component;
}

void BaseNode::removeAllComponement(){
	map<ComponentType,BaseComponent*>::iterator it;
	for(it=_componentMap.begin();it!=_componentMap.end();it++){
		it->second->attachToNode(NULL);
		it->second->release();

	}
	_componentMap.clear();
}

BaseComponent* BaseNode::getComponment(ComponentType type){
	map<ComponentType,BaseComponent*>::iterator it= _componentMap.find(type);
	if(it==_componentMap.end()){
		return 0;
	}else{
		return it->second;
	}
}
testCode::AnimationContainer* BaseNode::animation(){
	map<ComponentType,BaseComponent*>::iterator it= _componentMap.find(ComponentAnimation);
	if(it==_componentMap.end()){
		AnimationContainer* ret=AnimationContainer::alloc()->retain<AnimationContainer>();
		_componentMap[ComponentAnimation]=ret;
		return ret;
	}
	return (AnimationContainer*)(it->second);
}

TCMatrix3x3 BaseNode::localToParentMatrix() const{
	TCMatrix3x3 rotMat=TCMatrix3x3::matrixWithRotation(_rotation);
	TCMatrix3x3 translateMat=TCMatrix3x3::matrixWithTranslate(_position.x,_position.y);
	translateMat.mul(rotMat);
	return translateMat;
}

TCMatrix3x3 BaseNode::parentToLocalMatrix() const{
	TCMatrix3x3 translateMat=TCMatrix3x3::matrixWithTranslate(-_position.x,-_position.y);
	TCMatrix3x3 rotMat=TCMatrix3x3::matrixWithRotation(-_rotation);
	rotMat.mul(translateMat);
	return rotMat;
}
void BaseNode::invokeUpdate(){
	if(_updateTarget&&_delegateUpdate){
		(_updateTarget->*_delegateUpdate)();
	}
	AnimationContainer* anim=(AnimationContainer*) getComponment(ComponentAnimation);
	if(anim){
		anim->invokeUpdate(this);
	}
}

void BaseNode::removeSelf(){
	if(_parent){
		_parent->removeChild(this);
	}


}

//static method

NS_TC_END