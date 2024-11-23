#pragma once
#include "ResourceManager.h"
#include "Texture.h"

class TextureManager : public ResourceManager
{
public:
	static void Initialize();
	static void Destroy();
	static Texture* CreateTextureFromFile(const wchar_t* filePath);

protected:
	virtual Resource* CreateResourceFromFileConcrete(const wchar_t* filePath) override;

private:
	TextureManager();
	~TextureManager();
	TextureManager(TextureManager const&) {};
	TextureManager& operator=(TextureManager const&) {};

	static TextureManager* instance;

};

