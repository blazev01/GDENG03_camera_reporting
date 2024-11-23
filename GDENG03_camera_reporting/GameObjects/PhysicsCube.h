#pragma once
#include "GameObject.h"
#include "../GraphicsEngine/VertexBuffer.h"
#include "../GraphicsEngine/IndexBuffer.h"
#include "../GraphicsEngine/ConstantBuffer.h"
#include "../Resource/Texture.h"

class PhysicsCube : public GameObject
{
public:
	PhysicsCube(std::string name, void* shaderBytes, size_t shaderSize);
	~PhysicsCube();

	void Awake() override;
	void Update(float deltaTime) override;
	void Draw(Matrix4x4 view, Matrix4x4 proj) override;
	void Destroy() override;
	void SetAnimationSpeed(float speed);

private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;
	Texture* texture;

	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaRot = 0.0f;
	float deltaTime = 0.0f;
	float speed = 1.0f;
};

