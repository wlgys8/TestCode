#ifndef __TC_SPRITE_H__
#define __TC_SPRITE_H__
#include "BaseNode.h"
#include "TCDrawer.h"
#include <string>
#include "Rect.h"
NS_TC_BEGIN
class Sprite:public BaseNode{
private:
protected:
	Sprite();
	~Sprite();
	void initWithImageName(const std::string& imageName);
	void init();
public:
	inline TCDrawer* drawer(){
		return (TCDrawer*) getComponment(ComponentDrawer);
	}

	Vector2f size();

	void setImage(const std::string& imageName);
	static Sprite* alloc(const std::string& key);
};

NS_TC_END
#endif