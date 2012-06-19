#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "vector_3d.h"
#include "matrix_4x4.h"
#include "matrix_3X3.h"
#include "quaternion.h"
#include "plane_3d.h"

class Camera
{
	friend class Render;

public:
	Camera(Vector3D &_pos);

	virtual ~Camera();

	virtual void MoveForward(float _speed) = 0;
	virtual void MoveSide(float _speed) = 0;

	virtual void RotateX(float _angle) = 0;
	virtual void RotateY(float _angle) = 0;
	virtual void RotateZ(float _angle) = 0;

	virtual Matrix4X4 CalcMatrix() = 0;

protected:
	Vector3D position;

	const float fov;

	float far_plane;
	float near_plane;
};

#endif