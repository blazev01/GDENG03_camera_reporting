#include "ConstantBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"

ConstantBuffer::ConstantBuffer()
{
    this->buffer = NULL;
}

bool ConstantBuffer::Load(void* buffer, UINT bufferSize)
{
    if (this->buffer != NULL) this->buffer->Release();

    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = bufferSize;
    bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bufferDesc.CPUAccessFlags = 0;
    bufferDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = buffer;

    if (FAILED(GraphicsEngine::GetDevice()->CreateBuffer(&bufferDesc, &initData, &this->buffer)))
        return false;

    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    return true;
}

void ConstantBuffer::Update(DeviceContext* context, void* buffer)
{
    context->GetDeviceContext()->UpdateSubresource(this->buffer, NULL, NULL, buffer, NULL, NULL);
}

bool ConstantBuffer::Release()
{
    if (this->buffer) this->buffer->Release();
    delete this;

    return true;
}

ConstantBuffer::~ConstantBuffer()
{

}
