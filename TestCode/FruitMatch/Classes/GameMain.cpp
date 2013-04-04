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
#include "TCRectangleRGBA.h"
void GameMain::initGame(){
	TCResources::loadAudioInAssets("helloworld.wav");
	Sprite* bg=Sprite::alloc("bg.png");
	bg->addChild(FruitMap::instance()->node());

	ConnectionEffect::instance()->setSpaceNode(bg);

	Camera* ca= TCSceneManager::instance()->findCamera("main");
	ca->rootNode()->addChild(bg);


}

GameMain::~GameMain(){
	
}