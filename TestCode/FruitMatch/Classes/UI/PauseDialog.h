#ifndef __PAUSE_DIALOG_H__
#define __PAUSE_DIALOG_H__


#include "TCSprite.h"
#include "TCTouchEvent.h"

USING_NS_TC;

class PauseDialog:public TCObject{

private:
	Sprite* _bg;
	Sprite* _resumtBtn;
	Sprite* _replayBtn;
	Sprite* _menuBtn;

	PauseDialog();
	~PauseDialog();

	bool onResumeDown(const TCTouchEvent& evt);
	bool onResumeUp(const TCTouchEvent& evt);
	bool onResumeClick(const TCTouchEvent& evt);

	bool onMenuDown(const TCTouchEvent& evt);
	bool onMenuUp(const TCTouchEvent& evt);
	bool onMenuClick(const TCTouchEvent& evt);

	bool onReplayDown(const TCTouchEvent& evt);
	bool onReplayUp(const TCTouchEvent& evt);
	bool onReplayClick(const TCTouchEvent& evt);

public:
	void init();

	void show();

	void hide();

	static PauseDialog* instance();

};
#endif