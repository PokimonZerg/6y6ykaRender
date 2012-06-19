#ifndef _CORE_H_
#define _CORE_H_

#include <Windows.h>
#include <gdiplus.h>
#include "timer.h"
#include "screen.h"
#include "window.h"

class Core
{
public:
	Core();

	~Core();

	bool Create();
	bool Delete();

	bool Stop();

	Screen *GetScreen();

	double GetTime();

	bool GetKeyState(unsigned char _key);
	Point GetMousePos();
	void  SetMousePos();
	Point GetScreenCenter();

	void StopMe();

private:
	Window *window;
	Timer *timer;
	static Screen *screen;

	Gdiplus::GdiplusStartupInput gdiplusStartupInput; 
	ULONG_PTR gdiplusToken; 
	
	static HDC hdc;

	double delta_time;

	static bool stop;

	static bool keys[256];
	Point mouse_pos;

	static LRESULT WINAPI WndProc(HWND _hwnd, UINT _message, WPARAM _wparam, LPARAM _lparam);

	void EatMsg();

	void ShowFPS();
};

inline double Core::GetTime()
{
	return delta_time;
}

inline bool Core::GetKeyState(unsigned char _key)
{
	return keys[_key];
}

inline Point Core::GetMousePos()
{
	POINT p;
	GetCursorPos(&p);

	mouse_pos.x = p.x;
	mouse_pos.y = p.y;

	return mouse_pos;
}

inline void Core::SetMousePos()
{
	SetCursorPos(screen->GetWidth() / 2, screen->GetHeight() / 2);
}

inline void Core::StopMe()
{
	stop = true;
}

inline Point Core::GetScreenCenter()
{
	return Point(screen->GetWidth() / 2, screen->GetHeight() / 2);
}

#endif