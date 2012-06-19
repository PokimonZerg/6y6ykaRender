#ifndef _MESH_H_
#define _MESH_H_

#include <new>
#include <stdlib.h>
#include <crtdbg.h>
#include "triangle.h"

class Mesh
{
public:
	size_t t_size;
	size_t v_size;
	size_t cv_size;

	Triangle *triangles;
	Vector3D *vertex;
	Vector3D *cam_vertex;

	Mesh();
	Mesh(size_t _t, size_t _v);

	~Mesh();

	bool Alloc(size_t _t, size_t _v);
};

inline Mesh::Mesh()
{
	t_size = v_size = cv_size = 0;
}

inline Mesh::Mesh(size_t _t, size_t _v)
{
	Alloc(_t, _v);
}

inline Mesh::~Mesh()
{
	if(t_size)
	{
		free(triangles);
		free(vertex);
		free(cam_vertex);
	}
}

inline bool Mesh::Alloc(size_t _t, size_t _v)
{
	t_size = _t;
	v_size = _v;
	cv_size = _v;

	triangles = (Triangle *)malloc(sizeof(Triangle) * t_size);
	vertex = (Vector3D *)malloc(sizeof(Vector3D) * v_size);
	cam_vertex = (Vector3D *)malloc(sizeof(Vector3D) * cv_size);
	size_t dd = sizeof(Triangle) * t_size;
	return true;
}

#endif