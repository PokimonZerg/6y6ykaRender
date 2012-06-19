#ifndef _UVN_CAMERA_H_
#define _UVN_CAMERA_H_

#include "camera.h"

class UvnCamera : public Camera
{
public:
	UvnCamera();
	UvnCamera(Vector3D &_pos);

	~UvnCamera();

	void MoveForward(float _speed);
	void MoveSide(float _speed);

	void RotateX(float _angle);
	void RotateY(float _angle);
	void RotateZ(float _angle);

	Vector3D CalcTarget();

	Matrix4X4 CalcMatrix();

private:
	Vector3D target;
};

#endif