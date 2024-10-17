#pragma once
#include "string"
#include "vector"
#include "../GraphicsEngine/VertexShader.h"
#include "../GraphicsEngine/PixelShader.h"
#include "../Math/Matrix4x4.h"

class GameObject
{
public:
	GameObject(std::string name);
	~GameObject();

	virtual void Update(float deltaTime) = 0;
	virtual void Draw(VertexShader* vertexShader, PixelShader* pixelShader) = 0;
	virtual void Release() = 0;

	std::string GetName();

	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3 position);
	Vector3 GetLocalPosition() const;
	
	void SetScale(float x, float y, float z);
	void SetScale(Vector3 scale);
	Vector3 GetLocalScale() const;
	
	void SetRotation(float x, float y, float z);
	void SetRotation(Vector3 rotation);
	Vector3 GetLocalRotation() const;

	Vector3 GetRight();
	Vector3 GetUp();
	Vector3 GetForward();

	GameObject* GetParent();
	GameObject* GetChild(int index);
	std::vector<GameObject*> GetChildren();

protected:
	std::string name;

	Vector3 localPosition;
	Vector3 localScale;
	Vector3 localRotation;

	Matrix4x4 transform;

	GameObject* parent;
	std::vector<GameObject*> children;
};

