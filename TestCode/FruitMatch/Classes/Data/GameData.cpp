#include "Data/GameData.h"
#include "UserPref.h"

int GameData::currentLevel=0;
int GameData::unlockedLevel=0;

using namespace testCode;

void GameData::load(){
	unlockedLevel=UserPref::instance()->getInt("level",0);
}
void GameData::save(){
	UserPref::instance()->setInt("level",unlockedLevel);
	UserPref::instance()->save();
}