#ifndef __GAMEMAIN_H__
#define __GAMEMAIN_H__
#include "TCSingleton.h"
#include "Role/Role.h"
#include "Map/MapData.h"
#include "TCTouchComponent.h"
USING_NS_TC;

class GameMain:public TCObject{
private:
	~GameMain();
	GameMain();
	Sprite* _background;
	Sprite* _pauseBtn;

	bool onPauseDown(const TCTouchEvent& evt);

public:
	void init();

	void show(int lv);

	void hide();

	void resume();

	static GameMain* instance();



};
#endif