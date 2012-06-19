#ifndef _VECTOR_3D_H_
#define _VECTOR_3D_H_

#include <cassert>
#include <cmath>

class Vector3D
{
public:
	float x;
	float y;
	float z;

	Vector3D();
	Vector3D(float _x, float _y, float _z);
	Vector3D(const Vector3D &_vec);

	~Vector3D();

	Vector3D &operator =(const Vector3D &_vec);

	Vector3D operator +() const;
	Vector3D operator -() const;

	Vector3D &operator +=(const Vector3D &_vec);
	Vector3D &operator -=(const Vector3D &_vec);
	Vector3D &operator *=(const Vector3D &_vec);
	Vector3D &operator /=(const Vector3D &_vec);

	Vector3D &operator *=(float _s);
	Vector3D &operator /=(float _s);

	float &operator [](size_t _index);
	float  operator [](size_t _index) const;

	bool operator ==(const Vector3D &_vec) const;
	bool operator !=(const Vector3D &_vec) const;

	float Length() const;

	Vector3D &Normalize();

	static Vector3D Null();

	static float Dot(const Vector3D &_vec1, const Vector3D &_vec2);

	static Vector3D Cross(const Vector3D &_vec1, const Vector3D &_vec2);
};

Vector3D operator +(const Vector3D &_vec1, const Vector3D &_vec2);
Vector3D operator -(const Vector3D &_vec1, const Vector3D &_vec2);
Vector3D operator *(const Vector3D &_vec1, const Vector3D &_vec2);
Vector3D operator /(const Vector3D &_vec1, const Vector3D &_vec2);

Vector3D operator *(float _s,              const Vector3D &_vec );
Vector3D operator *(const Vector3D &_vec,  float _s             );

Vector3D operator /(float _s,              const Vector3D &_vec );
Vector3D operator /(const Vector3D &_vec,  float _s             );

inline Vector3D::Vector3D()
{
	// empty
}

inline Vector3D::Vector3D(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

inline Vector3D::Vector3D(const Vector3D &_vec)
{
	x = _vec.x;
	y = _vec.y;
	z = _vec.z;
}

inline Vector3D::~Vector3D()
{
	// empty
}

inline Vector3D &Vector3D::operator =(const Vector3D &_vec)
{
	x = _vec.x;
	y = _vec.y;
	z = _vec.z;

	return *this;
}

inline Vector3D Vector3D::operator +() const
{
	return *this;
}

inline Vector3D Vector3D::operator -() const
{
	return Vector3D(-x, -y, -z);
}

inline Vector3D &Vector3D::operator +=(const Vector3D &_vec)
{
	x += _vec.x;
	y += _vec.y;
	z += _vec.z;

	return *this;
}

inline Vector3D &Vector3D::operator -=(const Vector3D &_vec)
{
	x -= _vec.x;
	y -= _vec.y;
	z -= _vec.z;

	return *this;
}

inline Vector3D &Vector3D::operator *=(const Vector3D &_vec)
{
	x *= _vec.x;
	y *= _vec.y;
	z *= _vec.z;

	return *this;
}

inline Vector3D &Vector3D::operator /=(const Vector3D &_vec)
{
	x /= _vec.x;
	y /= _vec.y;
	z /= _vec.z;

	return *this;
}

inline Vector3D &Vector3D::operator *=(float _s)
{
	x *= _s;
	y *= _s;
	z *= _s;

	return *this;
}

inline Vector3D &Vector3D::operator /=(float _s)
{
	x /= _s;
	y /= _s;
	z /= _s;

	return *this;
}

inline float &Vector3D::operator [](size_t _index)
{
	assert(_index < 3);

	return *(&x + _index);
}

inline float Vector3D::operator [](size_t _index) const
{
	assert(_index < 3);

	return *(&x + _index);
}

inline bool Vector3D::operator ==(const Vector3D &_vec) const
{
	return x == _vec.x &&
		   y == _vec.y &&
		   z == _vec.z  ;
}

inline bool Vector3D::operator !=(const Vector3D &_vec) const
{
	return x != _vec.x ||
		   y != _vec.y ||
		   z != _vec.z  ;
}

inline float Vector3D::Length() const
{
	return sqrt(x * x + y * y + z * z);
}

inline Vector3D &Vector3D::Normalize()
{
	float len  = Length();

	if(len < (float)(1E-5))
		return *this;
		
	return (*this) /= len;
}

inline Vector3D Vector3D::Null()
{
	return Vector3D(0, 0, 0);
}

inline Vector3D operator +(const Vector3D &_vec1, const Vector3D &_vec2)
{
	return Vector3D(_vec1.x + _vec2.x,
				    _vec1.y + _vec2.y,
					_vec1.z + _vec2.z);
}

inline Vector3D operator -(const Vector3D &_vec1, const Vector3D &_vec2)
{
	return Vector3D(_vec1.x - _vec2.x,
				    _vec1.y - _vec2.y,
					_vec1.z - _vec2.z);
}

inline Vector3D operator *(const Vector3D &_vec1, const Vector3D &_vec2)
{
	return Vector3D(_vec1.x * _vec2.x,
				    _vec1.y * _vec2.y,
					_vec1.z * _vec2.z);
}

inline Vector3D operator /(const Vector3D &_vec1, const Vector3D &_vec2)
{
	return Vector3D(_vec1.x / _vec2.x,
				    _vec1.y / _vec2.y,
					_vec1.z / _vec2.z);
}

inline Vector3D operator *(float _s, const Vector3D &_vec)
{
	return Vector3D(_vec.x * _s,
				    _vec.y * _s,
					_vec.z * _s);
}

inline Vector3D operator *(const Vector3D &_vec, float _s)
{
	return Vector3D(_vec.x * _s,
				    _vec.y * _s,
					_vec.z * _s);
}

inline Vector3D operator /(float _s, const Vector3D &_vec)
{
	return Vector3D(_s / _vec.x,
				    _s / _vec.y,
					_s / _vec.z);
}

inline Vector3D operator /(const Vector3D &_vec, float _s)
{
	return Vector3D(_vec.x / _s,
				    _vec.y / _s,
					_vec.z / _s);
}

inline float Vector3D::Dot(const Vector3D &_vec1, const Vector3D &_vec2)
{
	return _vec1.x * _vec2.x +
		   _vec1.y * _vec2.y +
		   _vec1.z * _vec2.z ;
}

inline Vector3D Vector3D::Cross(const Vector3D &_vec1, const Vector3D &_vec2)
{
	return Vector3D(_vec1.y * _vec2.z - _vec1.z * _vec2.y,
					_vec1.z * _vec2.x - _vec1.x * _vec2.z,
					_vec1.x * _vec2.y - _vec1.y * _vec2.x);
}

#endif