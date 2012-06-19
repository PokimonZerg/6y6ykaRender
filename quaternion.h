#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include "vector_3d.h"
#include "matrix_4x4.h"
#include "matrix_3X3.h"
#include "trigonometry.h"

class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

	Quaternion();
	Quaternion(float _x, float _y, float _z, float _w);
	Quaternion(float _angle, Vector3D &_vec);
	Quaternion(const Quaternion &_q);

	~Quaternion();

	Quaternion &operator *=(Quaternion &_q);
	Quaternion operator *(Quaternion &q);
	Vector3D operator *(Vector3D &_vec);
	friend Quaternion operator /(float _s, Quaternion &_q);

	Matrix4X4 ToMatrix4X4();
	Matrix3X3 ToMatrix3X3();

	Quaternion Conjugate();

	Quaternion &Normalize();

	float Length();

	Quaternion &Inverse();
};

inline Quaternion::Quaternion()
{
	x = 0;
	y = 0;
	z = 0;
	w = 1;
}

inline Quaternion::Quaternion(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

inline Quaternion::Quaternion(float _angle, Vector3D &_vec)
{
	float sine = bsin(_angle / 2);
	Vector3D vn(_vec);
	vn.Normalize();

	x = vn.x * sine;
	y = vn.y * sine;
	z = vn.z * sine;
	w = bcos(_angle / 2);
}

inline Quaternion::Quaternion(const Quaternion &_q)
{
	x = _q.x;
	y = _q.y;
	z = _q.z;
	w = _q.w;
}

inline Quaternion::~Quaternion()
{
	// empty
}

inline Quaternion &Quaternion::operator *=(Quaternion &_q)
{
	*this = Quaternion(y * _q.z - z * _q.y + w * _q.x + x * _q.w,
					   z * _q.x - x * _q.z + w * _q.y + y * _q.w,
					   x * _q.y - y * _q.x + w * _q.z + z * _q.w,
					   w * _q.w - x * _q.x - y * _q.y - z * _q.z);

	return *this;
}

inline Quaternion Quaternion::operator *(Quaternion &q)
{
	Quaternion r;

	r.w = w*q.w - x*q.x - y*q.y - z*q.z;
	r.x = w*q.x + x*q.w + y*q.z - z*q.y;
	r.y = w*q.y + y*q.w + z*q.x - x*q.z;
	r.z = w*q.z + z*q.w + x*q.y - y*q.x;
	
	return r;
}

inline Quaternion Quaternion::Conjugate()
{
	return Quaternion(-x, -y, -z, w);
}

inline Vector3D Quaternion::operator *(Vector3D &_vec)
{
	Vector3D vn(_vec);
//	vn.Normalize();
 
	Quaternion vecQuat, resQuat;
	vecQuat.x = vn.x;
	vecQuat.y = vn.y;
	vecQuat.z = vn.z;
	vecQuat.w = 0.0f;
 
	resQuat = vecQuat * Conjugate();
	resQuat = *this * resQuat;
 
	return Vector3D(resQuat.x, resQuat.y, resQuat.z);
}

inline Matrix4X4 Quaternion::ToMatrix4X4()
{
	Matrix4X4 m;

	m[0][0] = 1.0f - 2.0f * ( y * y + z * z );  
	m[0][1] = 2.0f * ( x * y - w * z );  
	m[0][2] = 2.0f * ( x * z + w * y );  
	m[0][3] = 0.0f;  

	m[1][0] = 2.0f * ( x * y + w * z );  
	m[1][1] = 1.0f - 2.0f * ( x * x + z * z );  
	m[1][2] = 2.0f * ( y * z - w * x );  
	m[1][3] = 0.0f;  

	m[2][0] = 2.0f * ( x * z - w * y );  
	m[2][1] = 2.0f * ( y * z + w * x );  
	m[2][2] = 1.0f - 2.0f * ( x * x + y * y );  
	m[2][3] = 0.0f;  

	m[3][0] = 0;  
	m[3][1] = 0;  
	m[3][2] = 0;  
	m[3][3] = 1.0f;

	return m;
}

inline Matrix3X3 Quaternion::ToMatrix3X3()
{
	return Matrix3X3(1.0f - 2.0f * (y * y + z * z), 2.0f * (x * y - z * w)       , 2.0f * (x * z + y * w),
					 2.0f * (x * y + z * w)       , 1.0f - 2.0f * (x * x + z * z), 2.0f * (y * z - x * w),
					 2.0f * (x * z - y * w)       , 2.0f * (y * z + x * w)       , 1.0f - 2.0f * (x * x + y * y));
}

inline Quaternion operator /(Quaternion &_q, float _s)
{
	return Quaternion(_q.x / _s, _q.y / _s, _q.z / _s, _q.w / _s);
}

inline Quaternion &Quaternion::Normalize()
{

	/*float mag2 = w * w + x * x + y * y + z * z;
	if (fabs(mag2) > 0.00001f && fabs(mag2 - 1.0f) > 0.00001f) 
	{
		float mag = sqrt(mag2);
		w /= mag;
		x /= mag;
		y /= mag;
		z /= mag;
	}*/
	Quaternion q = *this;

	*this = q / Length();

	return *this;
}

inline float Quaternion::Length()
{
	return sqrt(w * w + x * x + y * y + z * z);
}
// ×ÒÎ ÝÒÎ ÇÀ ÅÐÓÍÄÅÍÜ?
inline Quaternion &Quaternion::Inverse()
{
	Quaternion q = *this;
	q = this->Conjugate();

	/*if(Length() == 0)
		return *this;

	return *this = q / Length();*/
//	float mag2 = w * w + x * x + y * y + z * z;
//	if (fabs(mag2) > 0.00001f && fabs(mag2 - 1.0f) > 0.00001f) 
	//{
	//	float mag = sqrt(mag2);
	//	mag = Length();
		*this = q / Length();
	//}

	return *this;
}

#endif