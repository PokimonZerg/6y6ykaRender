#ifndef _MATRIX_3X3_H_
#define _MATRIX_3X3_H_

#include "vector_3d.h"

class Matrix3X3
{
private:
	float m[3][3];

public:
	Matrix3X3();
	Matrix3X3(const Matrix3X3 &_mat);
	Matrix3X3(float _m00, float _m01, float _m02,
		      float _m10, float _m11, float _m12,
			  float _m20, float _m21, float _m22);

	~Matrix3X3();

	const float *operator [](size_t _index) const;
	float *operator [](size_t _index);

	friend Vector3D  operator *(Vector3D &_vec  , Matrix3X3 &_mat );
	friend Matrix3X3 operator *(Matrix3X3 &_mat1, Matrix3X3 &_mat2);

	static Matrix3X3 Identity();
	static Matrix3X3 Translate(Vector3D &_vec);
	static Matrix3X3 RotateX(float _angle);
	static Matrix3X3 RotateY(float _angle);
	static Matrix3X3 RotateZ(float _angle);
	static Matrix3X3 RotateV(float _angle, Vector3D &_v);
};

inline Matrix3X3::Matrix3X3()
{
	// empty
}

inline Matrix3X3::Matrix3X3(const Matrix3X3 &_mat)
{
    m[0][0] = _mat.m[0][0]; m[0][1] = _mat.m[0][1]; m[0][2] = _mat.m[0][2];
	m[1][0] = _mat.m[1][0]; m[1][1] = _mat.m[1][1]; m[1][2] = _mat.m[1][2];
	m[2][0] = _mat.m[2][0]; m[2][1] = _mat.m[2][1]; m[2][2] = _mat.m[2][2];

	//*this = _mat;
}

inline Matrix3X3::Matrix3X3(float _m00, float _m01, float _m02,
		                    float _m10, float _m11, float _m12,
			                float _m20, float _m21, float _m22)
{
	m[0][0] = _m00; m[0][1] = _m01; m[0][2] = _m02;
	m[1][0] = _m10; m[1][1] = _m11; m[1][2] = _m12;
	m[2][0] = _m20, m[2][1] = _m21; m[2][2] = _m22;
}

inline Matrix3X3::~Matrix3X3()
{
	// empty
}

inline const float *Matrix3X3::operator [](size_t _index) const
{
	assert(_index < 3);

	return &m[_index][0];
}

inline float *Matrix3X3::operator [](size_t _index)
{
	assert(_index < 3);

	return &m[_index][0];
}

inline Vector3D operator *(Vector3D &_vec, Matrix3X3 &_mat)
{
	return Vector3D(_mat[0][0] * _vec.x + _mat[1][0] * _vec.y + _mat[2][0] * _vec.z,
					_mat[0][1] * _vec.x + _mat[1][1] * _vec.y + _mat[2][1] * _vec.z,
					_mat[0][2] * _vec.x + _mat[1][2] * _vec.y + _mat[2][2] * _vec.z);

	/*return Vector3D(_mat[0][0] * _vec.x + _mat[0][1] * _vec.y + _mat[0][1] * _vec.z,
					_mat[1][0] * _vec.x + _mat[1][1] * _vec.y + _mat[1][2] * _vec.z,
					_mat[2][0] * _vec.x + _mat[2][1] * _vec.y + _mat[2][2] * _vec.z);*/
}

inline Matrix3X3 operator *(Matrix3X3 &_mat1, Matrix3X3 &_mat2)
{
	return Matrix3X3(_mat1[0][0] * _mat2[0][0] + _mat1[0][1] * _mat2[1][0] + _mat1[0][2] * _mat2[2][0],
					 _mat1[0][0] * _mat2[0][1] + _mat1[0][1] * _mat2[1][1] + _mat1[0][2] * _mat2[2][1],
					 _mat1[0][0] * _mat2[0][2] + _mat1[0][1] * _mat2[1][2] + _mat1[0][2] * _mat2[2][2],
					 _mat1[1][0] * _mat2[0][0] + _mat1[1][1] * _mat2[1][0] + _mat1[1][2] * _mat2[2][0],
					 _mat1[1][0] * _mat2[0][1] + _mat1[1][1] * _mat2[1][1] + _mat1[1][2] * _mat2[2][1],
					 _mat1[1][0] * _mat2[0][2] + _mat1[1][1] * _mat2[1][2] + _mat1[1][2] * _mat2[2][2],
					 _mat1[2][0] * _mat2[0][0] + _mat1[2][1] * _mat2[1][0] + _mat1[2][2] * _mat2[2][0],
					 _mat1[2][0] * _mat2[0][1] + _mat1[2][1] * _mat2[1][1] + _mat1[2][2] * _mat2[2][1],
					 _mat1[2][0] * _mat2[0][2] + _mat1[2][1] * _mat2[1][2] + _mat1[2][2] * _mat2[2][2]);
}

inline Matrix3X3 Matrix3X3::Identity()
{
	return Matrix3X3(1.0f, 0.0f, 0.0f,
		             0.0f, 1.0f, 0.0f,
					 0.0f, 0.0f, 1.0f);
}

inline Matrix3X3 Matrix3X3::Translate(Vector3D &_vec)
{
	/*return Matrix3X3(1.0f  , 0.0f  ,_vec.x ,
					 0.0f  , 1.0f  ,_vec.y ,
					 0.0f, 0.0f, _vec.z);*/
	return Matrix3X3(1.0f  , 0.0f  , 0.0f ,
					 0.0f  , 1.0f  , 0.0f ,
					 _vec.x, _vec.y, _vec.z);
}

inline Matrix3X3 Matrix3X3::RotateX(float _angle)
{
	float sina = bsin(_angle);
	float cosa = bcos(_angle);

	return Matrix3X3(1.0f, 0.0f, 0.0f ,
					 0.0f, cosa, -sina,
					 0.0f, sina, cosa);
}

inline Matrix3X3 Matrix3X3::RotateY(float _angle)
{
	float sina = bsin(_angle);
	float cosa = bcos(_angle);

	return Matrix3X3(cosa , 0.0f, sina,
					 0.0f , 1.0f, 0.0f,
					 -sina, 0.0f, cosa);
}

inline Matrix3X3 Matrix3X3::RotateZ(float _angle)
{
	float sina = bsin(_angle);
	float cosa = bcos(_angle);

	return Matrix3X3(cosa, -sina, 0.0f,
					 sina, cosa , 0.0f,
					 0.0f, 0.0f , 1.0f);
}

inline Matrix3X3 Matrix3X3::RotateV(float _angle, Vector3D &_v)
{
	float bcosa = bcos(_angle);
	float bsina = bsin(_angle);
	float x = _v.x;
	float y = _v.y;
	float z = _v.z;

	return Matrix3X3(bcosa + (1 - bcosa) * x * x,     (1 - bcosa) * x * y - bsina * z, (1 - bcosa) * x * z + bsina * y,
					 (1 - bcosa) * y * x + bsina * z, bcosa + (1 - bcosa) * y * y,     (1 - bcosa) * y * z - bsina * x,
					 (1 - bcosa) * z * x - bsina * y, (1 - bcosa) * z * y + bsina * x, bcosa + (1 - bcosa) * z * z);
}

#endif