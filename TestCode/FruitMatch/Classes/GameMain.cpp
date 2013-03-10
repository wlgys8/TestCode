#include "GameMain.h"
#include "Map/FruitMap.h"
#include "TCSceneManager.h"
#include "TCAnimation.h"
#include "Animation/TCAnimationCurve.h"
void GameMain::initGame(){
	_role=Role::alloc(Role_Xigua)->retain<Role>();
	Sprite* bg=Sprite::alloc("bg.png");
	bg->addChild(FruitMap::instance()->node());

	_role=Role::alloc(Role_Xigua)->retain<Role>();
	_role->sprite()->setLocalPosition(Vector2f(-170,270));
	bg->addChild(_role->sprite());

	AnimationCurve curvX=AnimationCurve();
	curvX.addKey(0,-170);
	curvX.addKey(2,170);

	AnimationCurve curvY=AnimationCurve();
	curvY.addKey(0,270);
	curvY.addKey(1,380);
	curvY.addKey(2,270);

	_role->sprite()->animation()->play(
			TranslateAnimation::alloc(
				curvX,
				curvY,
				2
			)
		);
	float ret=HermiteInterpolation3::evaluate(1,280,0,2,270,0,1.5f);
	DebugLog("v:%f",ret);
	TCSceneManager::instance()->addChild(bg);

}

GameMain::~GameMain(){
	if(_role){
		_role->release();
	}
}