#include "TCEGLView.h"
#include "TCScreen.h"
NS_TC_BEGIN
const WCHAR * kWindowClassName = L"TestCodeWin32";
TCEGLView::TCEGLView():hDC(NULL),hRC(NULL),hWnd(NULL),hInstance(NULL),_isCreated(false),
_isResized(false),_width(0),_height(0){

}

bool TCEGLView::initEGLContext(){
	EGLint	majorVersion, minorVersion;

	mEglContext = 0;

	hDC = GetDC( hWnd );
	mEglDisplay = eglGetDisplay( hDC );

	if( mEglDisplay == EGL_NO_DISPLAY )
		mEglDisplay = eglGetDisplay((EGLNativeDisplayType)EGL_DEFAULT_DISPLAY);

	if(!eglInitialize(mEglDisplay, &majorVersion, &minorVersion)){
		return false;
	}

	if(!eglBindAPI(EGL_OPENGL_ES_API)){
		return false;
	}

	mEglConfig = setEGLConfiguration();

	EGLint ai32ContextAttribs[32];
	int	i = 0;

	ai32ContextAttribs[i] = EGL_NONE;

	mEglContext = eglCreateContext(mEglDisplay, mEglConfig, NULL, NULL);

	if( mEglContext == EGL_NO_CONTEXT ){
		return false;
	}

	EGLint		attrib_list[16];
	i = 0;
	attrib_list[i] = EGL_NONE;

	mEglSurface = eglCreateWindowSurface(mEglDisplay, mEglConfig, hWnd, NULL);

	if( mEglSurface == EGL_NO_SURFACE){
		DebugLog( "Failed to create window surface." );
		return false;
	}

	if ( eglMakeCurrent(mEglDisplay, mEglSurface, mEglSurface, mEglContext) == EGL_TRUE )
		return eglSwapInterval(mEglDisplay, 1) == EGL_TRUE;
	else{
		DebugLog( "Failed to make current context." );
		return false;
	}
}

EGLConfig TCEGLView::setEGLConfiguration()
{
    EGLint		num_config;
	EGLConfig	conf;

	// Setup the configuration list for our surface.
    EGLint conflist[] =
	{
		EGL_LEVEL, 0,
		EGL_NATIVE_RENDERABLE, EGL_FALSE,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES_BIT,
		EGL_CONFIG_CAVEAT, EGL_NONE,
		/*
			Tell it the minimum size we want for our colour buffer and the depth size so
			eglChooseConfig will choose the config that is the closest match.
		*/
		EGL_BUFFER_SIZE, 32,
		EGL_DEPTH_SIZE, 16,
		// The PBuffer bit is the important part as it shows we want a PBuffer
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT | EGL_PBUFFER_BIT,
		EGL_BIND_TO_TEXTURE_RGBA, EGL_TRUE,
		EGL_SAMPLE_BUFFERS, 0,
		EGL_NONE
	};

	// Return null config if config is not found
    if(!eglChooseConfig(mEglDisplay, conflist, &conf, 1, &num_config) || num_config != 1){
		DebugLog("Unable to choose a valid config.." );
		return 0;
    }

	// Return config index
	return conf;
}

static LRESULT CALLBACK  _WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	static bool touch = false;
	switch(uMsg){
	case WM_CLOSE:
		testCode::DebugLog("close%d",1);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

bool TCEGLView::createWindow(long width, long height){
	WNDCLASS	wc;		
	DWORD		dwExStyle;
	DWORD		dwStyle;

	RECT WindowRect;
	WindowRect.left = 0l;
	WindowRect.top = 0l;

	WindowRect.right = width;
	WindowRect.bottom= height;
	_width=width;
	_height=height;
	HINSTANCE hInstance		= GetModuleHandle(NULL);			// Grab An Instance For Our Window

	wc.style		= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		// Redraw On Move, And Own DC For Window
	wc.lpfnWndProc	= (WNDPROC) _WndProc;				// WndProc Handles Messages
	wc.cbClsExtra	= 0;								// No Extra Window Data
	wc.cbWndExtra	= 0;								// No Extra Window Data
	wc.hInstance	= hInstance;						// Set The Instance
	wc.hIcon		= LoadIcon(NULL, IDI_WINLOGO);		// Load The Default Icon
	wc.hCursor		= LoadCursor(NULL, IDC_ARROW);		// Load The Arrow Pointer
	wc.hbrBackground	= NULL;							// No Background Required For GL
	wc.lpszMenuName		= NULL;							// We Don't Want A Menu
	wc.lpszClassName	= kWindowClassName;				// Set The Class Name


	if (!RegisterClass(&wc)){
		DebugLog("Can't register window class");
		return false;
	}

	dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
	dwStyle = WS_OVERLAPPEDWINDOW|WS_VISIBLE;				// Windows Style

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	if (
		!(hWnd = CreateWindowEx(	dwExStyle,				// Extended Style For The Window
		kWindowClassName,				// Class Name
		L"iPhone Simulator",		// Window Title
		WS_CLIPSIBLINGS |			// Required Window Style
		WS_CLIPCHILDREN |			// Required Window Style
		dwStyle						// Selected Window Style
		& ~(WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME),	// no resize bar
		0, 0,						// Window Position
		WindowRect.right - WindowRect.left-10,	// Calculate Adjusted Window Width
		WindowRect.bottom- WindowRect.top-10,	// Calculate Adjusted Window Height
		NULL,						// No Parent Window
		NULL,						// No Menu
		hInstance,					// Instance
		NULL) )						// Pass self-pointer To WM_CREATE
		)
	{
		DebugLog("Can't create window");
		return false;
	}
	return true;
}

void TCEGLView::create(float width,float height){
	if(!_isCreated){
		createWindow(width,height);
		Screen::resize(width,height);
		initEGLContext();
		_isCreated=true;
		resize(width,height);
		return;
	}
	DebugLog("view has been created!!");
	
}

void TCEGLView::resize(float width,float height){
	if(!_isResized){
		
		TCRender::instance()->onResize(_width,_height);
		_isResized=true;
	}
}
void TCEGLView::loop(){

	TCRender::instance()->onRender();
	if( !eglSwapBuffers(mEglDisplay, mEglDisplay) ){
		if(eglGetError() == EGL_CONTEXT_LOST){
			DebugLog("Lost context!");
		}
		DebugLog("Unable to swap buffer");
	}
}


void TCEGLView::showGameWindow(){
	ShowWindow(hWnd,SW_SHOW);
}


TCEGLView::~TCEGLView(){
	if (EGL_NO_SURFACE != mEglSurface)
	{
		eglDestroySurface(mEglDisplay, mEglSurface);
	}
	if (EGL_NO_CONTEXT != mEglContext)
	{
		eglDestroyContext(mEglDisplay, mEglContext);
	}
	eglMakeCurrent(mEglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglTerminate(mEglDisplay);
	if (hDC)
	{
		ReleaseDC(hWnd, hDC);
	}
	DestroyWindow(hWnd);
	hWnd=NULL;
	UnregisterClass(kWindowClassName, GetModuleHandle(NULL));
	DebugLog("destroy eglView");
}

NS_TC_END