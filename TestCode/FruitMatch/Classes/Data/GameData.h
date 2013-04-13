#ifndef __GAMEDATA_H__
#define __GAMEDATA_H__

class GameData{


public:
	static int currentLevel;
	static int unlockedLevel;

	static void load();
	static void save();
};
#endif