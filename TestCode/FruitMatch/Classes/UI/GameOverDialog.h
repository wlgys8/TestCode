#ifndef __GAMEOVER_DIALOG_H__
#define __GAMEOVER_DIALOG_H__

#include "TCCommon.h"
#include "TCSprite.h"
#include "TCRectangleRGBA.h"
#include "TCTouchEvent.h"
USING_NS_TC;

class GameOverDialog:public TCObject{

private:
	RectangleRGBA* _blackMask;
	Sprite* _background;
	Sprite* _restart;
	Sprite* _menu;
	Sprite* _next;
private:
	GameOverDialog();
	~GameOverDialog();

	bool onRestartClick(const TCTouchEvent& evt);
	bool onMenuClick(const TCTouchEvent& evt);
	bool onNextClick(const TCTouchEvent& evt);
	bool onMaskDown(const TCTouchEvent& evt);
public:
	void show(bool win);
	void hide();
	static GameOverDialog* instance();

};


#endif