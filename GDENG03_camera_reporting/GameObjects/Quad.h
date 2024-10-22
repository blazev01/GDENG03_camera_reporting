#pragma once
#include "GameObject.h"
#include "../GraphicsEngine/VertexBuffer.h"
#include "../GraphicsEngine/ConstantBuffer.h"

class Quad : public GameObject
{
public:
	Quad(std::string name, void* shaderBytes, size_t shaderSize);
	~Quad();

	void Update(float deltaTime) override;
	void Draw() override;
	void Release() override;

private:
	VertexBuffer* vertexBuffer;
	ConstantBuffer* constantBuffer;
	float ticks = 0.0f;
	float deltaTime = 0.0f;
};

