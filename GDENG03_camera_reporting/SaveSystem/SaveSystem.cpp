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
		gameObject["Type"] = GameObjectManager::GetGameObjects()[i]->GetPrimitiveTypeInt();
		translate["X"] = GameObjectManager::GetGameObjects()[i]->GetTransform().GetPosition().x;
		translate["Y"] = GameObjectManager::GetGameObjects()[i]->GetTransform().GetPosition().y;
		translate["Z"] = GameObjectManager::GetGameObjects()[i]->GetTransform().GetPosition().z;
		gameObject["Translate"] = translate;
		rotation["X"] = GameObjectManager::GetGameObjects()[i]->GetLocalRotation().x;
		rotation["Y"] = GameObjectManager::GetGameObjects()[i]->GetLocalRotation().y;
		rotation["Z"] = GameObjectManager::GetGameObjects()[i]->GetLocalRotation().z;
		gameObject["Rotation"] = rotation;
		scale["X"] = GameObjectManager::GetGameObjects()[i]->GetLocalScale().x;
		scale["Y"] = GameObjectManager::GetGameObjects()[i]->GetLocalScale().y;
		scale["Z"] = GameObjectManager::GetGameObjects()[i]->GetLocalScale().z;
		gameObject["Scale"] = scale;
		/*std::cout << gameObject["Type"].asString() + "Physics" << std::endl;*/
		if (GameObjectManager::GetGameObjects()[i]->GetComponentOfType(Component::ComponentType::Physics, "RigidBody") != nullptr)
		{
			gameObject["Physics"] = true;
			gameObject["Gravity"] = ((PhysicsComponent*)GameObjectManager::GetGameObjects()[i]->GetComponentOfType(Component::ComponentType::Physics, "RigidBody"
			))->GetRigidBody()->isGravityEnabled();
			gameObject["Mass"] = ((PhysicsComponent*)GameObjectManager::GetGameObjects()[i]->GetComponentOfType(Component::ComponentType::Physics, "RigidBody"))->GetMass();
			gameObject["BodyType"] = ((PhysicsComponent*)GameObjectManager::GetGameObjects()[i]->GetComponentOfType(Component::ComponentType::Physics, "RigidBody"))->GetBodyType();
			//gameObject["Transform"] = ((PhysicsComponent*)GameObjectManager::GetGameObjects()[i]->GetComponentOfType(Component::ComponentType::Physics, "RigidBody"))->GetRigidBody()->getTransform();
		}
		else
		{
			gameObject["Physics"] = false;
		}
		root.append(gameObject);
	}

	
	//objectsCollection.append(gameObject);

	std::ofstream output("SaveData\\Output.json");
	if (!output.is_open()) {
		std::cout << "Could not open the file!" << std::endl;
	}
	else
	{
		Json::StyledStreamWriter writer;
		writer.write(output, root);
		
	}
	output.close();

	
	
}
void SaveSystem::LoadScene()
{
	GameObjectManager::DeleteAllGameObjects();
	Json::Value data;
	Json::CharReaderBuilder readerBuilder;
	std::string errorMsg;
	std::ifstream input("SaveData\\Output.json");
	if (!input.is_open()) {
		std::cerr << "Could not open the file!" << std::endl;
		return;
	}
	if (!Json::parseFromStream(readerBuilder, input, &data, &errorMsg))
	{
		std::cerr << "Failed to parse JSON: " << errorMsg << std::endl;
		return;
	}
	input.close();
	if (data.isArray())
	{
		for (unsigned int i = 0; i < data.size(); i++)
		{
			const Json::Value& object = data[i];
			GameObjectManager::CreateGameObject(this->PrimitiveTypeToEnum(object["Type"].asInt()));
			GameObjectManager::GetGameObjects()[i]->SetName(object["Name"].asString());
			GameObjectManager::GetGameObjects()[i]->SetScale(Vector3D(object["Scale"]["X"].asFloat(), object["Scale"]["Y"].asFloat(),
				object["Scale"]["Z"].asFloat()));		
			GameObjectManager::GetGameObjects()[i]->SetRotation(Vector3D(object["Rotation"]["X"].asFloat(), object["Rotation"]["Y"].asFloat(),
				object["Rotation"]["Z"].asFloat()));
			GameObjectManager::GetGameObjects()[i]->SetPosition(Vector3D(object["Translate"]["X"].asFloat(), object["Translate"]["Y"].asFloat(),
				object["Translate"]["Z"].asFloat()));
			GameObjectManager::GetGameObjects()[i]->Recalculate();
			if (object["Physics"].asBool())
			{
				PhysicsComponent* component = new PhysicsComponent("RigidBody", GameObjectManager::GetGameObjects()[i]);
				GameObjectManager::GetGameObjects()[i]->AttachComponent(component);
				Transform transform;
				transform.setFromOpenGL(GameObjectManager::GetGameObjects()[i]->GetTransform().GetAs1DArray());
				component->GetRigidBody()->setTransform(transform);
				component->GetRigidBody()->setType(this->BodyTypetoEnum(object["BodyType"].asString()));
			}
		}
	}

}
PrimitiveType SaveSystem::PrimitiveTypeToEnum(int type)
{
	switch (type)
	{
	case 0:
		return QUAD;
	case 1:
		return CUBE;
	case 2:
		return SPHERE;
	case 3:
		return CYLINDER;
	case 4:
		return CAMERA;
	case 5:
		return MESH;
	case 6:
		return PHYSICS_CUBE;
	case 7:
		return PHYSICS_QUAD;
	case 8:
		return LINE;
	case 9:
		return CIRCLE;
	}
}
BodyType SaveSystem::BodyTypetoEnum(std::string BodyType)
{
	if (BodyType == "Dynamic")
	{
		return BodyType::DYNAMIC;
	}
	else if (BodyType == "Kinematic")
	{
		return BodyType::KINEMATIC;
	}
	else if (BodyType == "Static")
	{
		return BodyType::STATIC;
	}

}
SaveSystem::SaveSystem()
{
}

SaveSystem::~SaveSystem()
{
}
