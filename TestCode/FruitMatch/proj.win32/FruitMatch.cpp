#include "stdafx.h"
#include <Windows.h>
#include "TCApplication.h"
#include "TestAppDelegate.h"
USING_NS_TC


	int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	TCApplication::instance()->bindAppDelegate(new TestAppDelegate());
	return TCApplication::instance()->run();
}