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
std::string AndroidSystemInfo::_cacheDir;
std::string AndroidSystemInfo::_fileDir;

static std::string callGetString_(const std::string& methodName){
	jstring str=JNIHelper::callStaticMethod<jstring>("com/testcode/library/SystemInfo",methodName.c_str(),"Ljava/lang/String;");
	const char* ret=JNIHelper::getEnv()->GetStringUTFChars(str,0);
	std::string rets=std::string(ret);
	JNIHelper::getEnv()->ReleaseStringUTFChars(str,ret);
	return rets;
}
void AndroidSystemInfo::init(){
	_sourceDir=callGetString_("getSourceDir");
	_cacheDir=callGetString_("getCacheDir");
	_fileDir=callGetString_("getFileDir");
	DebugLog("[AndroidSystemInfo]sourceDir=%s",_sourceDir.c_str());
	DebugLog("[AndroidSystemInfo]cacheDir=%s",_cacheDir.c_str());
	DebugLog("[AndroidSystemInfo]fileDir=%s",_fileDir.c_str());
}

NS_TC_END

#endif //!__ANDROID__