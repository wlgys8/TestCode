#include "AndroidMain.h"
#include "Audio/AudioManager.h"
#include "TCMacros.h"
using namespace testCode;
JNIEXPORT
	jint
	JNICALL																	  
	Java_com_testcode_fruitmatch_FruitMatchActivity_play( JNIEnv* env,
	jobject thiz ){
	AudioManager::instance()->load("/sdcard/helloworld.wav");
	AudioManager::instance()->play("/sdcard/helloworld.wav");
	return 0;
}





