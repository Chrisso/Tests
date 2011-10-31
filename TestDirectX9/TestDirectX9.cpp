// TestDirectX9.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "TestDirectX9.h"
#include "DxWindow.h"

CAppModule _Module;

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	Logging::CLoggerFactory::getDefaultInstance()->AddTarget(new Logging::CLogTargetDebugger(Logging::LOG_LEVEL_INFO));
	Logging::CLoggerFactory::getDefaultInstance()->AddTarget(new Logging::CLogTargetMessageBox(Logging::LOG_LEVEL_ERROR));
	
	LOGMSG_DEBUG(_T("Application started.\n"));
	::CoInitialize(NULL);
	_Module.Init(NULL, hInstance);

	CDxWindow win;
	if (!win.CreateEx())
	{
		LOGMSG_ERROR(_T("Failed to create main window!\n"));
		return 1;       // Window creation failed
	}

	win.ShowWindow(nCmdShow);
	win.UpdateWindow();

	// Hauptmeldungsschleife:
	MSG msg;
	bool bDone = false;
	while (!bDone)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) 
				bDone = true;
			TranslateMessage(&msg); 
			DispatchMessage(&msg); 
		}
		else
		{
			win.Render();
		}
	}

	::CoUninitialize();
	LOGMSG_DEBUG(_T("Application finished.\n"));

	return (int)msg.wParam;
}
