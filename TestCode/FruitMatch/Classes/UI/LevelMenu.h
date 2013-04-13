#ifndef __LEVEL_MENU_H__
#define __LEVEL_MENU_H__
#include "TCObject.h"
#include "BaseNode.h"
#include "TCSprite.h"
#include "ui/LevelEntryButton.h"
USING_NS_TC;
class LevelMenu:public TCObject{

private:
	Sprite* _root;
	LevelMenu();
	~LevelMenu();
	std::vector<LevelEntryButton*> _buttonList;
public: 

	void init();

	void show();

	void hide();

	static LevelMenu* instance();
};
#endif