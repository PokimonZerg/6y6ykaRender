#ifndef _BoundingSphere_H_
#define _BoundingSphere_H_

#include "vector_3d.h"
#include "mesh.h"

class BoundingSphere
{
private:
	Vector3D center;
	float radius;

public:
	BoundingSphere();
	BoundingSphere(Vector3D _center, float _radius);
	BoundingSphere(const BoundingSphere &_s);

	~BoundingSphere();

	Vector3D &GetCenter();
	float     GetRadius();

	static BoundingSphere Build(Mesh &_mesh);
	static BoundingSphere Build(BoundingSphere &_s1, BoundingSphere &_s2);
};

#endif