#pragma once
#include "ResourceManager.h"
#include "Mesh.h"

class MeshManager : public ResourceManager
{
public:
	static void Initialize();
	static void Destroy();
	static Mesh* CreateMeshFromFile(const wchar_t* filePath);

protected:
	virtual Resource* CreateResourceFromFileConcrete(const wchar_t* filePath) override;

private:
	MeshManager();
	~MeshManager();
	MeshManager(MeshManager const&) {};
	MeshManager& operator=(MeshManager const&) {};

	static MeshManager* instance;

};

