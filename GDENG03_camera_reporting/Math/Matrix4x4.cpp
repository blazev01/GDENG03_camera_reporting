#include "Matrix4x4.h"

Matrix4x4::Matrix4x4()
{}

Matrix4x4::~Matrix4x4()
{}

void Matrix4x4::SetIdentity()
{
	::memset(this->mat, 0, sizeof(float) * 16);
	this->mat[0][0] = 1;
	this->mat[1][1] = 1;
	this->mat[2][2] = 1;
	this->mat[3][3] = 1;
}

void Matrix4x4::SetTranslation(const Vector3& translation)
{
	this->SetIdentity();
	this->mat[3][0] = translation.x;
	this->mat[3][1] = translation.y;
	this->mat[3][2] = translation.z;
}

void Matrix4x4::SetOrthoLH(float width, float height, float nearPlane, float farPlane)
{
	this->SetIdentity();
	this->mat[0][0] = 2.0f / width;
	this->mat[1][1] = 2.0f / height;
	this->mat[2][2] = 1.0f / (farPlane - nearPlane);
	this->mat[3][2] = -(nearPlane / (farPlane - nearPlane));
}

void Matrix4x4::SetScale(const Vector3& scale)
{
	this->SetIdentity();
	this->mat[0][0] = scale.x;
	this->mat[1][1] = scale.y;
	this->mat[2][2] = scale.z;
}

void Matrix4x4::SetRotationX(float x)
{
	this->SetIdentity();
	this->mat[1][1] = cos(x);
	this->mat[1][2] = sin(x);
	this->mat[2][1] = -sin(x);
	this->mat[2][2] = cos(x);
}

void Matrix4x4::SetRotationY(float y)
{
	this->SetIdentity();
	this->mat[0][0] = cos(y);
	this->mat[0][2] = -sin(y);
	this->mat[2][0] = sin(y);
	this->mat[2][2] = cos(y);
}

void Matrix4x4::SetRotationZ(float z)
{
	this->SetIdentity();
	this->mat[0][0] = cos(z);
	this->mat[0][1] = sin(z);
	this->mat[1][0] = -sin(z);
	this->mat[1][1] = cos(z);
}

void Matrix4x4::operator*=(const Matrix4x4& matrix)
{
	Matrix4x4 out;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			out.mat[i][j] = 
				(this->mat[i][0] * matrix.mat[0][j]) + (this->mat[i][1] * matrix.mat[1][j]) +
				(this->mat[i][2] * matrix.mat[2][j]) + (this->mat[i][3] * matrix.mat[3][j]);
		}
	}

	this->SetMatrix(out);
}

void Matrix4x4::SetMatrix(const Matrix4x4& matrix)
{
	::memcpy(this->mat, matrix.mat, sizeof(float) * 16);
}
