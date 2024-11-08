#include "TextureManager.h"

TextureManager::TextureManager() : ResourceManager()
{

}

TextureManager::~TextureManager()
{

}

Texture* TextureManager::CreateTextureFromFile(const wchar_t* filePath)
{
	return (Texture*)this->CreateResourceFromFile(filePath);
}

Resource* TextureManager::CreateResourceFromFileConcrete(const wchar_t* filePath)
{
	Texture* tex = nullptr;
	try
	{
		tex = new Texture(filePath);
	}
	catch (...) {}
	
	return tex;
}
