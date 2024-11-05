#include "GameObject.h"
#include "RenderQueue.h"

GameObject::GameObject(std::string name)
{
    this->name = name;
    this->localPosition = Vector3::Zero();
    this->localRotation = Vector3::Zero();
    this->localScale = Vector3::One();
    this->transform.SetIdentity();
    this->parent = NULL;
    this->layer = 0;
    this->priority = 0;
    this->enabled = true;
    this->vertexShader = NULL;
    this->pixelShader = NULL;
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

void GameObject::SetTransform(const Matrix4x4& transform)
{
    this->transform.SetMatrix(transform);
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

bool GameObject::IsEnabled() const
{
    return this->enabled;
}

void GameObject::setEnabled(bool enabled)
{
    this->enabled = enabled;
}

unsigned int GameObject::GetLayer() const
{
    return this->layer;
}

void GameObject::SetLayer(unsigned int layer)
{
    this->layer = layer;
}

int GameObject::GetPriority() const
{
    return this->priority;
}

void GameObject::SetPriority(int priority)
{
    this->priority = priority;
    RenderQueue::SortByPriority();
}

PixelShader* GameObject::GetPixelShader()
{
    return this->pixelShader;
}

VertexShader* GameObject::GetVertexShader()
{
    return this->vertexShader;
}

void GameObject::SetPixelShader(PixelShader* pixelShader)
{
    this->pixelShader = pixelShader;
}

void GameObject::SetVertexShader(VertexShader* vertexShader)
{
    this->vertexShader = vertexShader;
}



