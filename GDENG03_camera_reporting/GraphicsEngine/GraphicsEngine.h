#pragma once
#include "d3d11.h"
#include "d3dcompiler.h"

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
	GraphicsEngine();

	bool Init();
	bool Release();

	~GraphicsEngine();

public:
	SwapChain* CreateSwapChain();
	DeviceContext* GetImmediateDeviceContext();
	VertexBuffer* CreateVertexBuffer();
	IndexBuffer* CreateIndexBuffer();
	ConstantBuffer* CreateConstantBuffer();
	VertexShader* CreateVertexShader(const void* shaderBytes, size_t shaderByteSize);
	PixelShader* CreatePixelShader(const void* shaderBytes, size_t shaderByteSize);
	DepthStencilState* CreateDepthStencilState();

public:
	bool CompileVertexShader(const wchar_t* fileName, const char* entryPointName, void** shaderBytes, size_t* shaderSize);
	bool CompilePixelShader(const wchar_t* fileName, const char* entryPointName, void** shaderBytes, size_t* shaderSize);
	void ReleaseCompiledShader();

public:
	static GraphicsEngine* GetInstance();

private:
	DeviceContext* immDeviceContext;

private:
	ID3D11Device* d3dDevice;
	D3D_FEATURE_LEVEL featureLevel;
	ID3D11DeviceContext* immContext;

private:
	IDXGIDevice* dxgiDevice;
	IDXGIAdapter* dxgiAdapter;
	IDXGIFactory* dxgiFactory;

private:
	ID3DBlob* blob;

	ID3DBlob* vsBlob;
	ID3DBlob* psBlob;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;

private:
	friend class SwapChain;
	friend class VertexBuffer;
	friend class IndexBuffer;
	friend class ConstantBuffer;
	friend class VertexShader;
	friend class PixelShader;
	friend class DepthStencilState;
};

