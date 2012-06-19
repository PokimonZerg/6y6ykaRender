#ifndef _LINE_H_
#define _LINE_H_

#include "vector_3d.h"
#include "color.h"

class Line
{
public:
	Vector3D a;
	Vector3D b;
	Color color;
	bool visible;

	Line(Vector3D &_a, Vector3D &_b, Color &_c);

	~Line();
};

inline Line::Line(Vector3D &_a, Vector3D &_b, Color &_c)
{
	a = _a;
	b = _b;
	color = _c;
	visible = true;
}

inline Line::~Line()
{

}

#endif