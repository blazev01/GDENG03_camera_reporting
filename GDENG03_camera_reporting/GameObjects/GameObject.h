#pragma once
#include "string"
#include "../GraphicsEngine/VertexShader.h"
#include "../GraphicsEngine/PixelShader.h"
#include "../Math/Matrix4x4.h"

class GameObject
{
public:
	GameObject(std::string name);
	~GameObject();

	virtual void Update(float deltaTime) = 0;
	virtual void Draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) = 0;
	virtual void Release() = 0;

	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3 position);
	Vector3 GetLocalPosition() const;
	
	void SetScale(float x, float y, float z);
	void SetScale(Vector3 scale);
	Vector3 GetLocalScale() const;
	
	void SetRotation(float x, float y, float z);
	void SetRotation(Vector3 rotation);
	Vector3 GetLocalRotation() const;

protected:
	std::string name;

	Vector3 localPosition;
	Vector3 localScale;
	Vector3 localRotation;

	Matrix4x4 transform;
};

