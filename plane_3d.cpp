#include "plane_3d.h"

Plane3D::Plane3D()
{
	// empty
}

Plane3D::Plane3D(Vector3D &_n, Vector3D &_p)
{
	n = _n;
	p = _p;
	d = -Vector3D::Dot(p, n);
}

Plane3D::~Plane3D()
{
	// empty
}