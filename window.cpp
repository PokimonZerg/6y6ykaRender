#include "window.h"

Window::Window(WNDPROC _wndproc)
{
	hwnd = 0;
	hInst = GetModuleHandle(0);
	wndproc = _wndproc;
}

Window::~Window()
{
	Delete();
}

HWND Window::GetHwnd()
{
	return hwnd;
}

bool Window::Create(wchar_t *_title, size_t _width, size_t _height)
{
	if(hwnd)
		Delete();
	
	w.cbClsExtra = 0;
	w.cbWndExtra = 0;
	w.hbrBackground = (HBRUSH)COLOR_GRAYTEXT;
	w.hCursor       = LoadCursor(0, IDC_ARROW);
	w.hIcon         = LoadIcon(0, IDI_WARNING);
	w.hInstance     = hInst;
	w.lpfnWndProc   = wndproc;
	w.lpszClassName = L"Soft Render";
	w.lpszMenuName  = 0;
	w.style         = CS_HREDRAW | CS_VREDRAW;

	if(!RegisterClass(&w))
	{
		return false;
	}

	hwnd = CreateWindow(L"Soft Render", _title, WS_OVERLAPPEDWINDOW,
						100, 100, _width, _height, 0, 0, hInst, 0);
	if(!hwnd)
	{
		UnregisterClass(L"Soft Render", hInst);

		return false;
	}


	return true;
}

bool Window::Delete()
{
	if(!hwnd)
		return true;

	UnregisterClass(L"Soft Render", hInst);
	DestroyWindow(hwnd);

	return true;
}