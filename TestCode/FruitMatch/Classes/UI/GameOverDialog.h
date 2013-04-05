#ifndef __GAMEOVER_DIALOG_H__
#define __GAMEOVER_DIALOG_H__

#include "TCCommon.h"
#include "TCSprite.h"
#include "TCRectangleRGBA.h"
USING_NS_TC;

class GameOverDialog{

private:
	RectangleRGBA* _blackMask;
	Sprite* _background;
private:
	GameOverDialog();
	~GameOverDialog();
public:
	void show();
	void hide();
	static GameOverDialog* instance();

};


#endif