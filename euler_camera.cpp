#include "euler_camera.h"

EulerCamera::EulerCamera() : Camera(Vector3D(0, 0, 0)), angles(0, 0, 0)
{

}

EulerCamera::EulerCamera(Vector3D &_pos) : Camera(_pos), angles(0, 0, 0)
{

}

EulerCamera::~EulerCamera()
{

}

void EulerCamera::MoveForward(float _speed)
{
	position += Vector3D(0, 0, -_speed) * Matrix4X4::RotateX(angles.x) * 
										  Matrix4X4::RotateY(angles.y);
}

void EulerCamera::MoveSide(float _speed)
{
	position += Vector3D(-_speed, 0, 0) * Matrix4X4::RotateY(angles.y) ;
}

void EulerCamera::RotateX(float _angle)
{
	angles.x += _angle;
}

void EulerCamera::RotateY(float _angle)
{
	angles.y += _angle;
}

void EulerCamera::RotateZ(float _angle)
{
	angles.z += _angle;
}

Matrix4X4 EulerCamera::CalcMatrix()
{
	return Matrix4X4::Translate(-position) * Matrix4X4::RotateY(-angles.y) *
	       Matrix4X4::RotateX(-angles.x)   * Matrix4X4::RotateZ(-angles.z) ;
}