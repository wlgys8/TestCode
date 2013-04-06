#ifndef __TC_TEXTSPRITE_H__
#define __TC_TEXTSPRITE_H__

#include "BaseNode.h"

NS_TC_BEGIN

enum TextAlgin{
AlginLeft=0,
AlginMiddle,
AlginRight,
};

class TCDrawer;
class CustomFont;
class TextSprite:public BaseNode{
private:
	CustomFont* _font;
	std::string _text;
	TextAlgin _algin;
private:
	TextSprite();
	~TextSprite();
	void init();
public:
	TCDrawer* drawer();
	void setText(const std::string& text);

	void setFont(CustomFont* font);

	void setAlgin(TextAlgin algin);

	inline TextAlgin algin(){
		return _algin;
	}
	const std::string& text();

	static TextSprite* alloc();
};

NS_TC_END

#endif