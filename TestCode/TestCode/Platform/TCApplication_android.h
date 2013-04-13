#ifndef __TC_APPLICATION_ANDROID_H__
#define __TC_APPLICATION_ANDROID_H__

#include "TCCommon.h"

#if TC_TARGET_PLATFORM==TC_PLATFORM_ANDROID
#include <stdlib.h>
#include <string.h>
#include <jni.h>
NS_TC_BEGIN
#ifdef __cplusplus
	extern "C" {
#endif

		JNIEXPORT
			jint
			JNICALL																	  
			Java_com_zilch_testcode_TCRender_nativeInit( JNIEnv* env,
			jobject thiz,int width,int height );
		JNIEXPORT
			jint
			JNICALL																	  
			Java_com_zilch_testcode_TCRender_nativeRender( JNIEnv* env,
			jobject thiz );
		JNIEXPORT
			jint
			JNICALL																	  
			Java_com_zilch_testcode_TestCodeActivity_nativeSetRootPath( JNIEnv* env,
			jobject thiz,jstring path);
#ifdef __cplusplus
}
#endif

NS_TC_END


#include "AppDelegate.h"
#include "TCSingleton.h"
NS_TC_BEGIN
class TCApplication_android:public TCSingleton<TCApplication_android>{
	friend class TCSingleton<TCApplication_android>;
private:
	AppDelegate* _appDelegate;	
private:
	TCApplication_android();
	~TCApplication_android();
public:
	void bindAppDelegate(AppDelegate* delegate){
		delegate->retain();
		_appDelegate=delegate;
	};

	void onCreateGame(){
		_appDelegate->onCreateGame();
	}

	void onDestroy();
};

NS_TC_END

#endif //!PLATFORM==ANDROID
#endif