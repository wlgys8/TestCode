#ifndef __GAMEMAIN_H__
#define __GAMEMAIN_H__
#include "TCSingleton.h"
#include "Role/Role.h"
#include "Map/MapData.h"
USING_NS_TC;

class GameMain:public TCSingleton<GameMain>{
	friend class  TCSingleton<GameMain>;
private:
	~GameMain();
	GameMain();
	Sprite* _background;
public:
	void init();

	void show();

	void hide();



};
#endif