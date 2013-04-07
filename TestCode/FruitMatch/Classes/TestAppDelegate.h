#include "AppDelegate.h"
#include "TCTouchComponent.h"
#include "TCSprite.h"
#include "Font/TCCustomFont.h"
USING_NS_TC
class TestAppDelegate:public AppDelegate{

protected:
	void virtual onCreateGame();

	void virtual onResume();


	void virtual onPause();
	 

	void virtual onDestroyGame();


	void lateUpdate();

	Sprite* pingguo;
public:
	static CustomFont* customFont;
	~TestAppDelegate(){
		if(customFont){
			customFont->release();
			customFont=0;
		}
		DebugLog("release test app delegate");
	}
};