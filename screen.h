#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <Windows.h>
#include "color.h"
#include "point.h"

class Screen
{
private:
	Color *data;
	size_t size;

	size_t width;
	size_t height;
	size_t real_width;

	HBITMAP bitmap;
	HBITMAP old_bitmap;
	BITMAPINFO bitmap_info;
	HDC bitmap_hdc;

public:
	Screen();

	~Screen();

	bool Create(size_t _width, size_t _height, HDC _hdc);
	bool Resize(size_t _width, size_t _height, HDC _hdc);
	bool Delete();

	void SetPixel(Point &_point, Color &_color);

	Color *GetPixelLine(size_t _line);

	void Clear(Color &_color);

	size_t GetWidth();
	size_t GetHeight();
	
	void Show(HDC hdc);
};

#endif