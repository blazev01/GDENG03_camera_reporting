#pragma once
#include "../Math/Vector4D.h"
#include "../Math/Vector3D.h"
#include "../Math/Vector2D.h"

class VertexMesh
{
public:
	VertexMesh() {}
	~VertexMesh() {}

	VertexMesh(Vector3D position, Vector2D texcoord) : position(position), texcoord(texcoord), albedo(1.0f, 0.0f, 1.0f, 1.0f) {}
	VertexMesh(const VertexMesh& vertex) : position(vertex.position), texcoord(vertex.texcoord), albedo(vertex.albedo) {}

public:
	Vector3D position;
	Vector2D texcoord;
	Vector4D albedo;
};

