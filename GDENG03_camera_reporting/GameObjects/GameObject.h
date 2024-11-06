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
	virtual void Draw() = 0;
	virtual void Release() = 0;

public:
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

	void SetTransform(const Matrix4x4& transform);

	Vector3 GetRight();
	Vector3 GetUp();
	Vector3 GetForward();

	Matrix4x4 GetTransform();
	void MultiplyTransform(Matrix4x4 transform);
	GameObject* GetParent();
	GameObject* GetChild(int index);
	std::vector<GameObject*> GetChildren();

	bool IsEnabled() const;
	void setEnabled(bool enabled);

public:
	unsigned int GetLayer() const;
	void SetLayer(unsigned int layer);

	int GetPriority() const;
	void SetPriority(int priority);

	PixelShader* GetPixelShader();
	VertexShader* GetVertexShader();

	void SetPixelShader(PixelShader* pixelShader);
	void SetVertexShader(VertexShader* vertexShader);

protected:
	std::string name;

	Vector3 localPosition;
	Vector3 localScale;
	Vector3 localRotation;

	Matrix4x4 transform;

	GameObject* parent;
	std::vector<GameObject*> children;

	unsigned int layer;
	int priority;
	bool enabled;
	
	VertexShader* vertexShader;
	PixelShader* pixelShader;
};

