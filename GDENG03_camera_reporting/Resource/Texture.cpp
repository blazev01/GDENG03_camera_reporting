#include "Texture.h"
#include "DirectXTex.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "iostream"

Texture::Texture(const wchar_t* fullPath) : Resource(fullPath)
{
	std::cout << "Loading texture..." << "\n";

	DirectX::ScratchImage imageData;
	HRESULT hr = DirectX::LoadFromWICFile(fullPath, DirectX::WIC_FLAGS_NONE, nullptr, imageData);

	if (SUCCEEDED(hr))
	{
		hr = DirectX::CreateTexture(
			GraphicsEngine::GetDevice(),
			imageData.GetImages(),
			imageData.GetImageCount(),
			imageData.GetMetadata(),
			&this->texture);

		D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
		desc.Format = imageData.GetMetadata().format;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipLevels = imageData.GetMetadata().mipLevels;
		desc.Texture2D.MostDetailedMip = 0;

		GraphicsEngine::GetDevice()->CreateShaderResourceView(this->texture, &desc, &this->srv);
		std::cout << "Texture loaded." << "\n";
	}
	else
	{
		//std::cout << "FAILED TO LOAD TEXTURE." << "\n";
		throw std::exception("FAILED TO LOAD TEXTURE.");
	}
}

Texture::~Texture()
{
	if (this->texture) this->texture->Release();
	if (this->srv) this->srv->Release();
}

ID3D11ShaderResourceView* Texture::GetSRV()
{
	return this->srv;
}
