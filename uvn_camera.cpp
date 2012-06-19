#include "uvn_camera.h"

UvnCamera::UvnCamera() : Camera(Vector3D(0, 0, -1)), target(0, 0, -1)
{

}

UvnCamera::UvnCamera(Vector3D &_pos) : Camera(_pos), target(0, 1, 0)
{

}

UvnCamera::~UvnCamera()
{

}

void UvnCamera::MoveForward(float _speed)
{
	position += target * _speed;
}

void UvnCamera::MoveSide(float _speed)
{
	position += Vector3D::Cross(target, Vector3D(0, 1, 0)) * -_speed;
}

void UvnCamera::RotateX(float _angle)
{
	target = target * Matrix3X3::RotateV(-_angle, Vector3D::Cross(target, Vector3D(0, 1, 0)).Normalize());
}

void UvnCamera::RotateY(float _angle)
{
	target = target * Matrix4X4::RotateY(_angle);
}

void UvnCamera::RotateZ(float _angle)
{
	// empty
}

Matrix4X4 UvnCamera::CalcMatrix()
{

	Vector3D forward = target.Normalize();
	Vector3D side    = Vector3D::Cross(forward, Vector3D(0, 1, 0)).Normalize();
	Vector3D up      = Vector3D::Cross(side, forward);

	return Matrix4X4::Translate(-position) * Matrix4X4(side.x, up.x, -forward.x, 0,
													   side.y, up.y, -forward.y, 0,
													   side.z, up.z, -forward.z, 0,
													   0,         0,          0, 1);
}