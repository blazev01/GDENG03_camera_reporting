#include "GameObject.h"

GameObject::GameObject(std::string name)
{
    this->name = name;
    this->localPosition = Vector3::Zero();
    this->localRotation = Vector3::Zero();
    this->localScale = Vector3::One();
    this->transform.SetIdentity();
    this->parent = NULL;
}

GameObject::~GameObject()
{

}

std::string GameObject::GetName()
{
    return this->name;
}

void GameObject::SetPosition(float x, float y, float z)
{
    this->SetPosition(Vector3(x, y, z));
}

void GameObject::SetPosition(Vector3 position)
{
    this->localPosition = position;
}

Vector3 GameObject::GetLocalPosition() const
{
    return this->localPosition;
}

void GameObject::SetScale(float x, float y, float z)
{
    this->SetScale(Vector3(x, y, z));
}

void GameObject::SetScale(Vector3 scale)
{
    this->localScale = scale;
}

Vector3 GameObject::GetLocalScale() const
{
    return this->localScale;
}

void GameObject::SetRotation(float x, float y, float z)
{
    this->SetRotation(Vector3(x, y, z));
}

void GameObject::SetRotation(Vector3 rotation)
{
    this->localRotation = rotation;
}

Vector3 GameObject::GetLocalRotation() const
{
    return this->localRotation;
}

Vector3 GameObject::GetRight()
{
    return this->transform.GetRight();
}

Vector3 GameObject::GetUp()
{
    return this->transform.GetUp();
}

Vector3 GameObject::GetForward()
{
    return this->transform.GetForward();
}

GameObject* GameObject::GetParent()
{
    return this->parent;
}

GameObject* GameObject::GetChild(int index)
{
    return this->children[index];
}

std::vector<GameObject*> GameObject::GetChildren()
{
    return this->children;
}
