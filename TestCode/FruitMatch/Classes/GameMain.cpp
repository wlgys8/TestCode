#include "GameMain.h"
#include "Map/FruitMap.h"
#include "TCSceneManager.h"
#include "TCAnimation.h"
#include "TCAnimationCurve.h"
#include "Enemy/Enemy.h"
#include "ParticleSystem/TCParticleSystem.h"
#include "Map/ConnectionEffect.h"
void GameMain::initGame(){
	_role=Role::alloc(Role_Xigua)->retain<Role>();
	Sprite* bg=Sprite::alloc("bg.png");
	bg->addChild(FruitMap::instance()->node());
//	bg->drawer()->paint().setColor(Color(1,0,0,1));
	_role=Role::alloc(Role_Xigua)->retain<Role>();
	_role->sprite()->setLocalPosition(Vector2f(-170,270));
	bg->addChild(_role->sprite());
	AnimationCurve curvX=AnimationCurve();
	curvX.addKey(CurveKey(0,-170,0,1));
	curvX.addKey(0.8f,100);
	curvX.addKey(1,50);
	curvX.setWrapMode(CurveWrapPingPong);
	AnimationCurve curvY=AnimationCurve();
	curvY.addKey(0,270);
	curvY.addKey(1,-270);
	curvY.setWrapMode(CurveWrapPingPong);
	_role->sprite()->animation()->play(
		TranslateAnimation::alloc(
		curvX,
		curvY,
		0
			)
		);
	_role->sprite()->scale(Vector2f(1,1));
	_role->sprite()->drawer()->paint().setColor(Color(0,1,0,1));
	Enemy* snake=Enemy::alloc(Enemy_Snake);
	bg->addChild(snake);
	snake->setLocalPosition(Vector2f(170,180));

	ConnectionEffect::instance()->setSpaceNode(bg);
	TCSceneManager::instance()->addChild(bg);

}

GameMain::~GameMain(){
	if(_role){
		_role->release();
	}
}