#include "AppDelegate.h"
#include "TCResources.h"
#include "TCSceneManager.h"
#include "TCSprite.h"
#include "TestAppDelegate.h"
#include "TCTouchComponent.h"
#include "TCDrawer.h"
#include "AutoReleaseObject.h"
#include "TCTextureRegionManager.h"
#include "Map/FruitMap.h"
#include "Role/Role.h"
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
	DebugLog("onCreatehhhh");
	TCResources::loadTextureRegions("fruit.png","fruit.txt",RGBA_8888);
	Sprite* node=Sprite::alloc("bg.png");
	node->addChild(FruitMap::instance()->node());

	Role* role=Role::alloc(Role_Xigua)->retain<Role>();
	role->sprite()->setLocalPosition(Vector2f(-170,270));
	node->addChild(role->sprite());
	TCSceneManager::instance()->addChild(node);
}

void TestAppDelegate::onResume(){

}

void TestAppDelegate::onDestroyGame(){


}

void TestAppDelegate::onPause(){

}