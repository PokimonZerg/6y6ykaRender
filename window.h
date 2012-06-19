#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <windows.h>

class Window
{
private:
	Window(const Window &);

	HWND hwnd;
	HINSTANCE hInst;
	WNDCLASS w;
	WNDPROC wndproc;

public:
	Window(WNDPROC _wndproc);
	
	~Window();

	bool Create(wchar_t *_title, size_t _width, size_t _height);

	bool Delete();

	HWND GetHwnd();
};

#endif