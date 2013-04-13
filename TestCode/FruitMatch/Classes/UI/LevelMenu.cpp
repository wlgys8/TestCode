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

//	_buttonList.reserve(6*4);

	for(int i=0;i<6;i++){
		for(int j=0;j<4;j++){
			int x=-165+110*j;
			int y=287-i*115;
			LevelEntryButton* btn=LevelEntryButton::alloc();
			_root->addChild(btn);
			btn->updateUI(i*4+j+1);
			btn->setLocalPosition(Vector2f(x,y));
			_buttonList.push_back(btn);
			btn->retain();
		}
	}
}

void LevelMenu::show(){
	Camera* ca=TCSceneManager::instance()->findCamera("main");
	ca->rootNode()->addChild(_root);
	std::vector<LevelEntryButton*>::iterator it;
	int i=1;
	DebugLog("%d",_buttonList.size());
	for(it=_buttonList.begin();it!=_buttonList.end();it++){
		(*it)->updateUI(i++);
	}
}

void LevelMenu::hide(){
	_root->removeSelf();
}

LevelMenu::~LevelMenu(){
	if(_root){
		_root->release();
		_root=0;
	}
	std::vector<LevelEntryButton*>::iterator it;
	for(it=_buttonList.begin();it!=_buttonList.end();it++){
		(*it)->release();
	}
	_buttonList.clear();
}

LevelMenu* LevelMenu::instance(){
	static LevelMenu _level;
	return &_level;
}