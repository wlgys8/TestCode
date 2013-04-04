#include "AppDelegate.h"
#include "TCSceneManager.h"
#include "TCSprite.h"
#include "TestAppDelegate.h"
#include "TCTouchComponent.h"
#include "AutoReleaseObject.h"
#include "TCResources.h"
#include "GameMain.h"
#include "Fruit/BulletFactory.h"
#include "Enemy/EnemyManager.h"
#include "TCRender.h"
#include "Camera/TCCamera.h"
USING_NS_TC;

void TestAppDelegate::onCreateGame(){
	TCResources::loadTextureRegions("fruit.png","fruit.txt",RGBA_8888);
	Camera* ca= TCSceneManager::instance()->createCamera();
	GameMain::instance()->initGame();
	ca->setOrthof(480,854);

	BaseNode* n=BaseNode::alloc();
	n->registerUpdate(this,updateSelector(TestAppDelegate::lateUpdate));
	ca->rootNode()->addChild(n);
}
void TestAppDelegate::lateUpdate(){
	
}
void TestAppDelegate::onResume(){

}

void TestAppDelegate::onDestroyGame(){


}

void TestAppDelegate::onPause(){

}