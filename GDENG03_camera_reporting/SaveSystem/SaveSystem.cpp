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
		if (GameObjectManager::GetGameObjects()[i]->GetComponentOfType(Component::ComponentType::Physics, "RigidBody") != nullptr)
		{
			gameObject["Physics"] = true;
			gameObject["Gravity"] = ((PhysicsComponent*)GameObjectManager::GetGameObjects()[i]->GetComponentOfType(Component::ComponentType::Physics, "RigidBody"
			))->GetRigidBody()->isGravityEnabled();
			gameObject["Mass"] = ((PhysicsComponent*)GameObjectManager::GetGameObjects()[i]->GetComponentOfType(Component::ComponentType::Physics, "RigidBody"))->GetMass();
			gameObject["BodyType"] = ((PhysicsComponent*)GameObjectManager::GetGameObjects()[i]->GetComponentOfType(Component::ComponentType::Physics, "RigidBody"))->GetBodyType();
			gameObject["Position"]["X"] = ((PhysicsComponent*)GameObjectManager::GetGameObjects()[i]->GetComponentOfType(Component::ComponentType::Physics, "RigidBody"))->GetRigidBody()->getTransform().getPosition().x;
			gameObject["Position"]["Y"] = ((PhysicsComponent*)GameObjectManager::GetGameObjects()[i]->GetComponentOfType(Component::ComponentType::Physics, "RigidBody"))->GetRigidBody()->getTransform().getPosition().y;
			gameObject["Position"]["Z"] = ((PhysicsComponent*)GameObjectManager::GetGameObjects()[i]->GetComponentOfType(Component::ComponentType::Physics, "RigidBody"))->GetRigidBody()->getTransform().getPosition().z;
			gameObject["Orientation"]["X"] = ((PhysicsComponent*)GameObjectManager::GetGameObjects()[i]->GetComponentOfType(Component::ComponentType::Physics, "RigidBody"))->GetRigidBody()->getTransform().getOrientation().x;
			gameObject["Orientation"]["Y"] = ((PhysicsComponent*)GameObjectManager::GetGameObjects()[i]->GetComponentOfType(Component::ComponentType::Physics, "RigidBody"))->GetRigidBody()->getTransform().getOrientation().y;
			gameObject["Orientation"]["Z"] = ((PhysicsComponent*)GameObjectManager::GetGameObjects()[i]->GetComponentOfType(Component::ComponentType::Physics, "RigidBody"))->GetRigidBody()->getTransform().getOrientation().z;
			gameObject["Orientation"]["W"] = ((PhysicsComponent*)GameObjectManager::GetGameObjects()[i]->GetComponentOfType(Component::ComponentType::Physics, "RigidBody"))->GetRigidBody()->getTransform().getOrientation().w;
			std::cout << "Position: " << gameObject["Position"]["X"] << ", " << gameObject["Position"]["Y"] << ", " << gameObject["Position"]["Z"] << std::endl;
			std::cout << "Orientation: " << gameObject["Orientation"]["X"] <<", " << gameObject["Orientation"]["Y"] << ", " << gameObject["Orientation"]["Z"] << ", " << gameObject["Orientation"]["W"] << std::endl;
		}
		else
		{
			gameObject["Physics"] = false;
		}
		root.append(gameObject);
	}

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
		
			if (object["Physics"].asBool())
			{
				GameObjectManager::GetGameObjects()[i]->SetPosition(Vector3D(object["Translate"]["X"].asFloat() / 2, object["Translate"]["Y"].asFloat() / 2,
					object["Translate"]["Z"].asFloat() / 2));
				GameObjectManager::GetGameObjects()[i]->Recalculate();
				PhysicsComponent* component = new PhysicsComponent("RigidBody", GameObjectManager::GetGameObjects()[i]);
				GameObjectManager::GetGameObjects()[i]->AttachComponent(component);
				Transform transform = Transform(Vector3(object["Position"]["X"].asFloat(), object["Position"]["Y"].asFloat(), object["Position"]["Z"].asFloat()), 
					Quaternion(object["Orientation"]["X"].asFloat(), object["Orientation"]["Y"].asFloat(), object["Orientation"]["Z"].asFloat(), object["Orientation"]["W"].asFloat()));
				
				component->GetRigidBody()->setTransform(transform);
				component->GetRigidBody()->setType(this->BodyTypetoEnum(object["BodyType"].asString()));
				
			}
			GameObjectManager::GetGameObjects()[i]->SetPosition(Vector3D(object["Translate"]["X"].asFloat(), object["Translate"]["Y"].asFloat(),
				object["Translate"]["Z"].asFloat() ));
			GameObjectManager::GetGameObjects()[i]->Recalculate();
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
