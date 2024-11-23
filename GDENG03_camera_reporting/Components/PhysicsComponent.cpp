#include "PhysicsComponent.h"
#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "../GameObjects/GameObject.h"

PhysicsComponent::PhysicsComponent(std::string name, GameObject* owner) : Component(name, Physics, owner)
{
    BaseComponentSystem::GetPhysicsSystem()->RegisterComponent(this);
    PhysicsCommon* physicsCommon = BaseComponentSystem::GetPhysicsSystem()->GetPhysicsCommon();
    PhysicsWorld* physicsWorld = BaseComponentSystem::GetPhysicsSystem()->GetPhysicsWorld();

    Vector3D rot = this->owner->GetLocalRotation();
    Quaternion quat = Quaternion::fromEulerAngles(Vector3(rot.x, rot.y, rot.z));

    Vector3D pos = this->owner->GetLocalPosition();
    Transform transform = Transform(Vector3(pos.x, pos.y, pos.z), quat);

    Vector3D scale = this->owner->GetLocalScale();
    this->boxShape = physicsCommon->createBoxShape(Vector3(scale.x / 2, scale.y / 2, scale.z / 2));

    this->rigidBody = physicsWorld->createRigidBody(transform);
    this->rigidBody->addCollider(this->boxShape, transform);

    this->rigidBody->updateMassPropertiesFromColliders();
    this->rigidBody->setMass(this->mass);
    this->rigidBody->setType(BodyType::DYNAMIC);

    transform = this->rigidBody->getTransform();
    float matrix[16];
    transform.getOpenGLMatrix(matrix);
    this->owner->SetTransform(matrix);
}

PhysicsComponent::~PhysicsComponent()
{

}

void PhysicsComponent::Perform(float deltaTime)
{
    Transform transform = this->rigidBody->getTransform();
    float matrix[16];
    transform.getOpenGLMatrix(matrix);
    this->owner->SetTransform(matrix);
}

void PhysicsComponent::Destroy()
{
    BaseComponentSystem::GetPhysicsSystem()->UnregisterComponent(this);
    PhysicsWorld* physicsWorld = BaseComponentSystem::GetPhysicsSystem()->GetPhysicsWorld();
    PhysicsCommon* physicsCommon = BaseComponentSystem::GetPhysicsSystem()->GetPhysicsCommon();
    physicsWorld->destroyRigidBody(this->rigidBody);
    physicsCommon->destroyBoxShape(this->boxShape);

    delete this;
}

RigidBody* PhysicsComponent::GetRigidBody()
{
    return this->rigidBody;
}

BoxShape* PhysicsComponent::GetBoxShape()
{
    return this->boxShape;
}

float PhysicsComponent::GetMass() const
{
    return this->mass;
}

void PhysicsComponent::SetMass(float mass)
{
    this->mass = mass;
    this->rigidBody->setMass(this->mass);
}
