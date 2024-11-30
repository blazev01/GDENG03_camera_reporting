#pragma once
#include "vector"
#include "unordered_map"
#include "GameObject.h"
#include "../Enum/Enums.h"
class GameObjectManager
{
public:
	typedef std::vector<GameObject*> List;
	typedef std::unordered_map<std::string, GameObject*> HashTable;

	

	static void Initialize();
	static void Update();
	static void Destroy();

	static GameObject* CreateGameObject(PrimitiveType primitiveType, bool textured = false);
	static void AddGameObject(GameObject* gameObject);
	static void DeleteGameObject(GameObject* gameObject);
	static void DeleteGameObject(std::string name);
	static void DeleteAllGameObjects();

	static void SetSelectedObject(std::string name);
	static void SetSelectedObject(GameObject* gameObject);
	static GameObject* GetSelectedObject();

	static GameObject* FindGameObject(std::string name);
	static const List& GetGameObjects();
	static void SetObjectName(std::string name, std::string newName);

	static void SaveEditStates();
	static void RestoreEditStates();

private:
	GameObjectManager();
	~GameObjectManager();
	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator=(GameObjectManager const&) {};

	static GameObjectManager* instance;

	List gameObjects;
	HashTable gameObjectMap;
	GameObject* selectedObject = NULL;
};

