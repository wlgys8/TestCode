#include "ui/LevelEntryButton.h"
#include "TCTouchComponent.h"
#include "ui/LevelMenu.h"
#include "GameMain.h"

#include "TestAppDelegate.h"

LevelEntryButton::LevelEntryButton(){
	
}

void LevelEntryButton::init(){
	Sprite::initWithImageName("level_item.png");
//	Sprite* lock=Sprite::alloc("level_lock.png");
//	addChild(lock);
	TCTouchComponent* tc=TCTouchComponent::alloc();
	tc->bindDelegateTarget(this);
	tc->registerDownEvent(touchSelector(LevelEntryButton::onDown));
	addComponent(tc);

	_levelNum=TextSprite::alloc();
	_levelNum->setFont(TestAppDelegate::customFont);
	_levelNum->setAlgin(AlginMiddle);
	addChild(_levelNum);
}

void LevelEntryButton::updateUI(int level){
	_levelNum->setText(std::to_string((long double)level));
	//DebugLog("%s","12"+level);
}

bool LevelEntryButton::onDown(const TCTouchEvent& evt){
	LevelMenu::instance()->hide();
	GameMain::instance()->show();
	return true; 
//	return false;
}
LevelEntryButton::~LevelEntryButton(){

}

LevelEntryButton* LevelEntryButton::alloc(){
	LevelEntryButton* ret=new LevelEntryButton();
	ret->autoRelease();
	ret->init();
	return ret;
}