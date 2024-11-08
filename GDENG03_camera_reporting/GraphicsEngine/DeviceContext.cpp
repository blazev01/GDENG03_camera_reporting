#include "DeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "DepthStencilState.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* deviceContext)
{
    this->deviceContext = deviceContext;
}

void DeviceContext::ClearRenderTargetColor(SwapChain* swapChain, float r, float g, float b, float a)
{
    FLOAT clearColor[] = {r, g, b, a};
    this->deviceContext->ClearRenderTargetView(swapChain->rtv, clearColor);
    this->deviceContext->ClearDepthStencilView(swapChain->dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
    this->deviceContext->OMSetRenderTargets(1, &swapChain->rtv, swapChain->dsv);
}

void DeviceContext::ClearRenderTargetColor(ID3D11RenderTargetView* rtv, ID3D11DepthStencilView* dsv, float r, float g, float b, float a)
{
    FLOAT clearColor[] = { r, g, b, a };
    this->deviceContext->ClearRenderTargetView(rtv, clearColor);
    this->deviceContext->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
    this->deviceContext->OMSetRenderTargets(1, &rtv, dsv);
}

void DeviceContext::SetVertexBuffer(VertexBuffer * vertexBuffer)
{
    UINT stride = vertexBuffer->vertexSize;
    UINT offset = 0;
    this->deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer->buffer, &stride, &offset);
    this->deviceContext->IASetInputLayout(vertexBuffer->layout);
}

void DeviceContext::SetIndexBuffer(IndexBuffer* indexBuffer)
{
    this->deviceContext->IASetIndexBuffer(indexBuffer->buffer, DXGI_FORMAT_R32_UINT, 0);
}

void DeviceContext::DrawTriangleList(UINT vertexCount, UINT vertexStartIndex)
{
    this->deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    this->deviceContext->Draw(vertexCount, vertexStartIndex);
}

void DeviceContext::DrawIndexedTriangleList(UINT indexCount, UINT vertexStartIndex, UINT indexStartLoc)
{
    this->deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    this->deviceContext->DrawIndexed(indexCount, indexStartLoc, vertexStartIndex);
}

void DeviceContext::DrawTriangleStrip(UINT vertexCount, UINT vertexStartIndex)
{
    this->deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    this->deviceContext->Draw(vertexCount, vertexStartIndex);
}

void DeviceContext::DrawLineList(UINT vertexCount, UINT vertexStartIndex)
{
    this->deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
    this->deviceContext->Draw(vertexCount, vertexStartIndex);
}

void DeviceContext::DrawLineStrip(UINT vertexCount, UINT vertexStartIndex)
{
    this->deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
    this->deviceContext->Draw(vertexCount, vertexStartIndex);
}

void DeviceContext::SetViewportSize(UINT width, UINT height)
{
    D3D11_VIEWPORT vp = {};
    vp.Width = width;
    vp.Height = height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    this->deviceContext->RSSetViewports(1, &vp);
}

void DeviceContext::SetVertexShader(VertexShader* vertexShader)
{
    this->deviceContext->VSSetShader(vertexShader->vs, nullptr, 0);
}

void DeviceContext::SetPixelShader(PixelShader* pixelShader)
{
    this->deviceContext->PSSetShader(pixelShader->ps, nullptr, 0);
}

void DeviceContext::SetTexture(VertexShader* vertexShader, Texture* texture)
{
    this->deviceContext->VSSetShaderResources(0, 1, &texture->srv);
}

void DeviceContext::SetTexture(PixelShader * pixelShader, Texture* texture)
{
    this->deviceContext->PSSetShaderResources(0, 1, &texture->srv);
}

void DeviceContext::SetConstantBuffer(VertexShader* vertexShader, ConstantBuffer* buffer)
{
    this->deviceContext->VSSetConstantBuffers(0, 1, &buffer->buffer);
}

void DeviceContext::SetConstantBuffer(PixelShader* pixelShader, ConstantBuffer* buffer)
{
    this->deviceContext->PSSetConstantBuffers(0, 1, &buffer->buffer);
}

void DeviceContext::SetDepthStencilState(DepthStencilState* dsState)
{
    this->deviceContext->OMSetDepthStencilState(dsState->dsState, 0);
}

ID3D11DeviceContext* DeviceContext::GetDeviceContext()
{
    return this->deviceContext;
}

bool DeviceContext::Release()
{
    this->deviceContext->Release();
    delete this;
    return true;
}

DeviceContext::~DeviceContext()
{

}
