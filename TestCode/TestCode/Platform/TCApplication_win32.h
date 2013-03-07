#ifndef __TC_APPLICATION_WIN32_H__
#define __TC_APPLICATION_WIN32_H__

#include "TCEGLView.h"
#include "TCSingleton.h"
#include "AppDelegate.h"
NS_TC_BEGIN
class TCApplication_win32:public TCSingleton<TCApplication_win32>{
	friend class TCSingleton<TCApplication_win32>;
private:
	TCEGLView* _view;
	AppDelegate* _delegate;
	TCApplication_win32();
	~TCApplication_win32();
public:
	void bindAppDelegate(AppDelegate* delegate){
		delegate->retain();
		_delegate=delegate;
	};
	int run();

};
NS_TC_END
#endif