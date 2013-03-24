#ifndef __TC_SCREEN_H__
#define __TC_SCREEN_H__
#include "TCCommon.h"
#if TC_TARGET_PLATFORM==TC_PLATFORM_WIN32
	#include "TCEGLView.h"
#endif	
NS_TC_BEGIN

enum ScreenOritation{
	Portrait,
	LandScape,
};
class Screen{
#if TC_TARGET_PLATFORM==TC_PLATFORM_WIN32
friend class TCEGLView;
#endif

public:
	static void resize(int width,int height){
		_width=width;
		_height=height;
	}

private:
	static int _width;
	static int _height;
public:
	static int width(){
		return _width;
	}	
	static int height(){
		return _height;
	}
};

NS_TC_END
#endif