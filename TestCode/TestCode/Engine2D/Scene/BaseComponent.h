#ifndef __TC_BASECOMPONENT_H__
#define __TC_BASECOMPONENT_H__
#include "BaseNode.h"

NS_TC_BEGIN
class BaseNode;

class BaseComponent:public AutoReleaseObject{
	friend class BaseNode;
private:
	BaseNode* _node;
	void attachToNode(BaseNode* node);
protected:
	~BaseComponent();
public:
	BaseComponent(){
		_node=NULL;
	}
	enum ComponentType virtual type()=0;
	inline BaseNode* node(){
		return _node;
	}
};
NS_TC_END
#endif