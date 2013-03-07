#ifndef __TC_SPRITE_H__
#define __TC_SPRITE_H__
#include "BaseNode.h"
#include "TCDrawer.h"
#include <string>
NS_TC_BEGIN
class Sprite:public BaseNode{

protected:
	Sprite(const std::string& key);
	~Sprite();
public:
	inline TCDrawer* drawer(){
		return (TCDrawer*) getComponment(ComponentDrawer);
	}
	static Sprite* alloc(const std::string& key);
};

NS_TC_END
#endif