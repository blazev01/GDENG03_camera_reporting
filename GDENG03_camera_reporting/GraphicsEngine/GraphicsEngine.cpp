#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "DepthStencilState.h"

GraphicsEngine* GraphicsEngine::instance = NULL;

bool GraphicsEngine::Initialize()
{
	instance = new GraphicsEngine();

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
			&instance->d3dDevice,
			&instance->featureLevel,
			&instance->immContext);

		if (SUCCEEDED(result)) break;
	}

	if (FAILED(result)) return false;

	instance->d3dDevice->QueryInterface(_uuidof(IDXGIDevice), (void**)&instance->dxgiDevice);
	instance->dxgiDevice->GetParent(_uuidof(IDXGIAdapter), (void**)&instance->dxgiAdapter);
	instance->dxgiAdapter->GetParent(_uuidof(IDXGIFactory), (void**)&instance->dxgiFactory);

	instance->immDeviceContext = new DeviceContext(instance->immContext);

	return true;
}

void GraphicsEngine::Release()
{
	instance->dxgiDevice->Release();
	instance->dxgiAdapter->Release();
	instance->dxgiFactory->Release();

	instance->immDeviceContext->Release();
	instance->d3dDevice->Release();
}

SwapChain* GraphicsEngine::CreateSwapChain()
{
	return new SwapChain();
}

DeviceContext* GraphicsEngine::GetImmediateDeviceContext()
{
	return instance->immDeviceContext;
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
	if (FAILED(::D3DCompileFromFile(fileName, nullptr, nullptr, entryPointName, "vs_5_0", 0, 0, &instance->blob, &errblob)))
	{
		if (errblob) errblob->Release();
		return false;
	}

	*shaderBytes = instance->blob->GetBufferPointer();
	*shaderSize = instance->blob->GetBufferSize();

	return true;
}

bool GraphicsEngine::CompilePixelShader(const wchar_t* fileName, const char* entryPointName, void** shaderBytes, size_t* shaderSize)
{
	ID3DBlob* errblob = nullptr;
	if (FAILED(::D3DCompileFromFile(fileName, nullptr, nullptr, entryPointName, "ps_5_0", 0, 0, &instance->blob, &errblob)))
	{
		if (errblob) errblob->Release();
		return false;
	}

	*shaderBytes = instance->blob->GetBufferPointer();
	*shaderSize = instance->blob->GetBufferSize();

	return true;
}

void GraphicsEngine::ReleaseCompiledShader()
{
	if (instance->blob) instance->blob->Release();
}

ID3D11Device* GraphicsEngine::GetDevice()
{
	return instance->d3dDevice;
}

IDXGIFactory* GraphicsEngine::GetFactory()
{
	return instance->dxgiFactory;
}

GraphicsEngine::GraphicsEngine()
{

}

GraphicsEngine::~GraphicsEngine()
{

}

