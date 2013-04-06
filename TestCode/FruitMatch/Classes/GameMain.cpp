#include "GameMain.h"
#include "Map/FruitMap.h"
#include "TCSceneManager.h"
#include "TCAnimation.h"
#include "TCAnimationCurve.h"
#include "Enemy/Enemy.h"
#include "ParticleSystem/TCParticleSystem.h"
#include "Map/ConnectionEffect.h"
#include "Enemy/EnemyManager.h"
#include "Audio/AudioManager.h"
#include "Camera/TCCamera.h"
#include "Audio/TCAudioLoader.h"
#include "TCTextSprite.h"
#include "Map/MapDataManager.h"

static AudioSource* _src;

GameMain::GameMain(){
	_background=0;
	_src=0;
}
void GameMain::init(){
	if(_background){
		return;
	}
	_background=Sprite::alloc("bg.png");
	_background->retain();
	_background->addChild(FruitMap::instance()->node());

	ConnectionEffect::instance()->setSpaceNode(_background);

	_src=AudioManager::instance()->createSource("background.wav");
	_src->retain();
	_src->play(true);

	DebugLog("loaded");
//	unsigned long size;
//	unsigned char* stream=TCFileUtils::getFileData("background.wav",&size);
//	AudioLoader::loadOgg(stream,size);

}

void GameMain::show(){
	FruitMap::instance()->resetMap(MapDataManager::instance()->find("test.txt"));
	Camera* ca= TCSceneManager::instance()->findCamera("main");
	ca->rootNode()->addChild(_background);
}

void GameMain::hide(){
	_background->removeSelf();
}

GameMain::~GameMain(){
	if(_src){
		_src->release();
		_src=0;
	}
	if(_background){
		_background->release();
		_background=0;
	}
}