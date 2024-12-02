#pragma once
#include "ResourceManager.h"
#include <unordered_map>
#include "Texture.h"

class TextureManager : public ResourceManager
{
public:
	static void Initialize();
	static void Destroy();
	static Texture* LoadTexture(const std::wstring& filePath);
	static Texture* CreateTextureFromFile(const wchar_t* filePath);

protected:
	virtual Resource* CreateResourceFromFileConcrete(const wchar_t* filePath) override;

private:
	TextureManager();
	~TextureManager();
	TextureManager(TextureManager const&) {};
	TextureManager& operator=(TextureManager const&) {};

	static TextureManager* instance;
	static std::unordered_map<std::wstring, Texture*> textureCache;

};

