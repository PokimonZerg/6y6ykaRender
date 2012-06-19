#ifndef _TRIGONOMETRY_H_
#define _TRIGONOMETRY_H_

#include "b_cos.h"
#include "b_sin.h"
#include "vector_3d.h"
#include "plane_3d.h"

#define PI 3.1415926535897932384626433832795

inline double Radian(double _angle)
{
	return _angle * PI / 180.0f;
}

inline double Degree(double _angle)
{
	return _angle * 180 / PI;
}

inline Vector3D CutLine3DZ(Vector3D &_p1, Vector3D &_p2, float _z)
{
	Vector3D v = _p2 - _p1;

	float t = (_z - _p1.z) / v.z;

	return Vector3D(_p1.x + v.x *t, _p1.y + v.y * t, _z);
}

inline bool PlaneLineIntersection(Vector3D &_p1, Vector3D &_p2, Plane3D &_p, Vector3D &_d)
{
	float c = Vector3D::Dot(_p.n, _p2);
	float d = Vector3D::Dot(_p.n, _p1) + _p.d;

	_d = _p1 + -d/c * _p2;

	return true;
}

#endif