#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "mesh.h"

class Sphere
{
private:
	Mesh mesh;

	Vector3D CalcPoint(Vector3D &_center, float _radius, float _t, float _f);

public:
	Sphere();

	~Sphere();

	bool Build(Vector3D &_center, float _radius);

	Mesh &GetMesh();
};

#endif