#include "ui/LevelEntryButton.h"
#include "TCTouchComponent.h"
#include "ui/LevelMenu.h"
#include "GameMain.h"
#include "Data/GameData.h"
#include "TestAppDelegate.h"
#include <sstream>
LevelEntryButton::LevelEntryButton(){
	_level=-1;
}

void LevelEntryButton::init(){
	Sprite::initWithImageName("level_item.png");
	_lock=Sprite::alloc("level_lock.png")->retain<Sprite>();;
	addChild(_lock);
	TCTouchComponent* tc=TCTouchComponent::alloc();
	tc->bindDelegateTarget(this);
	tc->registerDownEvent(touchSelector(LevelEntryButton::onDown));
	addComponent(tc);

	_levelNum=TextSprite::alloc()->retain<TextSprite>();
	_levelNum->setFont(TestAppDelegate::customFont);
	_levelNum->setAlgin(AlginMiddle);
	addChild(_levelNum);
}

void LevelEntryButton::updateUI(int level){
	_level=level-1;
	std::stringstream sstrm;
	sstrm << level;
	_levelNum->setText( sstrm.str());
	if(_level>GameData::unlockedLevel){
		_levelNum->removeSelf();
		addChild(_lock);
		ensureTouchObject()->setTouchable(false);
	}else{
		_lock->removeSelf();
		addChild(_levelNum);
		ensureTouchObject()->setTouchable(true);
	}
	//DebugLog("%s","12"+level);
}

bool LevelEntryButton::onDown(const TCTouchEvent& evt){
	LevelMenu::instance()->hide();
	GameMain::instance()->show(_level);
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