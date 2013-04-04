#include "AppDelegate.h"
#include "TCTouchComponent.h"
#include "TCSprite.h"
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
	~TestAppDelegate(){
		DebugLog("release test app delegate");
	}
};