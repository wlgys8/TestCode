#include "TCApplication_win32.h"
#include "TCTime.h"
#include "TCTouchEvent.h"
#include "TCSceneManager.h"
#include "TCScreen.h"
NS_TC_BEGIN

TCApplication_win32::TCApplication_win32():_view(NULL){
	DebugLog("New Application");
}

TCApplication_win32::~TCApplication_win32(){
	if(_view!=NULL){
		delete _view;
	}
	if(_delegate!=0){
		_delegate->release();
	}
	DebugLog("destroy application");
}

int TCApplication_win32::run(){
	if(_delegate==0){
		DebugLog("AppDelegate is Null!!");
		return 0;
	}
	MSG msg;
	HACCEL hAccelTable=NULL;

	if(_view==NULL){
		_view=new TCEGLView();
	}
	_view->showGameWindow();
//	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TESTCODE));

	LARGE_INTEGER nFreq;
	LARGE_INTEGER nLast;
	LARGE_INTEGER nNow;

	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nLast);
	bool created=false;
	while(1){
		bool hasMsg= PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

		if (true)
		{

			QueryPerformanceCounter(&nNow);
			if(!created){
				_view->create(480,854);
				
				DebugLog("dddd ");
				_delegate->onCreateGame();
				created=true;
			}
			double deltaTime=((double)nNow.QuadPart - (double)nLast.QuadPart)/(double)nFreq.QuadPart;
			
			if(deltaTime > 0.016){
				Time::set((float)deltaTime);
				nLast.QuadPart = nNow.QuadPart;
				_view->loop();
			}

		//	continue;
		}
		if(hasMsg){
			bool hasTouch=false;
			TouchEventType type;
			switch(msg.message){
			case WM_LBUTTONDOWN:{
				hasTouch=true;
				type=LeftMouseDown;
								}
								break;
			case WM_LBUTTONUP:{
				hasTouch=true;
				type=LeftMouseUp;
							  }
							  break;
			case WM_MOUSEMOVE:{
				hasTouch=true;
				type=Move;
				break;
							  }
			case WM_RBUTTONDOWN:{
				hasTouch=true;
				type=RightMouseDown;
				break;
								}
			case WM_RBUTTONUP:{
				hasTouch=true;
				type=RightMouseUp;
				break;
							  }
			}
			if(hasTouch){
				TCTouchEvent evt=TCTouchEvent();
				float x=(float)LOWORD( msg.lParam);
				float y=(float)HIWORD(msg.lParam);
				evt.set(type,Vector2f(x,Screen::height()-y));
				TCSceneManager::instance()->dispatchTouch(evt);
			}
		}		


		if (WM_QUIT == msg.message)
		{
			// Quit message loop.
			_delegate->onDestroyGame();
			break;
		}
		if (!hAccelTable&&!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}


NS_TC_END