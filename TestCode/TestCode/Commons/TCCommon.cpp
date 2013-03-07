#include "TCCommon.h"

#define MAX_LEN (testCode::kMaxLogLen)

#if(TC_TARGET_PLATFORM == TC_PLATFORM_WIN32)
#include <Windows.h>
#include <stdio.h>
NS_TC_BEGIN
	void DebugLog(const char * message, ...){
		char szBuf[MAX_LEN];

		va_list ap;
		va_start(ap, message);
		vsnprintf_s(szBuf, MAX_LEN, MAX_LEN, message, ap);
		va_end(ap);

		WCHAR wszBuf[MAX_LEN] = {0};
		MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, wszBuf, sizeof(wszBuf));
		OutputDebugString(wszBuf);
		OutputDebugStringA("\n");
	}
NS_TC_END

#endif


#if (TC_TARGET_PLATFORM == TC_PLATFORM_ANDROID)

#include <android/log.h>
#include <stdio.h>
#include <jni.h>


NS_TC_BEGIN;

void DebugLog(const char * message, ...)
{
	char buf[MAX_LEN];

	va_list args;
	va_start(args, message);    	
	vsprintf(buf, message, args);
	va_end(args);

	__android_log_print(ANDROID_LOG_DEBUG, "testcode_debug",  buf);
}
NS_TC_END
#endif


