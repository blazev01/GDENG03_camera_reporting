#pragma once
#include "Vector3.h"
#include "memory"

class Matrix4x4
{
public:
	Matrix4x4();
	~Matrix4x4();

public:
	void SetIdentity();
	void SetTranslation(const Vector3& translation);
	void SetOrthoLH(float width, float height, float nearPlane, float farPlane);
	void SetScale(const Vector3& scale);
	void SetRotationX(float x);
	void SetRotationY(float y);
	void SetRotationZ(float z);


	void SetMatrix(const Matrix4x4& matrix);

	void operator *=(const Matrix4x4& matrix);

public:
	float mat[4][4] = {};
};

