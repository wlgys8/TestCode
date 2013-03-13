#include "BaseComponent.h"
NS_TC_BEGIN

BaseComponent::~BaseComponent(){
//	DebugLog("delete a component");

}
void BaseComponent::attachToNode(BaseNode* node){
	_node=node;//don't retain.avoid circular reference
}
NS_TC_END