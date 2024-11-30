#include "GameObject.h"
#include "RenderQueue.h"

GameObject::GameObject(std::string name, PrimitiveType primitiveType)
{
    this->name = name;
    this->localPosition = Vector3D::Zero();
    this->localRotation = Vector3D::Zero();
    this->localScale = Vector3D::One();
    this->orientation.SetIdentity();
    this->transform.SetIdentity();
    this->parent = NULL;
    this->layer = 0;
    this->priority = 0;
    this->enabled = true;
    this->vertexShader = NULL;
    this->pixelShader = NULL;
    this->primitiveType = primitiveType;
}

GameObject::~GameObject()
{
    
}

void GameObject::Destroy()
{
    for (Component* component : this->components)
        component->Destroy();
}

std::string GameObject::GetName()
{
    return this->name;
}

void GameObject::SetName(std::string name)
{
    this->name = name;
}

void GameObject::SetPosition(float x, float y, float z)
{
    this->SetPosition(Vector3D(x, y, z));
}

void GameObject::SetPosition(Vector3D position)
{
    this->localPosition = position;
}

Vector3D GameObject::GetLocalPosition() const
{
    return this->localPosition;
}

void GameObject::SetScale(float x, float y, float z)
{
    this->SetScale(Vector3D(x, y, z));
}

void GameObject::SetScale(Vector3D scale)
{
    this->localScale = scale;
}

Vector3D GameObject::GetLocalScale() const
{
    return this->localScale;
}

void GameObject::SetRotation(float x, float y, float z)
{
    this->SetRotation(Vector3D(x, y, z));
}

void GameObject::SetRotation(Vector3D rotation)
{
    this->localRotation = rotation;
}

Vector3D GameObject::GetLocalRotation() const
{
    return this->localRotation;
}

void GameObject::SetTransform(const Matrix4x4& transform)
{
    this->transform.SetMatrix(transform);
    this->localPosition = this->transform.GetPosition();
}

Matrix4x4 GameObject::GetTransform() const
{
    return this->transform;
}

Matrix4x4 GameObject::GetOrientation() const
{
    return this->orientation;
}

Vector3D GameObject::GetRight()
{
    return this->transform.GetRight();
}

Vector3D GameObject::GetUp()
{
    return this->transform.GetUp();
}

Vector3D GameObject::GetForward()
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

const std::vector<GameObject*>& GameObject::GetChildren()
{
    return this->children;
}

std::string GameObject::GetPrimitiveTypeString()
{
    switch (this->primitiveType)
    {
        case CUBE:
            return "Cube";
        case CAMERA:
            return "Camera";
        case QUAD:
            return "Quad";
        case SPHERE:
            return "Sphere";
        case MESH:
            return "Mesh";
        case PHYSICS_CUBE:
            return "Physics_Cube";
        case PHYSICS_QUAD:
            return "Physics_Quad";
        case LINE:
            return "Line";
        case CIRCLE:
            return "Circle";
            
    }
}

PrimitiveType GameObject::GetPrimitiveType()
{
    return this->primitiveType;
}

bool GameObject::GetEnabled() const
{
    return this->enabled;
}

void GameObject::SetEnabled(bool enabled)
{
    this->enabled = enabled;
}

void GameObject::AttachComponent(Component* component)
{
    this->components.push_back(component);
}

void GameObject::DetachComponent(Component* component)
{
    if (this->components.empty()) return;

    std::vector<Component*>::iterator it = this->components.begin();

    while (it != this->components.end() && *it != component) it++;

    if (*it == component)
    {
        (*it)->DetachOwner();
        this->components.erase(it);
    }
}

Component* GameObject::FindComponentByName(std::string name)
{
    std::vector<Component*>::iterator it = this->components.begin();
    while (it != this->components.end() && (*it)->GetName() != name) it++;

    if (it != this->components.end() && *it &&
        (*it)->GetName() == name)
        return *it;

    return nullptr;
}

Component* GameObject::GetComponentOfType(Component::ComponentType type, std::string name)
{
    std::vector<Component*>::iterator it = this->components.begin();
    while (it != this->components.end() && (*it)->GetType() != type && (*it)->GetName() != name) it++;

    if (it != this->components.end() && *it &&
        (*it)->GetType() == type && (*it)->GetName() == name)
        return *it;

    return nullptr;
}

std::vector<Component*>& GameObject::GetComponentsOfType(Component::ComponentType type)
{
    std::vector<Component*> foundComponents;

    for (Component* component : this->components)
    {
        if (component && component->GetType() == type)
            foundComponents.push_back(component);
    }

    return foundComponents;
}

std::vector<Component*>& GameObject::GetComponentsOfTypeRecursive(Component::ComponentType type)
{
    std::vector<Component*> foundComponents = this->GetComponentsOfType(type);

    for (GameObject* child : this->children)
    {
        for (Component* component : child->GetComponentsOfTypeRecursive(type))
        {
            if (component && component->GetType() == type)
                foundComponents.push_back(component);
        }
    }

    return foundComponents;
}

const std::vector<Component*>& GameObject::GetComponents()
{
    return this->components;
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

void GameObject::Recalculate()
{
    Matrix4x4 temp;
    this->transform.SetIdentity();

    temp.SetIdentity();
    temp.SetScale(this->localScale);
    this->transform *= temp;

    temp.SetIdentity();
    temp.SetRotationZ(this->localRotation.z);
    this->transform *= temp;
    this->orientation *= temp;

    temp.SetIdentity();
    temp.SetRotationY(this->localRotation.y);
    this->transform *= temp;
    this->orientation *= temp;

    temp.SetIdentity();
    temp.SetRotationX(this->localRotation.x);
    this->transform *= temp;
    this->orientation *= temp;

    temp.SetIdentity();
    temp.SetPosition(this->localPosition);
    this->transform *= temp;
}

void GameObject::SetTransform(float array[16])
{

    Matrix4x4 matrix;
    matrix.SetIdentity();
    matrix.SetMatrix(array);

    Matrix4x4 scale;
    scale.SetIdentity();
    scale.SetScale(this->localScale);

    Matrix4x4 translation;
    translation.SetIdentity();
    translation.SetPosition(this->localPosition);

    scale *= matrix;
    translation *= scale;
    this->transform.SetMatrix(translation);
    //this->localPosition = this->transform.GetPosition();
}


