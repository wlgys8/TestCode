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

	bool onDown(const TCTouchEvent& event);

	bool onUp(const TCTouchEvent& event);

	bool onClick(const TCTouchEvent& event);

	void lateUpdate();

	Sprite* pingguo;
public:
	~TestAppDelegate(){
		DebugLog("release test app delegate");
	}
};