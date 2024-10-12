#include "PixelShader.h"
#include "GraphicsEngine.h"

PixelShader::PixelShader()
{
    this->ps = NULL;
}

bool PixelShader::Init(const void* shaderBytes, size_t shaderByteSize)
{
    if (FAILED(GraphicsEngine::GetInstance()->d3dDevice->CreatePixelShader(shaderBytes, shaderByteSize, nullptr, &this->ps)))
        return false;

    return true;
}

bool PixelShader::Release()
{
    this->ps->Release();
    delete this;

    return true;
}

PixelShader::~PixelShader()
{

}
