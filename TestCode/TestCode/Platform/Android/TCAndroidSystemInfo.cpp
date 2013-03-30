#include "TCAndroidSystemInfo.h"
#include "JNIHelper.h"
USING_NS_TC;
#ifdef __ANDROID__

#ifdef __cplusplus
extern "C" {
#endif
	JNIEXPORT
		jint
		JNICALL																	  
		Java_com_testcode_library_SystemInfo_init( JNIEnv* env,
		jclass clazz ){
			AndroidSystemInfo::init();
	}

#ifdef __cplusplus
}
#endif//!_cplusplus

NS_TC_BEGIN
std::string AndroidSystemInfo::_sourceDir;

void AndroidSystemInfo::init(){
	jstring str=JNIHelper::callStaticMethod<jstring>("com/testcode/library/SystemInfo","getSourceDir","Ljava/lang/String;");
	const char* ret=JNIHelper::getEnv()->GetStringUTFChars(str,0);
	_sourceDir=std::string(ret);
	JNIHelper::getEnv()->ReleaseStringUTFChars(str,ret);
	DebugLog("[AndroidSystemInfo]sourceDir=%s",_sourceDir.c_str());

}

NS_TC_END

#endif //!__ANDROID__