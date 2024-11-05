#include "GameObjectManager.h"
#include "../EngineTime/EngineTime.h"

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
