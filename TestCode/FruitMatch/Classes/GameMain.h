#ifndef __GAMEMAIN_H__
#define __GAMEMAIN_H__
#include "TCSingleton.h"
#include "Role/Role.h"
#include "Map/MapData.h"
#include "TCTouchComponent.h"
#include "Enemy/Enemy.h"
USING_NS_TC;

class GameMain:public TCObject{
private:
	~GameMain();
	GameMain();
	Sprite* _background;
	Sprite* _pauseBtn;
	Enemy* _enemy;
	Sprite* _grass;
	bool onPauseDown(const TCTouchEvent& evt);

	void onGrassUpdate();

public:
	void init();

	void show(int lv);

	void hide();

	void resume();

	void reset();

	void loadTo(int lv);

	static GameMain* instance();



};
#endif