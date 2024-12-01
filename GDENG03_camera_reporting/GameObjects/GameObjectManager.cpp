#include "GameObjectManager.h"
#include "../EngineTime/EngineTime.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../GraphicsEngine/ShaderLibrary.h"
#include "../SceneCamera/SceneCameraHandler.h"
#include "RenderQueue.h"
#include "Cube.h"
#include "Sphere.h"
#include "Quad.h"
#include "GameCamera.h"
#include "MeshObject.h"
#include "PhysicsCube.h"
#include "PhysicsQuad.h"

GameObjectManager* GameObjectManager::instance = NULL;

void GameObjectManager::Initialize()
{
	instance = new GameObjectManager();
}

void GameObjectManager::Update()
{
	if (!instance->gameObjects.empty())
	{
		for (GameObject* gameObject : instance->gameObjects)
			if (gameObject->GetEnabled()) gameObject->Update(EngineTime::GetDeltaTime());
	}
}

void GameObjectManager::Destroy()
{
	if (!instance->gameObjects.empty())
	{
		for (int i = instance->gameObjects.size() - 1; i >= 0; i--)
			instance->gameObjects[i]->Destroy();

		instance->gameObjectMap.clear();
		instance->gameObjects.clear();
	}

	delete instance;
}

GameObject* GameObjectManager::CreateGameObject(PrimitiveType primitiveType, bool textured)
{
	GameObject* gameObject = NULL;

	void* shaderBytes = nullptr;
	size_t shaderSize = 0;

	ShaderLibrary::GetMeshLayout(&shaderBytes, &shaderSize);

	switch (primitiveType)
	{
	case QUAD:
	{
		gameObject = new Quad("Quad", shaderBytes, shaderSize);
		break;
	}
	case CUBE:
	{
		gameObject = new Cube("Cube", shaderBytes, shaderSize);
		break;
	}
	case SPHERE:
	{
		gameObject = new Sphere("Sphere", shaderBytes, shaderSize);
		break;
	}
	case CAMERA:
	{
		gameObject = SceneCameraHandler::AddGameCamera(shaderBytes, shaderSize);
		break;
	}
	case MESH:
	{
		gameObject = new MeshObject("Mesh", shaderBytes, shaderSize);
		break;
	}
	case PHYSICS_CUBE:
	{
		gameObject = new PhysicsCube("PhysicsCube", shaderBytes, shaderSize);
		break;
	}
	case PHYSICS_QUAD:
	{
		gameObject = new PhysicsQuad("PhysicsQuad", shaderBytes, shaderSize);
		break;
	}
	default:
		break;
	}

	VertexShader* vertexShader = ShaderLibrary::GetVertexShader(L"VertexShader.hlsl");
	PixelShader* pixelShader;

	if (textured) pixelShader = ShaderLibrary::GetPixelShader(L"TexturePixelShader.hlsl");
	else pixelShader = ShaderLibrary::GetPixelShader(L"PixelShader.hlsl");

	gameObject->SetVertexShader(vertexShader);
	gameObject->SetPixelShader(pixelShader);

	std::string name = gameObject->GetName();
	std::string num = "";

	int i = 1;
	bool added = false;

	while (!added)
	{
		if (instance->gameObjectMap.find(name + num) == instance->gameObjectMap.end())
		{
			gameObject->SetName(name + num);
			instance->AddGameObject(gameObject);
			added = true;
		}
		else
		{
			num = "_" + std::to_string(i);
			i++;
		}
	}

	return gameObject;
}

void GameObjectManager::AddGameObject(GameObject* gameObject)
{
	instance->gameObjects.push_back(gameObject);
	instance->gameObjectMap[gameObject->GetName()] = gameObject;
	RenderQueue::AddRenderer(gameObject);
	gameObject->Awake();
	gameObject->Recalculate();
}

void GameObjectManager::DeleteGameObject(GameObject* gameObject)
{
	if (instance->gameObjects.empty()) return;

	List::iterator it = instance->gameObjects.begin();

	while (it != instance->gameObjects.end() && *it != gameObject) it++;

	if (*it == gameObject)
	{
		if (instance->selectedObject == gameObject)
			instance->selectedObject = NULL;

		RenderQueue::RemoveRenderer(gameObject);
		instance->gameObjectMap.erase(gameObject->GetName());
		instance->gameObjects.erase(it);
		gameObject->Destroy();
	}
}

void GameObjectManager::DeleteGameObject(std::string name)
{
	if (instance->gameObjects.empty()) return;

	List::iterator it = instance->gameObjects.begin();

	while (it != instance->gameObjects.end() && (*it)->GetName() != name) it++;
	
	GameObject* gameObject = *it;
	if (gameObject && gameObject->GetName() == name)
	{
		if (instance->selectedObject == gameObject)
			instance->selectedObject = NULL;

		RenderQueue::RemoveRenderer(gameObject);
		instance->gameObjectMap.erase(name);
		instance->gameObjects.erase(it);
		gameObject->Destroy();
	}
}

void GameObjectManager::DeleteAllGameObjects()
{
	while (instance->gameObjects.size() > 0)
	{
		instance->DeleteGameObject(instance->gameObjects[0]);
	}

}

void GameObjectManager::SetSelectedObject(std::string name)
{
	instance->selectedObject = instance->gameObjectMap[name];
}

void GameObjectManager::SetSelectedObject(GameObject* gameObject)
{
	instance->selectedObject = gameObject;
}

GameObject* GameObjectManager::GetSelectedObject()
{
	return instance->selectedObject;
}

GameObject* GameObjectManager::FindGameObject(std::string name)
{
	return instance->gameObjectMap[name];
}

const std::vector<GameObject*>& GameObjectManager::GetGameObjects()
{
	return instance->gameObjects;
}

void GameObjectManager::SetObjectName(std::string name, std::string newName)
{
	GameObject* gameObject = instance->gameObjectMap[name];
	gameObject->SetName(newName);
	instance->gameObjectMap.erase(name);
	instance->gameObjectMap[newName] = gameObject;

	std::cout << "Renamed object: " << name << " to name: " << newName << "\n";
}

void GameObjectManager::SaveEditStates()
{

}

void GameObjectManager::RestoreEditStates()
{

}

GameObjectManager::GameObjectManager()
{

}

GameObjectManager::~GameObjectManager()
{

}
