#include "GameObjectManager.h"
#include "../EngineTime/EngineTime.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../SceneCamera/SceneCameraHandler.h"
#include "RenderQueue.h"
#include "Cube.h"
#include "Quad.h"
#include "GameCamera.h"

GameObjectManager* GameObjectManager::instance = NULL;

void GameObjectManager::Initialize()
{
	instance = new GameObjectManager();

	GraphicsEngine::CompileVertexShader(L"VertexShader.hlsl", "vsmain", &instance->vsBytes, &instance->vsSize);
	instance->vertexShader = GraphicsEngine::CreateVertexShader(instance->vsBytes, instance->vsSize);

	void* psBytes = nullptr;
	size_t psSize = 0;

	GraphicsEngine::CompilePixelShader(L"PixelShader.hlsl", "psmain", &psBytes, &psSize);
	instance->pixelShader = GraphicsEngine::CreatePixelShader(psBytes, psSize);

	GraphicsEngine::ReleaseCompiledShader();
}

void GameObjectManager::Update()
{
	if (!instance->gameObjects.empty())
	{
		for (GameObject* gameObject : instance->gameObjects)
			gameObject->Update(EngineTime::GetDeltaTime());
	}
}

void GameObjectManager::Release()
{
	if (!instance->gameObjects.empty())
	{
		for (int i = instance->gameObjects.size() - 1; i >= 0; i--)
			instance->gameObjects[i]->Release();

		instance->gameObjectMap.clear();
		instance->gameObjects.clear();
	}
}

void GameObjectManager::CreateGameObject(PrimitiveType primitiveType)
{
	GameObject* gameObject = NULL;

	switch (primitiveType)
	{
	case GameObjectManager::QUAD:
	{
		gameObject = new Quad("Quad", instance->vsBytes, instance->vsSize);
		break;
	}
	case GameObjectManager::CUBE:
	{
		gameObject = new Cube("Cube", instance->vsBytes, instance->vsSize);
		break;
	}
	case GameObjectManager::SPHERE:
	{
		//gameObject = new Cube("Sphere", instance->vsBytes, instance->vsSize);
		break;
	}
	case GameObjectManager::GAME_CAMERA:
	{

		gameObject = SceneCameraHandler::CreateGameCamera(instance->vsBytes, instance->vsSize);
		break;
	}
	default:
		break;
	}

	if (gameObject)
	{
		gameObject->SetVertexShader(instance->vertexShader);
		gameObject->SetPixelShader(instance->pixelShader);
		instance->AddGameObject(gameObject);
		RenderQueue::AddRenderer(gameObject);
	}
}

void GameObjectManager::AddGameObject(GameObject* gameObject)
{
	instance->gameObjects.push_back(gameObject);
	instance->gameObjectMap[gameObject->GetName()] = gameObject;
}

void GameObjectManager::DeleteGameObject(GameObject* gameObject)
{
	if (instance->gameObjects.empty()) return;

	List::iterator it = instance->gameObjects.begin();

	while (it != instance->gameObjects.end() && *it != gameObject) it++;

	if (*it == gameObject)
	{
		instance->gameObjectMap[gameObject->GetName()] = NULL;
		(*it)->Release();
		instance->gameObjects.erase(it);
	}
}

void GameObjectManager::DeleteGameObject(std::string name)
{
	if (instance->gameObjects.empty()) return;

	List::iterator it = instance->gameObjects.begin();

	while (it != instance->gameObjects.end() && (*it)->GetName() != name) it++;

	if ((*it)->GetName() == name)
	{
		(*it)->Release();
		instance->gameObjects.erase(it);
		instance->gameObjectMap[name] = NULL;
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

GameObjectManager::GameObjectManager()
{

}

GameObjectManager::~GameObjectManager()
{

}
