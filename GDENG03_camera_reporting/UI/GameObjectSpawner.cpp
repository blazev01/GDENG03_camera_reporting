#include "GameObjectSpawner.h"
#include "../GameObjects/GameObjectManager.h"
#include "../GameObjects/Cube.h"
#include "../GameObjects/Cube.h"
#include "../Components/PhysicsComponent.h"

void GameObjectSpawner::SpawnPhysicsObjects()
{
	for (int i = 0; i < 10; i++)
	{
		Cube* cube = (Cube*)GameObjectManager::CreateGameObject(GameObjectManager::CUBE);
		cube->SetPosition(Vector3D(0.0f, 2.5f, 0.0f));
		PhysicsComponent* component = new PhysicsComponent("RigidBody", cube);
		cube->AttachComponent(component);
	}

	Cube* cube = (Cube*)GameObjectManager::CreateGameObject(GameObjectManager::CUBE);
	cube->SetPosition(0.0f, -2.5f, 0.0f);
	cube->SetScale(Vector3D(20.0f, 1.0f, 20.0f));
	PhysicsComponent* component = new PhysicsComponent("RigidBody", cube);
	component->GetRigidBody()->setType(BodyType::STATIC);
	cube->AttachComponent(component);
}
