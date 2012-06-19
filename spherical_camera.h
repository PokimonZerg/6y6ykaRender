#ifndef _SPHERICAL_CAMERA_H_
#define _SPHERICAL_CAMERA_H_

#include "camera.h"

class SphericalCamera : public Camera
{
public:
	SphericalCamera();
	SphericalCamera(Vector3D &_pos);

	~SphericalCamera();

	void MoveForward(float _speed);
	void MoveSide(float _speed);

	void RotateX(float _angle);
	void RotateY(float _angle);
	void RotateZ(float _angle);

	Vector3D CalcTarget();

	Matrix4X4 CalcMatrix();

private:
	float h_angle;
	float v_angle;
};

#endif