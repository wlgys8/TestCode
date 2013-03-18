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
USING_NS_TC;

bool TestAppDelegate::onDown(const TCTouchEvent& event){
	TCDrawer* drawer=(TCDrawer*) pingguo->getComponment(ComponentDrawer);
	drawer->setTextureRegion(TextureRegionManager::instance()->get("juzi.png"));
	return true;
}
bool TestAppDelegate::onUp(const TCTouchEvent& event){
	TCDrawer* drawer=(TCDrawer*) pingguo->getComponment(ComponentDrawer);
	drawer->setTextureRegion(TextureRegionManager::instance()->get("pingguo.png"));
	return  true;
}

bool TestAppDelegate::onClick(const TCTouchEvent& event){
	DebugLog("click");
	return true;
}
void TestAppDelegate::onCreateGame(){
	TCResources::loadTextureRegions("fruit.png","fruit.txt",RGBA_8888);
	GameMain::instance()->initGame();
	BaseNode* lateUpdateNode=BaseNode::alloc();
	lateUpdateNode->registerUpdate(this,updateSelector(TestAppDelegate::lateUpdate));
	TCSceneManager::instance()->addChild(lateUpdateNode);
}
void TestAppDelegate::lateUpdate(){
	BulletFactory::BulletList btlist=BulletFactory::instance()->bulletList();
	BulletFactory::BulletList::iterator it;
//	DebugLog("ref:%d",btlist.size());
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