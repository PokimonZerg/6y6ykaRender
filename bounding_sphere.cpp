#include <algorithm>
#include "bounding_sphere.h"

using std::max;
using std::min;

BoundingSphere::BoundingSphere() : center(0, 0, 0)
{
	radius = 0;
}

BoundingSphere::BoundingSphere(Vector3D _center, float _radius) : center(_center)
{
	radius = _radius;
}

BoundingSphere::BoundingSphere(const BoundingSphere &_s)
{
	*this = _s;
}

BoundingSphere::~BoundingSphere()
{
	// empty
}

Vector3D &BoundingSphere::GetCenter()
{
	return center;
}

float BoundingSphere::GetRadius()
{
	return radius;
}

/*BoundingSphere BoundingSphere::Build(Mesh &_mesh)
{
	float max_x = 0, min_x = 0;
	float max_y = 0, min_y = 0;
	float max_z = 0, min_z = 0;

	for(size_t i = 0; i < _mesh.t_size; i++)
	{
		for(size_t k = 0; k < 3; k++)
		{
			Vector3D &vertex = _mesh.triangles[i][k];

			max_x = max(vertex.x, max_x); min_x = min(vertex.x, min_x);
			max_y = max(vertex.y, max_y); min_y = min(vertex.y, min_y);
			max_z = max(vertex.z, max_z); min_z = min(vertex.z, min_z);
		}
	}

	Vector3D c((min_x + max_x) / 2, (min_y + max_y) / 2, (min_z + max_z) / 2);

	float r = 0;

	for(size_t i = 0; i < _mesh.t_size; i++)
	{
		for(size_t k = 0; k < 3; k++)
		{
			Vector3D &vertex = _mesh.triangles[i][k];

			r = max(r, sqrt(vertex.x * vertex.x + vertex.y * vertex.y + vertex.z * vertex.z));
		}
	}

	return BoundingSphere(c, r);
}*/

BoundingSphere BoundingSphere::Build(BoundingSphere &_s1, BoundingSphere &_s2)
{
	Vector3D c_vec = _s2.center - _s1.center;
	float c_len = c_vec.Length();

	return BoundingSphere(_s1.center + ((c_len + _s2.radius - _s1.radius) / 2 * c_len) * c_vec,
		         (_s1.radius + _s2.radius + c_len) / 2);
}