#ifndef __GAMEMAIN_H__
#define __GAMEMAIN_H__
#include "TCSingleton.h"
#include "Role/Role.h"
USING_NS_TC;

class GameMain:public TCSingleton<GameMain>{
	friend class  TCSingleton<GameMain>;
private:

	~GameMain();
public:
	void initGame();
};
#endif