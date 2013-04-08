#include "ui/PauseDialog.h"
#include "TCSceneManager.h"
#include "Camera/TCCamera.h"
#include "ui/AnimationData.h"
#include "TCAnimation.h"
#include "TCTouchComponent.h"
#include "GameMain.h"
#include "ui/LevelMenu.h"
#include "Map/FruitMap.h"

PauseDialog::PauseDialog():
_bg(0),
_menuBtn(0),
_replayBtn(0),
_resumtBtn(0)
{


}

void PauseDialog::init(){
	if(_bg){
		return;
	}
	_bg=Sprite::alloc("pause_dialog.png")->retain<Sprite>();
	_menuBtn=Sprite::alloc("pause_memu.png")->retain<Sprite>();
	_replayBtn=Sprite::alloc("pause_replay.png")->retain<Sprite>();
	_resumtBtn=Sprite::alloc("pause_play.png")->retain<Sprite>();

	_bg->addChild(_resumtBtn);
	_resumtBtn->setLocalPosition(Vector2f(80,-60));

	_bg->addChild(_menuBtn);
	_menuBtn->setLocalPosition(Vector2f(-80,-60));

	_bg->addChild(_replayBtn);
	_replayBtn->setLocalPosition(Vector2f(0,-60));

	AnimationCurve curv=AnimationData::dialogShow*Vector2f(0.4f,1);
	ScaleAnimation* anim=ScaleAnimation::alloc(curv,curv,0.4f);
	_bg->animation()->bind(anim);

	TCTouchComponent* tc= _resumtBtn->ensureTouchObject();
	tc->bindDelegateTarget(this);
	tc->registerDownEvent(touchSelector(PauseDialog::onResumeDown));
	tc->registerUpEvent(touchSelector(PauseDialog::onResumeUp));
	tc->registerClickEvent(touchSelector(PauseDialog::onResumeClick));

	tc=_replayBtn->ensureTouchObject();
	tc->bindDelegateTarget(this);
	tc->registerDownEvent(touchSelector(PauseDialog::onReplayDown));
	tc->registerUpEvent(touchSelector(PauseDialog::onReplayUp));
	tc->registerClickEvent(touchSelector(PauseDialog::onReplayClick));

	tc=_menuBtn->ensureTouchObject();
	tc->bindDelegateTarget(this);
	tc->registerDownEvent(touchSelector(PauseDialog::onMenuDown));
	tc->registerUpEvent(touchSelector(PauseDialog::onMenuUp));
	tc->registerClickEvent(touchSelector(PauseDialog::onMenuClick));
}

bool PauseDialog::onResumeDown(const TCTouchEvent& evt){
	_resumtBtn->setLocalScale(Vector2f(1.2f,1.2f));
	return true;
}
bool PauseDialog::onResumeUp(const TCTouchEvent& evt){
	_resumtBtn->setLocalScale(Vector2f(1.0f,1.0f));
	
	return true;
}
bool PauseDialog::onResumeClick(const TCTouchEvent& evt){
	GameMain::instance()->resume();
	hide();
	return true;
}

bool PauseDialog::onMenuDown(const TCTouchEvent& evt){
	_menuBtn->setLocalScale(Vector2f(1.2f,1.2f));
	return true;
}

bool PauseDialog::onMenuUp(const TCTouchEvent& evt){
	_menuBtn->setLocalScale(Vector2f(1.0f,1.0f));
	return true;
}
bool PauseDialog::onMenuClick(const TCTouchEvent& evt){
	hide();
	GameMain::instance()->resume();
	GameMain::instance()->hide();
	LevelMenu::instance()->show();
	return true;
}

bool PauseDialog::onReplayDown(const TCTouchEvent& evt){
	_replayBtn->setLocalScale(Vector2f(1.2f,1.2f));
	return true;
}
bool PauseDialog::onReplayUp(const TCTouchEvent& evt){
	_replayBtn->setLocalScale(Vector2f(1.0f,1.0f));
	return true;
}
bool PauseDialog::onReplayClick(const TCTouchEvent& evt){
	hide();
	GameMain::instance()->resume();
	FruitMap::instance()->resetMap();
	return true;
}
void PauseDialog::show(){
	TCSceneManager::instance()->findCamera("main")->rootNode()->addChild(_bg);
	_bg->animation()->play();
}
void PauseDialog::hide(){
	_bg->removeSelf();
}
PauseDialog::~PauseDialog(){
	TC_RELEASE(_bg);
	TC_RELEASE(_menuBtn);
	TC_RELEASE(_replayBtn);
	TC_RELEASE(_resumtBtn);
}
PauseDialog* PauseDialog::instance(){
	static PauseDialog dialog;
	return &dialog;
}