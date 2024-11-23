#include "ShaderLibrary.h"
#include "GraphicsEngine.h"
#include "iostream"

ShaderLibrary* ShaderLibrary::instance = NULL;

void ShaderLibrary::Initialize()
{
    instance = new ShaderLibrary();

    void* shaderBytes = nullptr;
    size_t shaderSize = 0;

    RequestVertexShaderData(L"VertexMeshLayout.hlsl", &shaderBytes, &shaderSize);

    ::memcpy(instance->meshLayoutBytes, shaderBytes, shaderSize);
    instance->meshLayoutSize = shaderSize;
}

void ShaderLibrary::Destroy()
{
    for (auto it = instance->activeVS.begin(); it != instance->activeVS.end(); it++)
        it->second->Release();
    
    for (auto it = instance->activePS.begin(); it != instance->activePS.end(); it++)
        it->second->Release();

    instance->activeVS.clear();
    instance->activePS.clear();

    delete instance;
}

void ShaderLibrary::RequestVertexShaderData(std::wstring vsPath, void** shaderBytes, size_t* shaderSize)
{
    GraphicsEngine::CompileVertexShader(vsPath.c_str(), "vsmain", shaderBytes, shaderSize);
}

void ShaderLibrary::GetMeshLayout(void** shaderBytes, size_t* shaderSize)
{
    *shaderBytes = instance->meshLayoutBytes;
    *shaderSize = instance->meshLayoutSize;
}

VertexShader* ShaderLibrary::GetVertexShader(std::wstring vsPath)
{
    if (instance->activeVS.find(vsPath) != instance->activeVS.end())
        return instance->activeVS[vsPath];

    void* shaderBytes = nullptr;
    size_t shaderSize = 0;

    if (GraphicsEngine::CompileVertexShader(vsPath.c_str(), "vsmain", &shaderBytes, &shaderSize))
    {
        VertexShader* vertexShader = GraphicsEngine::CreateVertexShader(shaderBytes, shaderSize);
        GraphicsEngine::ReleaseCompiledShader();

        instance->activeVS[vsPath] = vertexShader;
        return vertexShader;
    }
    else return NULL;
}

PixelShader* ShaderLibrary::GetPixelShader(std::wstring psPath)
{
    if (instance->activePS.find(psPath) != instance->activePS.end())
        return instance->activePS[psPath];

    void* shaderBytes = nullptr;
    size_t shaderSize = 0;

    if (GraphicsEngine::CompilePixelShader(psPath.c_str(), "psmain", &shaderBytes, &shaderSize))
    {
        PixelShader* pixelShader = GraphicsEngine::CreatePixelShader(shaderBytes, shaderSize);
        GraphicsEngine::ReleaseCompiledShader();

        instance->activePS[psPath] = pixelShader;
        return pixelShader;
    }
    else return NULL;
}

ShaderLibrary::ShaderLibrary()
{

}

ShaderLibrary::~ShaderLibrary()
{
    
}
