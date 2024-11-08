#pragma once
#include "ResourceManager.h"
#include "Texture.h"

class TextureManager : public ResourceManager
{
public:
	TextureManager();
	~TextureManager();
	Texture* CreateTextureFromFile(const wchar_t* filePath);

protected:
	virtual Resource* CreateResourceFromFileConcrete(const wchar_t* filePath) override;
};

