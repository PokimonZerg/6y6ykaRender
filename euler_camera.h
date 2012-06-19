#ifndef _EULER_CAMERA_H_
#define _EULER_CAMERA_H_

#include "camera.h"

class EulerCamera : public Camera
{
public:
	EulerCamera();
	EulerCamera(Vector3D &_pos);

	~EulerCamera();

	void MoveForward(float _speed);
	void MoveSide(float _speed);

	void RotateX(float _angle);
	void RotateY(float _angle);
	void RotateZ(float _angle);

	Matrix4X4 CalcMatrix();

private:
	Vector3D angles;
};

#endif