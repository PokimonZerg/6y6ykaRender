#include <algorithm>
#include "goods.h"
#include "screen.h"

Screen::Screen()
{
	data = 0;
	bitmap = 0;
	width = 0;
	height = 0;
}

Screen::~Screen()
{
	Delete();
}

bool Screen::Delete()
{
	data = 0;

	return true;
}

bool Screen::Create(size_t _width, size_t _height, HDC _hdc)
{
	width = _width;
	height = _height;

	real_width = width;

	while(1)
	{
		if((width * 3) % 4)
			width++;
		else
			break;
	}

	size = width * height;

	memset(&bitmap_info, 0, sizeof(bitmap_info));
	bitmap_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmap_info.bmiHeader.biWidth = width;
    bitmap_info.bmiHeader.biHeight = height;
    bitmap_info.bmiHeader.biPlanes = 1;
    bitmap_info.bmiHeader.biBitCount = 32;
    bitmap_info.bmiHeader.biCompression = BI_RGB;

	bitmap_hdc = CreateCompatibleDC(_hdc);
	bitmap = CreateDIBSection(_hdc, &bitmap_info, DIB_RGB_COLORS, (void**)&data, 0, 0);
	old_bitmap = (HBITMAP)SelectObject(bitmap_hdc, bitmap);

	return true;
}
	
bool Screen::Resize(size_t _width, size_t _height, HDC _hdc)
{
	width = _width;
	height = _height;

	SelectObject(bitmap_hdc, old_bitmap);
	DeleteDC(bitmap_hdc);
	DeleteObject(bitmap);

	return Create(width, height, _hdc);
}

void Screen::SetPixel(Point &_point, Color &_color)
{
	data[_point.x + _point.y * width] = _color;
}

Color *Screen::GetPixelLine(size_t _line)
{
	return &data[_line * width];
}

void Screen::Clear(Color &_color)
{
	std::fill(data, data + size, _color);
}

size_t Screen::GetWidth()
{
	return width;
}

size_t Screen::GetHeight()
{
	return height;
}

void Screen::Show(HDC hdc)
{
	BitBlt(hdc, 0, 0, width, height, bitmap_hdc, 0, 0, SRCCOPY);
}