#ifndef _PLANE_3D_H_
#define _PLANE_3D_H_

#include "vector_3d.h"

class Plane3D
{
public:
	Vector3D n; // normal
	Vector3D p; // point
	float    d; // dist

	Plane3D();
	Plane3D(Vector3D &_n, Vector3D &_p);

	~Plane3D();
};

#endif