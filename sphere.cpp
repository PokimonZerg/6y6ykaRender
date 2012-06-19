#include "trigonometry.h"
#include "sphere.h"

Sphere::Sphere() : mesh()
{
}

Sphere::~Sphere()
{
	// empty
}

Mesh &Sphere::GetMesh()
{
	return mesh;
}

/*bool Sphere::Build(Vector3D &_center, float _radius)
{
	float t = -90.0f; // -90 - 90
	float f = 0.0f; // 0 - 360

	float step_t = 30.0f;
	float step_f = 30.0f;

	size_t vertex = size_t((360.0f / step_f) * (180.0f / step_t) * 2.0f) * 3;

	mesh.Alloc(vertex / 3, 0, 0);

	Vector3D *p = (Vector3D *)malloc(vertex * sizeof(Vector3D));;

	for(size_t i = 0; i < vertex; )
	{
		for(float k = 0; k < 360.0f; k += step_f)
		{
			p[i] = CalcPoint(_center, _radius, t, k);
			i++;
		}

		t += step_t;
		//p1 = CalcPoint(_center, _radius, t + step_t * i, f + step_f * i);
	}

	free(p);

	return true;
}*/

Vector3D Sphere::CalcPoint(Vector3D &_center, float _radius, float _t, float _f)
{
	float x = _center.x + _radius * bsin(_t) * bcos(_f);
	float y = _center.y + _radius * bsin(_t) * bsin(_f);
	float co = bcos(_t);
	float z = float( _center.z + _radius * bcos(_t));
	return Vector3D(_center.x + _radius * bsin(_t) * bcos(_f),
					_center.y + _radius * bsin(_t) * bsin(_f),
					_center.z + _radius * bcos(_t));
}