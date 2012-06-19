#ifndef _COLOR_H_
#define _COLOR_H_

class Color
{
public:
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char a;

	Color();
	Color(unsigned char _r, unsigned char _g, unsigned char _b);
	Color(const Color &_color);

	~Color();
};

inline Color::Color()
{
	r = 255;
	g = 0;
	b = 0;
	a = 255;
}

inline Color::Color(unsigned char _r, unsigned char _g, unsigned char _b)
{
	r = _r;
	g = _g;
	b = _b;
	a = 255;
}

inline Color::Color(const Color &_color)
{
	r = _color.r;
	g = _color.g;
	b = _color.b;
	a = _color.a;
}

inline Color::~Color()
{
	// empty
}

#endif