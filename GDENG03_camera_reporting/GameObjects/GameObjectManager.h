#pragma once
#include "vector"
#include "GameObject.h"

class GameObjectManager
{
public:
	static void Initialize();
	static void Update();
	static void Release();

	static void AddGameObject(GameObject* gameObject);
	static void DeleteGameObject(GameObject* gameObject);
	static void DeleteGameObject(std::string name);

	static GameObject* Find(std::string name);

private:
	GameObjectManager();
	~GameObjectManager();
	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator=(GameObjectManager const&) {};

	static GameObjectManager* instance;

	std::vector<GameObject*> gameObjects;
};

