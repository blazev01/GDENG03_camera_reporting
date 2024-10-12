#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "DepthStencilState.h"

GraphicsEngine::GraphicsEngine()
{
	this->dxgiDevice = NULL;
	this->dxgiAdapter = NULL;
	this->dxgiFactory = NULL;

	this->d3dDevice = NULL;
	this->featureLevel = {};
	this->immContext = NULL;
	this->immDeviceContext = NULL;

	this->blob = NULL;
	this->vsBlob = NULL;
	this->psBlob = NULL;
	this->vertexShader = NULL;
	this->pixelShader = NULL;
}

bool GraphicsEngine::Init()
{
	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};

	UINT numDriverTypes = ARRAYSIZE(driverTypes);
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	UINT numfeatureLevels = ARRAYSIZE(featureLevels);

	HRESULT result = 0;
	for (UINT i = 0; i < numDriverTypes; i++)
	{
		result = D3D11CreateDevice(
			NULL,
			driverTypes[i],
			NULL,
			NULL,
			featureLevels,
			numfeatureLevels,
			D3D11_SDK_VERSION,
			&this->d3dDevice,
			&this->featureLevel,
			&this->immContext);

		if (SUCCEEDED(result)) break;
	}

	if (FAILED(result)) return false;

	this->d3dDevice->QueryInterface(_uuidof(IDXGIDevice), (void**)&this->dxgiDevice);
	this->dxgiDevice->GetParent(_uuidof(IDXGIAdapter), (void**)&this->dxgiAdapter);
	this->dxgiAdapter->GetParent(_uuidof(IDXGIFactory), (void**)&this->dxgiFactory);

	this->immDeviceContext = new DeviceContext(this->immContext);
	
	return true;
}

bool GraphicsEngine::Release()
{
	this->dxgiDevice->Release();
	this->dxgiAdapter->Release();
	this->dxgiFactory->Release();

	this->immDeviceContext->Release();
	this->d3dDevice->Release();
	return true;
}

GraphicsEngine::~GraphicsEngine()
{

}

SwapChain* GraphicsEngine::CreateSwapChain()
{
	return new SwapChain();
}

DeviceContext* GraphicsEngine::GetImmediateDeviceContext()
{
	return this->immDeviceContext;
}

VertexBuffer* GraphicsEngine::CreateVertexBuffer()
{
	return new VertexBuffer();
}

IndexBuffer* GraphicsEngine::CreateIndexBuffer()
{
	return new IndexBuffer();
}

ConstantBuffer* GraphicsEngine::CreateConstantBuffer()
{
	return new ConstantBuffer();
}

VertexShader* GraphicsEngine::CreateVertexShader(const void* shaderBytes, size_t shaderSize)
{
	VertexShader* vs = new VertexShader();

	if (!vs->Init(shaderBytes, shaderSize))
	{
		vs->Release();
		return nullptr;
	}
		
	return vs;
}

PixelShader* GraphicsEngine::CreatePixelShader(const void* shaderBytes, size_t shaderSize)
{
	PixelShader* ps = new PixelShader();

	if (!ps->Init(shaderBytes, shaderSize))
	{
		ps->Release();
		return nullptr;
	}

	return ps;
}

DepthStencilState* GraphicsEngine::CreateDepthStencilState()
{
	return new DepthStencilState();
}

bool GraphicsEngine::CompileVertexShader(const wchar_t* fileName, const char* entryPointName, void** shaderBytes, size_t* shaderSize)
{
	ID3DBlob* errblob = nullptr;
	if (FAILED(::D3DCompileFromFile(fileName, nullptr, nullptr, entryPointName, "vs_5_0", 0, 0, &this->blob, &errblob)))
	{
		if (errblob) errblob->Release();
		return false;
	}

	*shaderBytes = this->blob->GetBufferPointer();
	*shaderSize = this->blob->GetBufferSize();

	return true;
}

bool GraphicsEngine::CompilePixelShader(const wchar_t* fileName, const char* entryPointName, void** shaderBytes, size_t* shaderSize)
{
	ID3DBlob* errblob = nullptr;
	if (FAILED(::D3DCompileFromFile(fileName, nullptr, nullptr, entryPointName, "ps_5_0", 0, 0, &this->blob, &errblob)))
	{
		if (errblob) errblob->Release();
		return false;
	}

	*shaderBytes = this->blob->GetBufferPointer();
	*shaderSize = this->blob->GetBufferSize();

	return true;
}

void GraphicsEngine::ReleaseCompiledShader()
{
	if (this->blob) this->blob->Release();
}

GraphicsEngine* GraphicsEngine::GetInstance()
{
	static GraphicsEngine engine;

	return &engine;
}
