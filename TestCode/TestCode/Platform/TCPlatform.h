#ifndef __TC_PLATFORM_H__
#define __TC_PLATFORM_H__
#include "TCMacros.h"

#define TC_PLATFORM_UNKNOWN            0
#define TC_PLATFORM_IOS                1
#define TC_PLATFORM_ANDROID            2
#define TC_PLATFORM_WOPHONE            3
#define TC_PLATFORM_WIN32              4
#define TC_PLATFORM_MARMALADE          5
#define TC_PLATFORM_LINUX              6
#define TC_PLATFORM_BADA               7
#define TC_PLATFORM_QNX				   8

#define TC_TARGET_PLATFORM             TC_PLATFORM_UNKNOWN

#if ! TC_TARGET_PLATFORM && defined(ANDROID)
#undef  TC_TARGET_PLATFORM
#define TC_TARGET_PLATFORM         TC_PLATFORM_ANDROID
#endif

#if ! TC_TARGET_PLATFORM && (defined(WIN32) && defined(_WINDOWS))
#undef  TC_TARGET_PLATFORM
#define TC_TARGET_PLATFORM         TC_PLATFORM_WIN32
#endif


#endif