#ifndef __TC_BASENODE_H__
#define __TC_BASENODE_H__
#include <map>
#include <vector>
#include "AutoReleaseObject.h"
#include "TCVector2f.h"
#include "TCMatrix3x3.h"

using namespace std;
NS_TC_BEGIN

enum ComponentType{
	ComponentDrawer=0,
	ComponentTouch=1,
	ComponentAnimation=2,
	ComponentParticleSystem=3,
};

typedef void (TCObject::*delegateUpdate)();
#define updateSelector(_SELECTOR) (delegateUpdate)(&_SELECTOR)

class BaseComponent;
class AutoReleaseObject;
class AnimationContainer;

class BaseNode:public AutoReleaseObjectTemplete<BaseNode>{
	friend class AutoReleaseObjectTemplete<BaseNode>;
	typedef vector<BaseNode*> ArrayList;
	typedef ArrayList::iterator iterator;
	//====class=====///
private:
	ArrayList _childrenList;
	map<ComponentType,BaseComponent*> _componentMap;
	BaseNode* _parent;
	Vector2f _position;
	float _rotation;
	Vector2f _scale;
	TCObject* _updateTarget;//weak ref
	delegateUpdate _delegateUpdate;
protected:
	~BaseNode();
	BaseNode();
public:
	void addChild(BaseNode* child);

	BaseNode* getChild(int index);

	inline BaseNode* parent(){
		return _parent;
	}
	void removeAllChildren();

	void addComponent(BaseComponent* component);

	BaseComponent* getComponment(ComponentType type);

	AnimationContainer* animation();

	void removeAllComponement();

	inline int childCount(){
		return _childrenList.size();
	}

	bool removeChild(BaseNode* child);

	inline const ArrayList& childList() const{
		return _childrenList;
	}
//transform

	inline Vector2f localPosition(){
		return _position;
	}
	inline void setLocalPosition(const Vector2f& pos){
		_position=pos;
	}
	inline Vector2f worldPosition(){
		if(_parent){
			return _position+_parent->worldPosition();
		}
		return _position;
	}
	inline void setWorldPosition(const Vector2f& pos){
		_position+=(pos-worldPosition());
	}

	inline void setRotation(const float& degree){
		_rotation=degree;
	}

	inline void rotate(const float& degree){
		_rotation+=degree;
	}
	inline const float& localRotation(){
		return _rotation;
	}

	inline void scale(const Vector2f& scale){
		_scale*=scale;
	}
	inline void setLocalScale(const Vector2f& scale){
		_scale=scale;
	}

	inline const Vector2f& localScale(){
		return _scale;
	}

	inline const Vector2f worldScale(){
		if(_parent){
			return _parent->worldScale()*_scale;
		}
		return _scale;
	}

	TCMatrix3x3 localToParentMatrix() const;

	TCMatrix3x3 parentToLocalMatrix() const;


	inline void registerUpdate(TCObject* target,delegateUpdate updateAction){
		_updateTarget=target;//weak ref
		_delegateUpdate=updateAction;
	}

	void virtual invokeUpdate();

	void removeSelf();

private:
	static int _count;
public:
	static int count();
};

NS_TC_END
#endif