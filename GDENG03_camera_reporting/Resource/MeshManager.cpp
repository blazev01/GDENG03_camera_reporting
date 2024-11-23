#include "MeshManager.h"

MeshManager* MeshManager::instance = NULL;

MeshManager::MeshManager() : ResourceManager()
{

}

MeshManager::~MeshManager()
{
	
}

void MeshManager::Initialize()
{
	instance = new MeshManager();

}

void MeshManager::Destroy()
{
	instance->FreeResources();

	delete instance;
}

Mesh* MeshManager::CreateMeshFromFile(const wchar_t* filePath)
{
	return (Mesh*)instance->CreateResourceFromFile(filePath);
}

Resource* MeshManager::CreateResourceFromFileConcrete(const wchar_t* filePath)
{
	Mesh* mesh = nullptr;
	try
	{
		mesh = new Mesh(filePath);
	}
	catch (...) {}

	return mesh;
}
