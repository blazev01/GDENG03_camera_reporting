#include "ResourceManager.h"
#include "filesystem"

Resource* ResourceManager::CreateResourceFromFile(const wchar_t* filePath)
{
	std::wstring fullPath = std::filesystem::absolute(filePath);

	auto it = this->resourceMap.find(fullPath);

	if (it != this->resourceMap.end())
		return it->second;

	Resource* rawRes = this->CreateResourceFromFileConcrete(fullPath.c_str());

	if (rawRes)
	{
		this->resourceMap[fullPath] = rawRes;
		return rawRes;
	}

	return nullptr;
}

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}
