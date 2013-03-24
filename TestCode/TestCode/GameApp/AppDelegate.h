#ifndef __TC_APPDELEGATE_H__
#define __TC_APPDELEGATE_H__

#include "TCCommon.h"
#include "AutoReleaseObject.h"
NS_TC_BEGIN

class AppDelegate:public AutoReleaseObject{
#if TC_TARGET_PLATFORM==TC_PLATFORM_WIN32
	friend class TCApplication_win32;
#elif TC_TARGET_PLATFORM==TC_PLATFORM_ANDROID
	friend class TCApplication_android;
#endif

protected:
	void virtual onCreateGame()=0;
	void virtual onPause()=0;
	void virtual onResume()=0;
	void virtual onDestroyGame()=0;

};
NS_TC_END
#endif