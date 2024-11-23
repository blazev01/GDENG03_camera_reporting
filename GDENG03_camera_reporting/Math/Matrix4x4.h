#pragma once
#include "Vector3D.h"
#include "Vector4D.h"
#include "memory"

class Matrix4x4
{
public:
	Matrix4x4();
	Matrix4x4(const Matrix4x4& matrix);
	~Matrix4x4();

public:
	void SetIdentity();
	void SetPosition(const Vector3D& position);
	void SetScale(const Vector3D& scale);
	void SetRotationX(float x);
	void SetRotationY(float y);
	void SetRotationZ(float z);
	void SetRotation(float angle, Vector3D axis);

	Vector3D GetPosition();
	Vector3D GetScale();
	Vector3D GetRotation();
	Vector3D GetRight();
	Vector3D GetUp();
	Vector3D GetForward();

	float GetDeterminant() const;
	void Inverse();

	void SetPerspectiveLH(float fov, float aspect, float zNear, float zFar);
	void SetOrthoLH(float width, float height, float nearPlane, float farPlane);
	void SetMatrix(const Matrix4x4& matrix);
	void SetMatrix(float matrix[16]);
	float* GetAs1DArray() const;

	void operator *=(const Matrix4x4& matrix);

	friend std::ostream& operator<<(std::ostream& out, const Matrix4x4& matrix4x4);

public:
	float mat[4][4] = {};
};

