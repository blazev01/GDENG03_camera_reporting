#pragma once
#include "GameObject.h"
#include "../GraphicsEngine/VertexBuffer.h"
#include "../GraphicsEngine/ConstantBuffer.h"

class Line : public GameObject
{
public:
	Line(std::string name, void* shaderBytes, size_t shaderSize, const Vector3& startPos, const Vector3& endPos);
	~Line();

	void Update(float deltaTime) override;
	void Draw(Matrix4x4 view, Matrix4x4 proj) override;
	void Release() override;

	void SetParent(GameObject* parent);

private:
	GameObject* parent = NULL;


private:
	VertexBuffer* vertexBuffer;
	ConstantBuffer* constantBuffer;
	float ticks = 0.0f;
	float deltaTime = 0.0f;
};