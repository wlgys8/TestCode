#ifndef __TC_COMMON_H__
#define __TC_COMMON_H__

#include "TCPlatform.h"
#include <assert.h>
NS_TC_BEGIN
#if (TC_SCREEN_ORIENTION==TC_SCREEN_ORIENTION_PORTRAIT)
	static const int SCREEN_WIDTH=480;
	static const int SCREEN_HEIGHT=854;
#else
	static const int SCREEN_WIDTH=854;
	static const int SCREEN_HEIGHT=480;
#endif
	static const int kMaxLogLen=(16*1024+1);
	void DebugLog(const char * message, ...);
	 
NS_TC_END
#endif