#pragma once
#include "string"
#include "vector"
#include "../GraphicsEngine/VertexShader.h"
#include "../GraphicsEngine/PixelShader.h"
#include "../Resource/Texture.h"
#include "../Math/Matrix4x4.h"
#include "../Components/Component.h"
#include "../GameObjects/GameObjectManager.h"
#include "../Enum/Enums.h"

class GameObject
{
public:
	GameObject(std::string name, PrimitiveType primitiveType);
	~GameObject();

	virtual void Awake() {};
	virtual void Update(float deltaTime) = 0;
	virtual void Draw(Matrix4x4 view, Matrix4x4 proj) = 0;
	virtual void Destroy();

public:
	std::string GetName();
	void SetName(std::string name);

	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3D position);
	Vector3D GetLocalPosition() const;
	
	void SetScale(float x, float y, float z);
	void SetScale(Vector3D scale);
	Vector3D GetLocalScale() const;
	
	void SetRotation(float x, float y, float z);
	void SetRotation(Vector3D rotation);
	Vector3D GetLocalRotation() const;

	void SetTransform(const Matrix4x4& transform);
	void SetTransform(float array[16]);
	Matrix4x4 GetTransform() const;
	Matrix4x4 GetOrientation() const;

	Vector3D GetRight();
	Vector3D GetUp();
	Vector3D GetForward();

	void AdoptChild(GameObject* pChild);
	void DisownChild(GameObject* pChild);

	GameObject* GetParent();
	GameObject* GetChild(int index);
	const std::vector<GameObject*>& GetChildren();

	int GetPrimitiveTypeInt();
	PrimitiveType GetPrimitiveType();

	bool GetEnabled() const;
	void SetEnabled(bool enabled);

public:
	void AttachComponent(Component* component);
	void DetachComponent(Component* component);

	Component* FindComponentByName(std::string name);
	Component* GetComponentOfType(Component::ComponentType type, std::string name);
	std::vector<Component*>& GetComponentsOfType(Component::ComponentType type);
	std::vector<Component*>& GetComponentsOfTypeRecursive(Component::ComponentType type);
	const std::vector<Component*>& GetComponents();

public:
	unsigned int GetLayer() const;
	void SetLayer(unsigned int layer);

	int GetPriority() const;
	void SetPriority(int priority);

	Texture* GetTexture();
	void SetTexture(Texture* tex);

	PixelShader* GetPixelShader();
	VertexShader* GetVertexShader();

	void SetPixelShader(PixelShader* pixelShader);
	void SetVertexShader(VertexShader* vertexShader);

	virtual void Recalculate();

protected:
	std::string name;

	Vector3D localPosition;
	Vector3D localScale;
	Vector3D localRotation;

	Matrix4x4 orientation;
	Matrix4x4 transform;

	GameObject* parent = nullptr;
	std::vector<GameObject*> children;
	std::vector<Component*> components;

	unsigned int layer;
	int priority;
	bool enabled;
	
	Texture* texture;

	VertexShader* vertexShader;
	PixelShader* pixelShader;
	PrimitiveType primitiveType;
};

