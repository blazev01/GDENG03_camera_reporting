#pragma once
#include "unordered_map"
#include "string"
#include "Resource.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	Resource* CreateResourceFromFile(const wchar_t* filePath);

protected:
	virtual Resource* CreateResourceFromFileConcrete(const wchar_t* filePath) = 0;

private:
	std::unordered_map<std::wstring, Resource*> resourceMap;
};

