#include "TextureManager.h"

TextureManager* TextureManager::instance = NULL;
std::unordered_map<std::wstring, Texture*> TextureManager::textureCache;

TextureManager::TextureManager() : ResourceManager()
{
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr)) throw std::exception("Texture manager failed to initialize.");
}

TextureManager::~TextureManager()
{
	CoUninitialize();
}

void TextureManager::Initialize()
{
	instance = new TextureManager();
}

void TextureManager::Destroy()
{
	instance->FreeResources();

	delete instance;
}

Texture* TextureManager::LoadTexture(const std::wstring& filePath)
{
	auto it = textureCache.find(filePath);
	if (it != textureCache.end())
	{
		return it->second; 
	}

	Texture* newTexture = instance->CreateTextureFromFile(filePath.c_str());
	if (newTexture)
	{
		textureCache[filePath] = newTexture;
		return newTexture;
	}

	delete newTexture;
	return nullptr;
}

Texture* TextureManager::CreateTextureFromFile(const wchar_t* filePath)
{
	return (Texture*)instance->CreateResourceFromFile(filePath);
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
