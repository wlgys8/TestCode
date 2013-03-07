#ifndef __TC_EGLVIEW_H__
#define __TC_EGLVIEW_H__


#include "EGL/egl.h"
#include "EGL/eglplatform.h"
#include <Windows.h>
#include "TCCommon.h"
#include "TCRender.h"


NS_TC_BEGIN
	class TCEGLView{

	private:
		//windows
		HGLRC hRC;
		HDC hDC;
		HWND hWnd;
		HINSTANCE hInstance;

		//egl
		EGLContext mEglContext;
		EGLDisplay mEglDisplay;
		EGLConfig mEglConfig;
		EGLSurface mEglSurface;

		bool createWindow(long width,long height);
		bool initEGLContext();
		EGLConfig setEGLConfiguration();

		bool _isCreated;
		bool _isResized;
		int _width;
		int _height;
	public:
		TCEGLView();
		~TCEGLView();
		void showGameWindow();

		void resize(float width,float height);
		void create(float width,float height);
		void loop();
	};	
NS_TC_END

#endif