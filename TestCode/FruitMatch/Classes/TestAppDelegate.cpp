#include "AppDelegate.h"
#include "TCSceneManager.h"
#include "TCSprite.h"
#include "TestAppDelegate.h"
#include "TCTouchComponent.h"
#include "AutoReleaseObject.h"
#include "TCResources.h"
#include "GameMain.h"
#include "Fruit/BulletFactory.h"
#include "TCRender.h"
#include "Camera/TCCamera.h"
#include "Debug/TCRenderStatistics.h"
#include "Debug/TCMemoryStatistics.h"
#include "ui/LevelMenu.h"
#include "Map/MapDataManager.h"
#include "ui/AnimationData.h"
#include "data/GameData.h"
USING_NS_TC;

CustomFont* TestAppDelegate::customFont=0;

void TestAppDelegate::onCreateGame(){
	TCResources::loadTextureRegions("fruit.png","fruit.txt",RGBA_8888);
	TCResources::loadTextureRegions("ui_levelMenu.png","ui_levelMenu.txt",RGBA_8888);
	TCResources::loadTextureRegions("ui_pause.png","ui_pause.txt",RGBA_8888);
	TCResources::loadAudioInAssets("match.wav");
	TCResources::loadAudioInAssets("background.wav");
	MapDataManager::instance()->loadAllMapData();
	AnimationData::init();
	GameData::load();
	customFont=CustomFont::alloc();
	customFont->retain();
	customFont->registerPair("0","num_0.png");
	customFont->registerPair("1","num_1.png");
	customFont->registerPair("2","num_2.png");
	customFont->registerPair("3","num_3.png");
	customFont->registerPair("4","num_4.png");
	customFont->registerPair("5","num_5.png");
	customFont->registerPair("6","num_6.png");
	customFont->registerPair("7","num_7.png");
	customFont->registerPair("8","num_8.png");
	customFont->registerPair("9","num_9.png");

	Camera* ca= TCSceneManager::instance()->createCamera();
	ca->setOrthof(480,854);
	GameMain::instance()->init();
	LevelMenu::instance()->init();
	LevelMenu::instance()->show();
	BaseNode* n=BaseNode::alloc();
	n->registerUpdate(this,updateSelector(TestAppDelegate::lateUpdate));
	ca->rootNode()->addChild(n);
}
void TestAppDelegate::lateUpdate(){
//	DebugLog("batched=%d,drawCalls=%d,objectCount=%d,nodeCount=%d",
//		RenderStatistics::batched(),
//		RenderStatistics::drawCalls(),
//		TCObject::count(),
//		BaseNode::count()
//		);
}
void TestAppDelegate::onResume(){

}
void TestAppDelegate::onPause(){

}
void TestAppDelegate::onDestroyGame(){
	GameData::save();
}

