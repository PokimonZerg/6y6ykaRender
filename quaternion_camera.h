#ifndef _QUATERNION_CAMERA_H_
#define _QUATERNION_CAMERA_H_

#include "camera.h"

class QuaternionCamera : public Camera
{
public:
	QuaternionCamera();
	QuaternionCamera(Vector3D &_pos);

	~QuaternionCamera();

	void MoveForward(float _speed);
	void MoveSide(float _speed);

	void RotateX(float _angle);
	void RotateY(float _angle);
	void RotateZ(float _angle);

	Matrix4X4 CalcMatrix();

private:
	Quaternion rotation;
};

#endif