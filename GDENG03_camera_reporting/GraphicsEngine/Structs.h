#pragma once
#include "../Math/Matrix4x4.h"
#include "../Math/Vector2D.h"

struct Vertex
{
	Vector3D position;
	Vector2D texcoord;
	Vector4D albedo;
};

__declspec(align(16))
struct Constant
{
	Matrix4x4 world;
	Matrix4x4 view;
	Matrix4x4 proj;
	float time;
};
