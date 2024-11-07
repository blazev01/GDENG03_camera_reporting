#pragma once
#include "vector"
#include "unordered_map"
#include "GameObject.h"

class GameObjectManager
{
public:
	typedef std::vector<GameObject*> List;
	typedef std::unordered_map<std::string, GameObject*> HashTable;

	enum PrimitiveType
	{
		QUAD,
		CUBE,
		SPHERE,
		GAME_CAMERA,
	};

	static void Initialize();
	static void Update();
	static void Release();

	static void CreateGameObject(PrimitiveType primitiveType);
	static void AddGameObject(GameObject* gameObject);
	static void DeleteGameObject(GameObject* gameObject);
	static void DeleteGameObject(std::string name);

	static void SetSelectedObject(std::string name);
	static void SetSelectedObject(GameObject* gameObject);
	static GameObject* GetSelectedObject();

	static GameObject* FindGameObject(std::string name);

private:
	GameObjectManager();
	~GameObjectManager();
	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator=(GameObjectManager const&) {};

	static GameObjectManager* instance;

	List gameObjects;
	HashTable gameObjectMap;
	GameObject* selectedObject = NULL;

	VertexShader* vertexShader;
	PixelShader* pixelShader;

	void* vsBytes = nullptr;
	size_t vsSize = 0;

};

