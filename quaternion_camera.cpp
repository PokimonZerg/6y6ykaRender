#include "quaternion_camera.h"

QuaternionCamera::QuaternionCamera() : Camera(Vector3D(0, 0, 0))
{

}

QuaternionCamera::QuaternionCamera(Vector3D &_pos) : Camera(_pos)
{

}

QuaternionCamera::~QuaternionCamera()
{

}

void QuaternionCamera::MoveForward(float _speed)
{
	position += rotation * Vector3D(0, 0, _speed);
}

void QuaternionCamera::MoveSide(float _speed)
{
	position += rotation * Vector3D(_speed, 0, 0);
}

void QuaternionCamera::RotateX(float _angle)
{
	rotation = rotation * Quaternion(_angle, Vector3D(1, 0, 0));
}

void QuaternionCamera::RotateY(float _angle)
{
	rotation = Quaternion(_angle, Vector3D(0, 1, 0)) * rotation;
}

void QuaternionCamera::RotateZ(float _angle)
{
	rotation = Quaternion(_angle, Vector3D(0, 0, 1)) * rotation;
}

Matrix4X4 QuaternionCamera::CalcMatrix()
{
	return Matrix4X4::Translate(position) * rotation.Normalize().ToMatrix4X4();
}