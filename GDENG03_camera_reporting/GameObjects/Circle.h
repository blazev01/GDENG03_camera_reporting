#pragma once
#include "GameObject.h"
#include "../GraphicsEngine/VertexBuffer.h"
#include "../GraphicsEngine/IndexBuffer.h"
#include "../GraphicsEngine/ConstantBuffer.h"

class Circle : public GameObject
{
public:
	Circle(std::string name, void* shaderBytes, size_t shaderSize);
	~Circle();

	void Update(float deltaTime) override;
	void Draw(Matrix4x4 view, Matrix4x4 proj) override;
	void Destroy() override;
	void SetVelocity(Vector3D velocity);

private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;

	float ticks = 0.0f;
	float deltaTime = 0.0f;
	float radius = 0.5f;
	Vector3D velocity;
};

