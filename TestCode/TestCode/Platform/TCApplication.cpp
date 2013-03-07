#include "TCApplication.h"

#if TC_TARGET_PLATFORM==TC_PLATFORM_WIN32

#include "TCApplication_win32.h"
NS_TC_BEGIN
void TCApplication::bindAppDelegate( AppDelegate* delegate){
	TCApplication_win32::instance()->bindAppDelegate(delegate);
}

int TCApplication::run(){
	return TCApplication_win32::instance()->run();
}


NS_TC_END


#endif