#pragma once
#include "Component.h"
#include "reactphysics3d/reactphysics3d.h"

using namespace reactphysics3d;

class PhysicsComponent : public Component
{
public:
	PhysicsComponent(std::string name, GameObject* owner);
	~PhysicsComponent();

	void Perform(float deltaTime) override;
	void Reset() override;
	void Destroy() override;

	RigidBody* GetRigidBody();
	BoxShape* GetBoxShape();
	std::string GetBodyType();

	float GetMass() const;
	void SetMass(float mass);

private:
	float mass = 1000.0f;
	BoxShape* boxShape;
	RigidBody* rigidBody;
};

