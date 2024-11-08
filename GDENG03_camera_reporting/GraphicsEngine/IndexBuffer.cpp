#include "IndexBuffer.h"
#include "GraphicsEngine.h"

IndexBuffer::IndexBuffer()
{
	this->buffer = NULL;
	this->listSize = NULL;
}

bool IndexBuffer::Load(void* indexList, UINT listSize)
{
    if (this->buffer != NULL) this->buffer->Release();

    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = 4 * listSize;
    bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bufferDesc.CPUAccessFlags = 0;
    bufferDesc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = indexList;

    this->listSize = listSize;

    if (FAILED(GraphicsEngine::GetDevice()->CreateBuffer(&bufferDesc, &initData, &this->buffer)))
        return false;

	return true;
}

UINT IndexBuffer::GetIndexListSize()
{
	return this->listSize;
}

bool IndexBuffer::Release()
{
    if (this->buffer) this->buffer->Release();
    delete this;

	return true;
}

IndexBuffer::~IndexBuffer()
{

}
