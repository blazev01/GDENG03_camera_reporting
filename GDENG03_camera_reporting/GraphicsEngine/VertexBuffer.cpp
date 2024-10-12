#include "VertexBuffer.h"
#include "GraphicsEngine.h"

VertexBuffer::VertexBuffer()
{
    this->vertexSize = 0;
    this->listSize = 0;

    this->buffer = NULL;
    this->layout = NULL;
}

bool VertexBuffer::Load(void* vertexList, UINT vertexSize, UINT listSize, void* shaderBytes, UINT shaderByteSize)
{
    if (this->buffer != NULL) this->buffer->Release();
    if (this->layout != NULL) this->layout->Release();

    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = vertexSize * listSize;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bufferDesc.CPUAccessFlags = 0;
    bufferDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = vertexList;

    this->vertexSize = vertexSize;
    this->listSize = listSize;

    if (FAILED(GraphicsEngine::GetInstance()->d3dDevice->CreateBuffer(&bufferDesc, &initData, &this->buffer)))
        return false;

    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR",    1, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    UINT layoutSize = ARRAYSIZE(layout);
    if (FAILED(GraphicsEngine::GetInstance()->d3dDevice->CreateInputLayout(
        layout,
        layoutSize,
        shaderBytes,
        shaderByteSize,
        &this->layout)))
        return false;

    return true;
}

UINT VertexBuffer::GetVertexListSize()
{
    return this->listSize;
}

bool VertexBuffer::Release()
{
    if (this->layout) this->layout->Release();
    if (this->buffer) this->buffer->Release();
    delete this;

    return true;
}

VertexBuffer::~VertexBuffer()
{

}
