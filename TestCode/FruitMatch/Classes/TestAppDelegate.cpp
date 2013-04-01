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
	BaseNode* lateUpdateNode=BaseNode::alloc();
	lateUpdateNode->registerUpdate(this,updateSelector(TestAppDelegate::lateUpdate));
	ca->rootNode()->addChild(lateUpdateNode);
	ca->setOrthof(480,800);
}
void TestAppDelegate::lateUpdate(){
	BulletFactory::BulletList btlist=BulletFactory::instance()->bulletList();
	BulletFactory::BulletList::iterator it;
	for(it=btlist.begin();it!=btlist.end();it++){
		if(EnemyManager::instance()->checkWithBullet(*it)){
			(*it)->removeSelf();
			break;
		}
	}
	BulletFactory::instance()->recollectUnusedBullet();
}
void TestAppDelegate::onResume(){

}

void TestAppDelegate::onDestroyGame(){


}

void TestAppDelegate::onPause(){

}