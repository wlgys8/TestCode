#include "AndroidMain.h"
#include "Audio/AudioManager.h"
#include "TCMacros.h"
#include "JNIHelper.h"
#include <typeinfo>
#include "Android/TCAndroidObject.h"
#include <string>
#include "TCRender.h"
#include "TCSceneManager.h"
#include "TCApplication_android.h"
#include "TestAppDelegate.h"
#include "TCScreen.h"
#include "TCTime.h"
#if TC_TARGET_PLATFORM==TC_PLATFORM_ANDROID

USING_NS_TC;

JNIEXPORT
	jint
	JNICALL																	  
	Java_com_testcode_fruitmatch_FruitMatchActivity_play( JNIEnv* env,
	jobject thiz ){
		return 0;
}

JNIEXPORT
	void
	JNICALL																	  
	Java_com_testcode_library_TCRender_nativeInit( JNIEnv* env,
	jobject thiz,int width,int height ){
		DebugLog("native init,width=%d,height=%d",width,height);
		TCRender::instance()->onResize(width,height);
		AppDelegate* d=new TestAppDelegate();
		TCApplication_android::instance()->bindAppDelegate(d);
		TCApplication_android::instance()->onCreateGame();
}

static TCTouchEvent evt=TCTouchEvent();
static bool touched=false;
JNIEXPORT
	void
	JNICALL																	  
	Java_com_testcode_library_TCRender_nativeRender( JNIEnv* env,
	jobject thiz){
		TCRender::instance()->onRender();
		if(touched){
			TCSceneManager::instance()->dispatchTouch(evt);
			touched=false;
		}
}
JNIEXPORT
	void
	JNICALL																	  
	Java_com_testcode_library_TCRender_nativeUpdateTime( JNIEnv* env,
	jobject thiz,jfloat deltaTime ){
		Time::set(deltaTime);
}
JNIEXPORT
	jboolean
	JNICALL																	  
	Java_com_testcode_library_TCGLSurfaceView_nativeDispatchEvent( JNIEnv* env,
	jobject thiz ,jint action,jfloat x,jfloat y){
		x=x-Screen::width()/2;
		y=y-Screen::height()/2;
		TouchEventType type;
		switch (action)
		{
		case 0:
			type=LeftMouseDown;
			break;
		case 1:
			type=LeftMouseUp;
			break;
		case  2:
			type=Move;
			break;;
		}
		
		evt.set(type,Vector2f(x,-y));
		touched=true;
		

}
extern "C"{
	void test(){
		int ret=JNIHelper::callStaticMethod4<int,int,float,bool,double>("com/testcode/fruitmatch/FruitMatchActivity","test","I",1,1,true,2);
		DebugLog("from java:%d",ret);
	}
	jint JNI_OnLoad(JavaVM *vm, void *reserved){
		std::string str;
		JNIHelper::setJavaVM(vm);
		return JNI_VERSION_1_4;
	}
}
#endif





