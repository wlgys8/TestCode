#ifndef __TC_APPLICATION_H__
#define __TC_APPLICATION_H__

#include "TCSingleton.h"
#include "AppDelegate.h"
NS_TC_BEGIN
class TCApplication:public TCSingleton<TCApplication>{
	friend class TCSingleton<TCApplication>;
private:
	AppDelegate* _appDelegate;
private:

public:
	void bindAppDelegate( AppDelegate* delegate);
	int run();

};

NS_TC_END
#endif