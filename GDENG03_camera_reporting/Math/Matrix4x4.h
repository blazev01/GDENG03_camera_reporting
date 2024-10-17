#pragma once
#include "Vector3.h"
#include "Vector4.h"
#include "memory"

class Matrix4x4
{
public:
	Matrix4x4();
	Matrix4x4(const Matrix4x4& matrix);
	~Matrix4x4();

public:
	void SetIdentity();
	void SetPosition(const Vector3& position);
	void SetScale(const Vector3& scale);
	void SetRotationX(float x);
	void SetRotationY(float y);
	void SetRotationZ(float z);
	void SetRotation(float angle, Vector3 axis);

	Vector3 GetPosition();
	Vector3 GetRight();
	Vector3 GetUp();
	Vector3 GetForward();

	float GetDeterminant() const;
	void Inverse();

	void SetPerspectiveLH(float fov, float aspect, float zNear, float zFar);
	void SetOrthoLH(float width, float height, float nearPlane, float farPlane);
	void SetMatrix(const Matrix4x4& matrix);

	void operator *=(const Matrix4x4& matrix);

	friend std::ostream& operator<<(std::ostream& out, const Matrix4x4& matrix4x4);

public:
	float mat[4][4] = {};
};

