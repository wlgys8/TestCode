#include "ui/GameOverDialog.h"
#include "Camera/TCCamera.h"
#include "TCSceneManager.h"
#include "TCAnimation.h"
#include "TCTouchComponent.h"
#include "Map/FruitMap.h"
#include "ui/LevelMenu.h"
#include "GameMain.h"
#include "ui/AnimationData.h"
#include "data/GameData.h"

GameOverDialog::GameOverDialog(){
	_background=Sprite::alloc("gameover_win.png");
	_background->retain();
	AnimationCurve curv=AnimationData::dialogShow*Vector2f(0.4f,1);
	ScaleAnimation* anim=ScaleAnimation::alloc(curv,curv,0.4f);
	_background->animation()->bind(anim);
	_background->setLocalScale(Vector2f(0.1f,0.1f));

	_blackMask=RectangleRGBA::alloc();
	_blackMask->setSize(Vector2f(1000,1000));
	_blackMask->drawer()->paint().setColor(Color(0,0,0,0.5f));
	_blackMask->retain();

	_blackMask->addChild(_background);

	_restart=Sprite::alloc("gameover_replay.png");
	_restart->retain();
	_background->addChild(_restart);
	_restart->setLocalPosition(Vector2f(0,-80));

	TCTouchComponent* tc=_restart->ensureTouchObject();
	_restart->addComponent(tc);
	tc->bindDelegateTarget(this);
	tc->registerDownEvent(touchSelector(GameOverDialog::onRestartClick));

	_menu=Sprite::alloc("gameover_back.png");
	_menu->retain();
	_background->addChild(_menu);
	_menu->setLocalPosition(Vector2f(-80,-80));

	tc=_menu->ensureTouchObject();
	tc->bindDelegateTarget(this);
	tc->registerDownEvent(touchSelector(GameOverDialog::onMenuClick));

	_next=Sprite::alloc("gameover_next.png")->retain<Sprite>();
	_background->addChild(_next);
	_next->setLocalPosition(Vector2f(80,-80));

	tc=_next->ensureTouchObject();
	tc->bindDelegateTarget(this);
	tc->registerDownEvent(touchSelector(GameOverDialog::onNextClick));

	_blackMask->ensureTouchObject()->bindDelegateTarget(this);
	_blackMask->ensureTouchObject()->registerDownEvent(touchSelector(GameOverDialog::onMaskDown));
}

bool GameOverDialog::onMaskDown(const TCTouchEvent& evt){
	return true;
}

bool GameOverDialog::onRestartClick(const TCTouchEvent& evt){
	GameMain::instance()->reset();
	hide();
	return true;
}
bool GameOverDialog::onMenuClick(const TCTouchEvent& evt){
	hide();
	GameMain::instance()->hide();
	LevelMenu::instance()->show();

	return true;
}
bool GameOverDialog::onNextClick(const TCTouchEvent& evt){
	hide();
	GameMain::instance()->resume();
	GameMain::instance()->loadTo(GameData::currentLevel+1);
	return true;
}
GameOverDialog::~GameOverDialog(){
	if(_background){
		_background->release();
		_background=0;
	}
	if(_blackMask){
		_blackMask->release();
		_blackMask=0;
	}
	if(_restart){
		_restart->release();
		_restart=0;
	}

}

void GameOverDialog::show(bool win){
	if(win){
		_background->setImage("gameover_win.png");
	}else{
		_background->setImage("gameover_lose.png");
	}
	Camera* ca= TCSceneManager::instance()->findCamera("main");
	ca->rootNode()->addChild(_blackMask);
	_background->animation()->play();
	_next->setActive(win);
}

void GameOverDialog::hide(){
	_blackMask->removeSelf();
}



GameOverDialog* GameOverDialog::instance(){
	static GameOverDialog _instance;
	return &_instance;
}