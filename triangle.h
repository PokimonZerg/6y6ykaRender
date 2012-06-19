#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "vector_3d.h"

class Triangle
{
public:
	size_t a;
	size_t b;
	size_t c;

	bool visible;

	Triangle();
	Triangle(size_t _a, size_t _b, size_t _c);

	~Triangle();

	size_t operator [](size_t _index);
};

inline Triangle::Triangle()
{
	// empty
}

inline Triangle::Triangle(size_t _a, size_t _b, size_t _c)
{
	a = _a;
	b = _b;
	c = _c;
}

inline Triangle::~Triangle()
{
	// empty
}

inline size_t Triangle::operator [](size_t _index)
{
	return *(&a + _index);
}

#endif