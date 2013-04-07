#ifndef __LEVEL_ENTRY_BUTTON_H__
#define __LEVEL_ENTRY_BUTTON_H__

#include "TCSprite.h"
#include "TCTouchEvent.h"
#include "TCTextSprite.h"
USING_NS_TC;

class LevelEntryButton:public Sprite{

private:
	LevelEntryButton();
	~LevelEntryButton();
	void init();

	bool onDown(const TCTouchEvent& evt);

	TextSprite* _levelNum;
public:

	void updateUI(int level);

	static LevelEntryButton* alloc();
};
#endif