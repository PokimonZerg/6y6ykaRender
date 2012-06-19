#include "spherical_camera.h"

SphericalCamera::SphericalCamera() : Camera(Vector3D(0, 0, 0))
{
	h_angle = 180;
	v_angle = 0;
}

SphericalCamera::SphericalCamera(Vector3D &_pos) : Camera(_pos)
{
	h_angle = 0;
	v_angle = 0;
}

SphericalCamera::~SphericalCamera()
{

}

Vector3D SphericalCamera::CalcTarget()
{
	return Vector3D(bcos(h_angle) * bsin(v_angle),
					bsin(h_angle),
					bcos(-h_angle) * bcos(-v_angle));
}

void SphericalCamera::MoveForward(float _speed)
{
	position += CalcTarget() * _speed;
}

void SphericalCamera::MoveSide(float _speed)
{
	position += Vector3D::Cross(CalcTarget(), Vector3D(0, 1, 0)) * -_speed;
}

void SphericalCamera::RotateX(float _angle)
{
	h_angle -= _angle;
}

void SphericalCamera::RotateY(float _angle)
{
	v_angle += _angle;
}

void SphericalCamera::RotateZ(float _angle)
{
	// empty
}

Matrix4X4 SphericalCamera::CalcMatrix()
{
	Vector3D forward = CalcTarget  ().Normalize();
	Vector3D side    = Vector3D::Cross(forward, Vector3D(0, 1, 0)).Normalize();
	Vector3D up      = Vector3D::Cross(side, forward);

	return Matrix4X4::Translate(-position) * Matrix4X4(side.x, up.x, -forward.x, 0,
													   side.y, up.y, -forward.y, 0,
													   side.z, up.z, -forward.z, 0,
													   0,         0,          0, 1);
}