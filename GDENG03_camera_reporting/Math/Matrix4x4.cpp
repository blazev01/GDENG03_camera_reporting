#include "Matrix4x4.h"

Matrix4x4::Matrix4x4()
{}

Matrix4x4::Matrix4x4(const Matrix4x4 & matrix)
{
	this->SetMatrix(matrix);
}

Matrix4x4::~Matrix4x4()
{

}

void Matrix4x4::SetIdentity()
{
	::memset(this->mat, 0, sizeof(float) * 16);
	this->mat[0][0] = 1;
	this->mat[1][1] = 1;
	this->mat[2][2] = 1;
	this->mat[3][3] = 1;
}

void Matrix4x4::SetPosition(const Vector3& position)
{
	this->mat[3][0] = position.x;
	this->mat[3][1] = position.y;
	this->mat[3][2] = position.z;
}

void Matrix4x4::SetScale(const Vector3& scale)
{
	this->mat[0][0] = scale.x;
	this->mat[1][1] = scale.y;
	this->mat[2][2] = scale.z;
}

void Matrix4x4::SetRotationX(float x)
{
	this->mat[1][1] = cos(x);
	this->mat[1][2] = sin(x);
	this->mat[2][1] = -sin(x);
	this->mat[2][2] = cos(x);
}

void Matrix4x4::SetRotationY(float y)
{
	this->mat[0][0] = cos(y);
	this->mat[0][2] = -sin(y);
	this->mat[2][0] = sin(y);
	this->mat[2][2] = cos(y);
}

void Matrix4x4::SetRotationZ(float z)
{
	this->mat[0][0] = cos(z);
	this->mat[0][1] = sin(z);
	this->mat[1][0] = -sin(z);
	this->mat[1][1] = cos(z);
}

void Matrix4x4::SetRotation(float angle, Vector3 axis)
{
	const double pi = 3.1415926535;
	float angleRads = (angle * pi) / 180.0f;
	float a = cosf(angleRads / 2.0f);
	float b = axis.x * sinf(angleRads / 2.0f);
	float c = axis.y * sinf(angleRads / 2.0f);
	float d = axis.z * sinf(angleRads / 2.0f);

	this->mat[0][0] = { powf(a, 2) + powf(b, 2) - powf(c, 2) - powf(d, 2) };
	this->mat[0][1] = { (2 * b * c) - (2 * a * d) };
	this->mat[0][2] = { (2 * b * d) + (2 * a * c) };
	this->mat[0][3] = 0;
	this->mat[1][0] = { (2 * b * c) + (2 * a * d) };
	this->mat[1][1] = { powf(a, 2) - powf(b, 2) + powf(c, 2) - powf(d, 2) };
	this->mat[1][2] = { (2 * c * d) - (2 * a * b) };
	this->mat[1][3] = 0;
	this->mat[2][0] = { (2 * b * d) - (2 * a * c) };
	this->mat[2][1] = { (2 * c * d) + (2 * a * b) };
	this->mat[2][2] = { powf(a, 2) - powf(b, 2) - powf(c, 2) + powf(d, 2) };
	this->mat[2][3] = 0;
	this->mat[3][0] = 0;
	this->mat[3][1] = 0;
	this->mat[3][2] = 0;
	this->mat[3][3] = 1;
}

Vector3 Matrix4x4::GetPosition()
{
	return Vector3(this->mat[3][0], this->mat[3][1], this->mat[3][2]);;
}

Vector3 Matrix4x4::GetRight()
{
	return Vector3(this->mat[0][0], this->mat[1][0], this->mat[2][0]);
}

Vector3 Matrix4x4::GetUp()
{
	return Vector3(this->mat[0][1], this->mat[1][1], this->mat[2][1]);
}

Vector3 Matrix4x4::GetForward()
{
	return -Vector3(this->mat[0][2], this->mat[1][2], this->mat[2][2]);
}

void Matrix4x4::SetPerspectiveLH(float fov, float aspect, float zNear, float zFar)
{
	this->SetIdentity();
	float yscale = 1.0f / tan(fov / 2.0f);
	float xscale = yscale / aspect;
	this->mat[0][0] = xscale;
	this->mat[1][1] = yscale;
	this->mat[2][2] = zFar / (zFar - zNear);
	this->mat[2][3] = 1.0f;
	this->mat[3][2] = (-zNear * zFar) / (zFar - zNear);
}

void Matrix4x4::SetOrthoLH(float width, float height, float nearPlane, float farPlane)
{
	this->SetIdentity();
	this->mat[0][0] = 2.0f / width;
	this->mat[1][1] = 2.0f / height;
	this->mat[2][2] = 1.0f / (farPlane - nearPlane);
	this->mat[3][2] = -(nearPlane / (farPlane - nearPlane));
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

float Matrix4x4::GetDeterminant() const
{
	Vector4 minor, v1, v2, v3;
	float det;

	v1 = Vector4(this->mat[0][0], this->mat[1][0], this->mat[2][0], this->mat[3][0]);
	v2 = Vector4(this->mat[0][1], this->mat[1][1], this->mat[2][1], this->mat[3][1]);
	v3 = Vector4(this->mat[0][2], this->mat[1][2], this->mat[2][2], this->mat[3][2]);

	minor = Vector4::Cross(v1, v2, v3);
	det = -(this->mat[0][3] * minor.x + this->mat[1][3] * minor.y + this->mat[2][3] * minor.z +
		this->mat[3][3] * minor.w);
	return det;
}

void Matrix4x4::Inverse()
{
	int a, i, j;
	Matrix4x4 out;
	Vector4 v, vec[3];
	float det = 0.0f;

	det = this->GetDeterminant();
	if (!det) return;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (j != i)
			{
				a = j;
				if (j > i) a = a - 1;
				vec[a].x = (this->mat[j][0]);
				vec[a].y = (this->mat[j][1]);
				vec[a].z = (this->mat[j][2]);
				vec[a].w = (this->mat[j][3]);
			}
		}
		v = Vector4::Cross(vec[0], vec[1], vec[2]);

		out.mat[0][i] = powf(-1.0f, i) * v.x / det;
		out.mat[1][i] = powf(-1.0f, i) * v.y / det;
		out.mat[2][i] = powf(-1.0f, i) * v.z / det;
		out.mat[3][i] = powf(-1.0f, i) * v.w / det;
	}

	this->SetMatrix(out);
}

std::ostream& operator<<(std::ostream& out, const Matrix4x4& matrix4x4)
{
	out << "\n" << "{ { " << matrix4x4.mat[0][0] << ", " << matrix4x4.mat[0][1] << ", " << matrix4x4.mat[0][2] << ", " << matrix4x4.mat[0][3] << " }, " << "\n";
	out <<		   "  { " << matrix4x4.mat[1][0] << ", " << matrix4x4.mat[1][1] << ", " << matrix4x4.mat[1][2] << ", " << matrix4x4.mat[1][3] << " }, " << "\n";
	out <<		   "  { " << matrix4x4.mat[2][0] << ", " << matrix4x4.mat[2][1] << ", " << matrix4x4.mat[2][2] << ", " << matrix4x4.mat[2][3] << " }, " << "\n";
	out <<		   "  { " << matrix4x4.mat[3][0] << ", " << matrix4x4.mat[3][1] << ", " << matrix4x4.mat[3][2] << ", " << matrix4x4.mat[3][3] << " } }" << "\n";
	return out;
}
