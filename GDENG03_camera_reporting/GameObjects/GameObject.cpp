#include "GameObject.h"
#include "RenderQueue.h"
#include "../Backend/Debug.h"

//#include "../Components/PhysicsComponent.h"

#include <stack>

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

bool GameObject::GetIsLocalTransform()
{
    return this->isLocalTransform;
}

void GameObject::SetIsLocalTransform(bool isLocal)
{
    this->isLocalTransform = isLocal;
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

void GameObject::AdoptChild(GameObject* pChild)
{
    pChild->parent = this;
    children.push_back(pChild);
    this->ResolveConflictingComponents(pChild);

    std::cout << std::endl << GetName() << " Parented " << pChild->GetName() << "\n\tChildren left : ";
    for (auto child : children) {
        std::cout << child->GetName() << ", ";
    }
}

void GameObject::DisownChild(GameObject* pChild)
{
    pChild->parent = nullptr;
    children.erase(find(children.begin(), children.end(), pChild));

    std::cout << std::endl << GetName() << " Disowned " << pChild->GetName() << "\n\tChildren left : ";
    for (auto child : children) {
        std::cout << child->GetName() << ", ";
    }
}

void GameObject::ResolveConflictingComponents(GameObject* pChild)
{
    GameObject* parent = pChild;
    bool parentHasRB = false;

    // AVOID CONFLICT BY CHECKING IF PARENT HAS RB
    while (parent->GetParent() != nullptr && !parentHasRB) {
        parent = parent->GetParent();

        for (Component* comp : parent->GetComponents()) {
            if (comp->GetType() == Component::ComponentType::Physics) {
                parentHasRB = true;
                break;
            }
        }
    }

    // REMOVE THE CHILD'S RB 
    for (Component* comp : pChild->GetComponents()) {
        if (parentHasRB && comp->GetType() == Component::ComponentType::Physics) {
            pChild->DetachComponent(comp);
            //((PhysicsComponent*)comp)->Destroy();
        }
    }
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

int GameObject::GetPrimitiveTypeInt()
{
    switch (this->primitiveType)
    {
        case QUAD:
            return 0;
        case CUBE:
            return 1;
        case SPHERE:
            return 2;
        case CYLINDER:
            return 3;
        case CAMERA:
            return 4;
        case MESH:
            return 5;
        case PHYSICS_CUBE:
            return 6;
        case PHYSICS_QUAD:
            return 7;
        case LINE:
            return 8;
        case CIRCLE:
            return 9;
            
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
    GameObject* it = this;
    while (it->GetParent() != nullptr) {
        it = it->GetParent();
        enabled = enabled && it->GetEnabled();
    }
    
    this->enabled = enabled;


    for (int i = 0; i < children.size(); i++) {
        children[i]->SetEnabled(enabled);
    }
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

Texture* GameObject::GetTexture()
{
    return this->texture;
}

void GameObject::SetTexture(Texture* tex)
{
    this->texture = tex;
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


    // ADDITIONALS FOR PARENTING
    this->ApplyParentTransforms();  // MODIFIES THE TRANSFORM
    this->RecalculateChildren();
}

void GameObject::RecalculateChildren()
{
    if (this->children.empty())
        return;

    for (int i = 0; i < children.size(); i++) {
        children[i]->Recalculate();
    }
}

void GameObject::ApplyParentTransforms()
{
    if (isLocalTransform) {
        return;
    }

    std::stack<Matrix4x4> parentTransforms;

    GameObject* it = this;
    while (it->GetParent() != nullptr) {
        parentTransforms.push(it->GetParent()->GetTransform());
        it = it->GetParent();
    }

    while (!parentTransforms.empty()) {
        this->transform *= parentTransforms.top();
        parentTransforms.pop();
    }
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


