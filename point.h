#ifndef _POINT_H_
#define _POINT_H_

class Point
{
public:
	int x;
	int y;

	Point();
	Point(int _x, int _y);
	Point(const Point &_point);

	~Point();
};

inline Point::Point()
{
	x = 0;
	y = 0;
}

inline Point::Point(int _x, int _y)
{
	x = _x;
	y = _y;
}

inline Point::Point(const Point &_point)
{
	x = _point.x;
	y = _point.y;
}

inline Point::~Point()
{
	// empty
}

#endif