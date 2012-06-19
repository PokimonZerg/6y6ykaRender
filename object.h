#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "vector_3d.h"
#include "color.h"
#include "model.h"
#include "b_array.h"
#include "triangle.h"
#include "mesh.h"

struct Object
{
	friend class Render;

public:
	Object();

	~Object();

	static Object *Construct(Model *_model, Color &_color, Vector3D &_pos);

	void Move(Vector3D &_vec);
	void Scale(Vector3D &_vec);
	void Rotate(float _angle, bool _x, bool _y, bool _z);

private:
	Mesh mesh;

	Vector3D position;

	Color color;

};

#endif