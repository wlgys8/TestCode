#include "ui/GameOverDialog.h"
#include "Camera/TCCamera.h"
#include "TCSceneManager.h"
#include "TCAnimation.h"

GameOverDialog::GameOverDialog(){
	_background=Sprite::alloc("gameover_win.png");
	_background->retain();
	AnimationCurve curvX;
	AnimationCurve curvY;
	curvX.setWrapMode(CurveWrapClamp);
	curvY.setWrapMode(CurveWrapClamp);
	curvX.addKey(0,0.0f);
	curvX.addKey(0.2f,1.2f);
	curvX.addKey(0.3f,0.9f);
	curvX.addKey(0.4f,1);
	curvY.addKey(0,0.0f);
	curvY.addKey(0.2f,1.2f);
	curvY.addKey(0.3f,0.9f);
	curvY.addKey(0.4f,1);
	ScaleAnimation* anim=ScaleAnimation::alloc(curvX,curvY,0.4f);
	_background->animation()->bind(anim);
	_background->setLocalScale(Vector2f(0.1f,0.1f));
}

GameOverDialog::~GameOverDialog(){
	if(_background){
		_background->release();
		_background=0;
	}

}

void GameOverDialog::show(){
	Camera* ca= TCSceneManager::instance()->findCamera("main");
	
	ca->rootNode()->addChild(_background);
	_background->animation()->play();
}

void GameOverDialog::hide(){
	_background->removeSelf();
}



GameOverDialog* GameOverDialog::instance(){
	static GameOverDialog _instance;
	return &_instance;
}