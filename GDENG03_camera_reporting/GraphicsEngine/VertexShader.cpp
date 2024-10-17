#include "VertexShader.h"
#include "GraphicsEngine.h"

VertexShader::VertexShader()
{
    this->vs = NULL;
}

bool VertexShader::Init(const void* shaderBytes, size_t shaderByteSize)
{
    if (FAILED(GraphicsEngine::GetDevice()->CreateVertexShader(shaderBytes, shaderByteSize, nullptr, &this->vs)))
        return false;

    return true;
}

bool VertexShader::Release()
{
    this->vs->Release();
    delete this;

    return true;
}

VertexShader::~VertexShader()
{

}
