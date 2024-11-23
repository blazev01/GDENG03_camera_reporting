#pragma once
#include "GameObject.h"
#include "../GraphicsEngine/VertexBuffer.h"
#include "../GraphicsEngine/ConstantBuffer.h"

class PhysicsQuad : public GameObject
{
public:
	PhysicsQuad(std::string name, void* shaderBytes, size_t shaderSize);
	~PhysicsQuad();

	void Update(float deltaTime) override;
	void Draw(Matrix4x4 view, Matrix4x4 proj) override;
	void Destroy() override;

private:
	VertexBuffer* vertexBuffer;
	ConstantBuffer* constantBuffer;
	float ticks = 0.0f;
	float deltaTime = 0.0f;
};
