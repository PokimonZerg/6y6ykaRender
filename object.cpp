#include <cstdlib>
#include <algorithm>
#include <crtdbg.h>
#include <new>
#include "matrix_4x4.h"
#include "trigonometry.h"
#include "object.h"

Object::Object()
{

}

Object::~Object()
{

}

Object *Object::Construct(Model *_model, Color &_color, Vector3D &_pos)
{
	Object *object = new Object();

	object->color = _color;
	object->position = _pos;

	object->mesh.Alloc(_model->t_size / 3, _model->v_size / 3);

	memcpy(object->mesh.vertex, _model->v, _model->v_size * sizeof(float));

	for(size_t i = 0, k = 0; i < object->mesh.t_size; i++, k += 3)
	{
		object->mesh.triangles[i].a = _model->t[k];
		object->mesh.triangles[i].b = _model->t[k + 1];
		object->mesh.triangles[i].c = _model->t[k + 2];
	}

	return object;
}

void Object::Move(Vector3D &_vec)
{
	position += _vec;
}

void Object::Scale(Vector3D &_vec)
{
	Matrix4X4 S = Matrix4X4::Scale(_vec);

	for(size_t i = 0; i < mesh.v_size; i++)
	{
		mesh.vertex[i] = mesh.vertex[i] * S;
	}
}

void Object::Rotate(float _angle, bool _x, bool _y, bool _z)
{
	Matrix4X4 R = Matrix4X4::Identity();

	if(_x)
		R = R * Matrix4X4::RotateX(_angle);
	if(_y)
		R = R * Matrix4X4::RotateY(_angle);
	if(_z)
		R = R * Matrix4X4::RotateZ(_angle);

	for(size_t i = 0; i < mesh.v_size; i++)
	{
		mesh.vertex[i] = mesh.vertex[i] * R;
	}

}