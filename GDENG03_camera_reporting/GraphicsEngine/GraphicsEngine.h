#pragma once
#include "d3d11.h"
#include "d3dcompiler.h"
#include "../Resource/TextureManager.h"

class SwapChain;
class DeviceContext;
class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;
class DepthStencilState;

class GraphicsEngine
{
public:
	static bool Initialize();
	static void Release();

	static SwapChain* CreateSwapChain();
	static DeviceContext* GetImmediateDeviceContext();
	static VertexBuffer* CreateVertexBuffer();
	static IndexBuffer* CreateIndexBuffer();
	static ConstantBuffer* CreateConstantBuffer();
	static VertexShader* CreateVertexShader(const void* shaderBytes, size_t shaderByteSize);
	static PixelShader* CreatePixelShader(const void* shaderBytes, size_t shaderByteSize);
	static DepthStencilState* CreateDepthStencilState();

	static bool CompileVertexShader(const wchar_t* fileName, const char* entryPointName, void** shaderBytes, size_t* shaderSize);
	static bool CompilePixelShader(const wchar_t* fileName, const char* entryPointName, void** shaderBytes, size_t* shaderSize);
	static void ReleaseCompiledShader();

	static ID3D11Device* GetDevice();
	static IDXGIFactory* GetFactory();

private:
	GraphicsEngine();
	~GraphicsEngine();
	GraphicsEngine(GraphicsEngine const&) {};
	GraphicsEngine& operator=(GraphicsEngine const&) {};

	static GraphicsEngine* instance;

private:
	DeviceContext* immDeviceContext = NULL;

private:
	ID3D11Device* d3dDevice = NULL;
	D3D_FEATURE_LEVEL featureLevel = {};
	ID3D11DeviceContext* immContext = NULL;

private:
	IDXGIDevice* dxgiDevice = NULL;
	IDXGIAdapter* dxgiAdapter = NULL;
	IDXGIFactory* dxgiFactory = NULL;

private:
	ID3DBlob* blob = NULL;

	ID3DBlob* vsBlob = NULL;
	ID3DBlob* psBlob = NULL;
	ID3D11VertexShader* vertexShader = NULL;
	ID3D11PixelShader* pixelShader = NULL;

private:
	friend class SwapChain;
	friend class VertexBuffer;
	friend class IndexBuffer;
	friend class ConstantBuffer;
	friend class VertexShader;
	friend class PixelShader;
	friend class DepthStencilState;
};

