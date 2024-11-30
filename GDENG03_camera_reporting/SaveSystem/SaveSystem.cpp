#include "SaveSystem.h"

#include "stdio.h"
#include "json/json.h"
#include "json/forwards.h"
#include "../GameObjects/GameObjectManager.h"
#include "../Components/PhysicsComponent.h"
#include "fstream"
SaveSystem* SaveSystem::instance = NULL;
void SaveSystem::Initialize()
{
	instance = new SaveSystem();
}
SaveSystem* SaveSystem::GetInstance()
{
	return instance;
}
void SaveSystem::SaveScene()
{
	Json::Value root;
	Json::Value objectsCollection(Json::arrayValue);
	Json::Value gameObject;
	Json::Value translate;
	Json::Value rotation;
	Json::Value scale;
	
	/*gameObject["Type"] = "Cube";
	translate["X"] = 0.0f;
	translate["Y"] = 0.0f;
	translate["Z"] = 0.0f;
	gameObject["Translate"] = translate;
	rotation["X"] = 0.0f;
	rotation["Y"] = 0.0f;
	rotation["Z"] = 0.0f;
	gameObject["Rotation"] = rotation;
	scale["X"] = 1.0f;
	scale["Y"] = 1.0f;
	scale["Z"] = 1.0f;
	gameObject["Scale"] = scale;*/

	for (int i = 0; i < GameObjectManager::GetGameObjects().size(); i++)
	{
		gameObject["Name"] = GameObjectManager::GetGameObjects()[i]->GetName();
		gameObject["Type"] = GameObjectManager::GetGameObjects()[i]->GetPrimitiveTypeString();
		translate["X"] = GameObjectManager::GetGameObjects()[i]->GetTransform().GetPosition().x;
		translate["Y"] = GameObjectManager::GetGameObjects()[i]->GetTransform().GetPosition().y;
		translate["Z"] = GameObjectManager::GetGameObjects()[i]->GetTransform().GetPosition().z;
		gameObject["Translate"] = translate;
		rotation["X"] = GameObjectManager::GetGameObjects()[i]->GetTransform().GetRotation().x;
		rotation["Y"] = GameObjectManager::GetGameObjects()[i]->GetTransform().GetRotation().y;
		rotation["Z"] = GameObjectManager::GetGameObjects()[i]->GetTransform().GetRotation().z;
		gameObject["Rotation"] = rotation;
		scale["X"] = GameObjectManager::GetGameObjects()[i]->GetTransform().GetScale().x;
		scale["Y"] = GameObjectManager::GetGameObjects()[i]->GetTransform().GetScale().y;
		scale["Z"] = GameObjectManager::GetGameObjects()[i]->GetTransform().GetScale().z;
		gameObject["Scale"] = scale;
		/*std::cout << gameObject["Type"].asString() + "Physics" << std::endl;*/
		if (GameObjectManager::GetGameObjects()[i]->GetComponentOfType(Component::ComponentType::Physics, "RigidBody") != nullptr)
		{
			gameObject["Physics"] = true;
			gameObject["Gravity"] = ((PhysicsComponent*)GameObjectManager::GetGameObjects()[i]->GetComponentOfType(Component::ComponentType::Physics, "RigidBody"
			))->GetRigidBody()->isGravityEnabled();
			gameObject["Mass"] = ((PhysicsComponent*)GameObjectManager::GetGameObjects()[i]->GetComponentOfType(Component::ComponentType::Physics, "RigidBody"))->GetMass();
			gameObject["BodyType"] = ((PhysicsComponent*)GameObjectManager::GetGameObjects()[i]->GetComponentOfType(Component::ComponentType::Physics, "RigidBody"))->GetBodyType();
		}
		else
		{
			gameObject["Physics"] = false;
		}
		root.append(gameObject);
	}

	
	//objectsCollection.append(gameObject);

	std::ofstream output("SaveData\\Output.json");
	Json::StyledStreamWriter writer;
	writer.write(output, root);
	output.close();

	
	
}
void SaveSystem::LoadScene()
{
}
SaveSystem::SaveSystem()
{
}

SaveSystem::~SaveSystem()
{
}
