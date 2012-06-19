#include "window.h"
#include "screen.h"
#include "core.h"

Screen *Core::screen = 0;
bool Core::stop = false;
HDC Core::hdc = 0;
bool Core::keys[256] = {0};

Core::Core()
{
	screen = new Screen();
	timer = new Timer();
	window = new Window(WndProc);

	memset(keys, 0, 256);

	stop = false;

	delta_time = 0;

	ShowCursor(false);
}

Core::~Core()
{
	delete screen;
	delete timer;
	delete window;

	ShowCursor(true);
}


bool Core::Create()
{
	delta_time = timer->Update();

	window->Create(L"Soft Render v 0.001", 1024, 768);
	
	hdc = GetDC(window->GetHwnd());
	screen->Create(1024, 768, hdc);

	ShowWindow(window->GetHwnd(), SW_SHOW);
	UpdateWindow(window->GetHwnd());
	
	return true;
}

bool Core::Delete()
{
	screen->Delete();
	ReleaseDC(window->GetHwnd(), hdc);
	window->Delete();

	return true;
}

void Core::EatMsg()
{
	MSG msg;

	while(PeekMessage(&msg, window->GetHwnd(), 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void Core::ShowFPS()
{
	static double time = 0;
	static int fps = 0;
	static wchar_t fps_text[32];
	
	time += delta_time;
	fps += 1;

	if(time > 1)
	{
		wsprintf(fps_text, L"Soft Render v 0.001 FPS = %d", fps);
		SetWindowText(window->GetHwnd(), fps_text);
		fps = 0;
		time = 0;
	}
}

bool Core::Stop()
{
	EatMsg();

	ShowFPS();

	screen->Show(hdc);

	delta_time = timer->Update();
	 
	return stop;
}

Screen *Core::GetScreen()
{
	return screen;
}

LRESULT WINAPI Core::WndProc(HWND _hwnd, UINT _message, WPARAM _wparam, LPARAM _lparam)
{
	switch(_message)
	{
	case WM_QUIT:
	case WM_CLOSE:
		stop = true;
		break;

	case WM_SIZE:
		screen->Resize(LOWORD(_lparam), HIWORD(_lparam), hdc);
		break;

	case WM_KEYDOWN:
		keys[_wparam] = true;
		break;

	case WM_KEYUP:                       
		keys[_wparam] = false;
		break;
	}

	return DefWindowProc(_hwnd, _message, _wparam, _lparam);
}