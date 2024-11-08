#include "TextureManager.h"

TextureManager::TextureManager() : ResourceManager()
{
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr)) throw std::exception("Texture manager failed to initialize.");
}

TextureManager::~TextureManager()
{
	CoUninitialize();
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
