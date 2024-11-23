#include "TextureManager.h"

TextureManager* TextureManager::instance = NULL;

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
