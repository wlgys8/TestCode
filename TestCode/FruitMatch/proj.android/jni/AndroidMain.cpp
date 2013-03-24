#include "AndroidMain.h"
#include "Audio/AudioManager.h"
#include "TCMacros.h"
#include "JNIHelper.h"
#include <typeinfo>
#include "Android/TCAndroidObject.h"
#include <string>
#include "TCRender.h"
#include "TCApplication_android.h"
#include "TestAppDelegate.h"
#if TC_TARGET_PLATFORM==TC_PLATFORM_ANDROID

USING_NS_TC;

JNIEXPORT
	jint
	JNICALL																	  
	Java_com_testcode_fruitmatch_FruitMatchActivity_play( JNIEnv* env,
	jobject thiz ){
		AudioManager::instance()->load("/sdcard/helloworld.wav");
		AudioManager::instance()->play("/sdcard/helloworld.wav");
		test();
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

JNIEXPORT
	void
	JNICALL																	  
	Java_com_testcode_library_TCRender_nativeRender( JNIEnv* env,
	jobject thiz){
		TCRender::instance()->onRender();
}
extern "C"{
	void test(){
		int ret=JNIHelper::callStaticMethod<int,int,float,bool,double>("com/testcode/fruitmatch/FruitMatchActivity","test","I",1,1,true,2);
		DebugLog("from java:%d",ret);
	}
	jint JNI_OnLoad(JavaVM *vm, void *reserved){
		std::string str;
		JNIHelper::setJavaVM(vm);
		return JNI_VERSION_1_4;
	}
}
#endif





