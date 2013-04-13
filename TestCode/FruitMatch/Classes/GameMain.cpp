#include "GameMain.h"
#include "Map/FruitMap.h"
#include "TCSceneManager.h"
#include "TCAnimation.h"
#include "TCAnimationCurve.h"
#include "Enemy/Enemy.h"
#include "ParticleSystem/TCParticleSystem.h"
#include "Map/ConnectionEffect.h"
#include "Audio/AudioManager.h"
#include "Camera/TCCamera.h"
#include "Audio/TCAudioLoader.h"
#include "TCTextSprite.h"
#include "Map/MapDataManager.h"
#include "TCTime.h"
#include "ui/PauseDialog.h"
#include "data/GameData.h"
#include "ui/GameOverDialog.h"
#include <sstream>
static AudioSource* _src;

GameMain::GameMain(){
	_background=0;
	_src=0;
	_pauseBtn=0;
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

	_pauseBtn=Sprite::alloc("pause_btn.png");
	_pauseBtn->retain();

	TCTouchComponent* tc=TCTouchComponent::alloc();
	tc->bindDelegateTarget(this);
	tc->registerDownEvent(touchSelector(GameMain::onPauseDown));
	_pauseBtn->addComponent(tc);
	_background->addChild(_pauseBtn);
	_pauseBtn->setLocalPosition(Vector2f(-200,400));

	PauseDialog::instance()->init();


	_grass=Sprite::alloc("grass.png")->retain<Sprite>();
	_background->addChild(_grass);
	_grass->setLocalPosition(Vector2f(0,360));

	_grass->registerUpdate(this,updateSelector(GameMain::onGrassUpdate));

	_enemy=Enemy::alloc()->retain<Enemy>();
	_background->addChild(_enemy);
	_enemy->reset();
}
void GameMain::onGrassUpdate(){
	float percent=(_enemy->localPosition().x+210)/470;
	_grass->setPart(Rect(0,0,percent,1));
	if(percent<0){
		GameOverDialog::instance()->show(false);
		_grass->setUpdatable(false);
	}
	
}
void GameMain::resume(){
	_background->setTouchIntercept(false);
	_background->setUpdateIntercept(false);
}
bool GameMain::onPauseDown(const TCTouchEvent& evt){
	_background->setTouchIntercept(true);
	_background->setUpdateIntercept(true);
	PauseDialog::instance()->show();
	return true;
}
void GameMain::show(int lv){
	loadTo(lv);
	Camera* ca= TCSceneManager::instance()->findCamera("main");
	ca->rootNode()->addChild(_background);
}

void GameMain::hide(){
	_background->removeSelf();
}

void GameMain::reset(){
	FruitMap::instance()->resetMap();
	_enemy->reset();
	_grass->setPart(Rect(0,0,1,1));
	_grass->setUpdatable(true);
}

void GameMain::loadTo(int lv){
	std::stringstream sstrm;
	sstrm << lv;
	FruitMap::instance()->loadMap(MapDataManager::instance()->find("level_"+ sstrm.str()+".txt"));
	_enemy->reset();
	_grass->setPart(Rect(0,0,1,1));
	_grass->setUpdatable(true);
	GameData::currentLevel=lv;
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
	if(_pauseBtn){
		_pauseBtn->release();
		_pauseBtn=0;
	}
}

GameMain* GameMain::instance(){
	static GameMain _ret;
	return &_ret;
}