#ifndef _MATRIX_4X4_H_
#define _MATRIX_4X4_H_

#include <cassert>
#include <cstring>
#include <math.h>
#include "vector_3d.h"
#include "trigonometry.h"

class Matrix4X4
{
private:
	float m[4][4];

public:
	Matrix4X4();
	Matrix4X4(float _m00, float _m01, float _m02, float _m03,
			  float _m10, float _m11, float _m12, float _m13,
			  float _m20, float _m21, float _m22, float _m23,
			  float _m30, float _m31, float _m32, float _m33);
	Matrix4X4(const Matrix4X4 &_mat);

	~Matrix4X4();

	const float *operator [](size_t _index) const;
	float       *operator [](size_t _index)      ;

	Matrix4X4 &operator +=(Matrix4X4 &_mat);
	Matrix4X4 &operator -=(Matrix4X4 &_mat);
	Matrix4X4 &operator *=(Matrix4X4 &_mat);

	Matrix4X4 &Invert();

	static Matrix4X4 Identity();
	static Matrix4X4 Translate(Vector3D &_vec);
	static Matrix4X4 RotateX(float _angle);
	static Matrix4X4 RotateY(float _angle);
	static Matrix4X4 RotateZ(float _angle);
	static Matrix4X4 Scale(Vector3D &_vec);

	friend Matrix4X4 operator *(Matrix4X4 &_mat1, Matrix4X4 &_mat2);
	friend Vector3D operator *(Vector3D &_vec, Matrix4X4 &_mat);
};

inline Matrix4X4::Matrix4X4()
{
	// empty
}

inline Matrix4X4::Matrix4X4(float _m00, float _m01, float _m02, float _m03,
							float _m10, float _m11, float _m12, float _m13,
							float _m20, float _m21, float _m22, float _m23,
							float _m30, float _m31, float _m32, float _m33)
{
	m[0][0] = _m00; m[0][1] = _m01; m[0][2] = _m02; m[0][3] = _m03;
	m[1][0] = _m10; m[1][1] = _m11; m[1][2] = _m12; m[1][3] = _m13;
	m[2][0] = _m20; m[2][1] = _m21; m[2][2] = _m22; m[2][3] = _m23;
	m[3][0] = _m30; m[3][1] = _m31; m[3][2] = _m32; m[3][3] = _m33;
}

inline Matrix4X4::Matrix4X4(const Matrix4X4 &_mat)
{
	memcpy(m, _mat.m, sizeof(m));
}

inline Matrix4X4::~Matrix4X4()
{
	// empty
}

inline const float *Matrix4X4::operator [](size_t _index) const
{
	assert(_index < 4);

	return &m[_index][0];
}

inline float *Matrix4X4::operator [](size_t _index)
{
	assert(_index < 4);

	return &m[_index][0];
}

inline Matrix4X4 Matrix4X4::Identity()
{
	return Matrix4X4(1, 0, 0, 0,
					 0, 1, 0, 0,
					 0, 0, 1, 0,
					 0, 0, 0, 1);
}

inline Matrix4X4 Matrix4X4::Translate(Vector3D &_vec)
{
	return Matrix4X4(1,      0,      0,      0,
					 0,      1,      0,      0,
					 0,      0,      1,      0,
					 _vec.x, _vec.y, _vec.z, 1);
}

inline Matrix4X4 Matrix4X4::RotateX(float _angle)
{
	return Matrix4X4(1, 0,             0,            0,
					 0, bcos(_angle),  bsin(_angle), 0,
		             0, -bsin(_angle), bcos(_angle), 0,
		             0, 0,             0,            1);
}

inline Matrix4X4 Matrix4X4::RotateY(float _angle)
{
	return Matrix4X4(bcos(_angle), 0, -bsin(_angle), 0,
					 0,            1, 0,             0,
		             bsin(_angle), 0, bcos(_angle),  0,
		             0,            0, 0,             1);
}

inline Matrix4X4 Matrix4X4::RotateZ(float _angle)
{
	return Matrix4X4(bcos(_angle),  bsin(_angle), 0, 0,
					 -bsin(_angle), bcos(_angle), 0, 0,
					 0,             0,            1, 0,
		             0,             0,            0, 1);
}

inline Matrix4X4 Matrix4X4::Scale(Vector3D &_vec)
{
	return Matrix4X4(_vec.x, 0,      0,      0,
					 0,      _vec.y, 0,      0,
		             0,      0,      _vec.z, 0,
		             0,      0,      0,      1);
}

inline Matrix4X4 &Matrix4X4::operator +=(Matrix4X4 &_mat)
{
	for(size_t i = 0; i < 4; i++)
	{
		for(size_t k = 0; i < 4; i++)
		{
			m[i][k] += _mat.m[i][k];
		}
	}

	return *this;
}

inline Matrix4X4 &Matrix4X4::operator -=(Matrix4X4 &_mat)
{
	for(size_t i = 0; i < 4; i++)
	{
		for(size_t k = 0; i < 4; i++)
		{
			m[i][k] -= _mat.m[i][k];
		}
	}

	return *this;
}

inline Matrix4X4 operator *(Matrix4X4 &_mat1, Matrix4X4 &_mat2)
{
	Matrix4X4 m;

	for(size_t i = 0; i < 4; i++)
	{
		for(size_t k = 0; k < 4; k++)
		{
			m[i][k] = _mat1[i][0] * _mat2[0][k] +
				      _mat1[i][1] * _mat2[1][k] +
					  _mat1[i][2] * _mat2[2][k] +
					  _mat1[i][3] * _mat2[3][k] ;
		}
	}

	return m;
}

inline Vector3D operator *(Vector3D &_vec, Matrix4X4 &_mat)
{
	float r[4];

	for(size_t i = 0; i < 4; i++)
	{
		r[i] = _mat[0][i] * _vec.x + _mat[1][i] * _vec.y + _mat[2][i] * _vec.z + _mat[3][i] * 1;
	}

	return Vector3D(r[0], r[1], r[2]);
}

/*inline Matrix4X4 &Matrix4X4::Invert()
{
	float det;
	Matrix4X4 inv;

	det =  (m[0][0] * ( m[1][1] * m[2][2] - m[1][2] * m[2][1] ) -
             m[0][1] * ( m[1][0] * m[2][2] - m[1][2] * m[2][0] ) +
             m[0][2] * ( m[1][0] * m[2][1] - m[1][1] * m[2][0] ) );

	//if (fabs(det) < (float)(1E-5))
	//   return *this;

	float det_inv  = 1.0f / det;

	inv[0][0] =  det_inv * ( m[1][1] * m[2][2] - m[1][2] * m[2][1] );
	inv[0][1] = -det_inv * ( m[0][1] * m[2][2] - m[0][2] * m[2][1] );
	inv[0][2] =  det_inv * ( m[0][1] * m[1][2] - m[0][2] * m[1][1] );
	inv[0][3] = 0.0f; // always [0]

	inv[1][0] = -det_inv * ( m[1][0] * m[2][2] - m[1][2] * m[2][0] );
	inv[1][1] =  det_inv * ( m[0][0] * m[2][2] - m[0][2] * m[2][0] );
	inv[1][2] = -det_inv * ( m[0][0] * m[1][2] - m[0][2] * m[1][0] );
	inv[1][3] = 0.0f; // always 0

	inv[2][0] =  det_inv * ( m[1][0] * m[2][1] - m[1][1] * m[2][0] );
	inv[2][1] = -det_inv * ( m[0][0] * m[2][1] - m[0][1] * m[2][0] );
	inv[2][2] =  det_inv * ( m[0][0] * m[1][1] - m[0][1] * m[1][0] );
	inv[2][3] = 0.0f; // always 0

	inv[3][0] = -( m[3][0] * inv[0][0] + m[3][1] * inv[1][0] + m[3][2] * inv[2][0] );
	inv[3][1] = -( m[3][0] * inv[0][1] + m[3][1] * inv[1][1] + m[3][2] * inv[2][1] );
	inv[3][2] = -( m[3][0] * inv[0][2] + m[3][1] * inv[1][2] + m[3][2] * inv[2][2] );
	inv[3][3] = 1.0f; // always 0

	*this = inv;

	return *this;
} */

#endif