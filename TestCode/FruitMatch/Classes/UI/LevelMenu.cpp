#include "LevelMenu.h"
#include "TCSceneManager.h"
#include "Camera/TCCamera.h"
#include "ui/LevelEntryButton.h"
LevelMenu::LevelMenu(){
	_root=0;
}

void LevelMenu::init(){
	if(_root){
		return;
	}
	_root=Sprite::alloc("level_menu.png");
	_root->retain();

	for(int i=0;i<6;i++){
		for(int j=0;j<4;j++){
			int x=-165+110*j;
			int y=287-i*115;
			LevelEntryButton* btn=LevelEntryButton::alloc();
			_root->addChild(btn);
			btn->updateUI(i*4+j+1);
			btn->setLocalPosition(Vector2f(x,y));
		}
	}
}

void LevelMenu::show(){
	Camera* ca=TCSceneManager::instance()->findCamera("main");
	ca->rootNode()->addChild(_root);
}

void LevelMenu::hide(){
	_root->removeSelf();
}

LevelMenu::~LevelMenu(){
	if(_root){
		_root->release();
		_root=0;
	}
}

LevelMenu* LevelMenu::instance(){
	static LevelMenu _level;
	return &_level;
}