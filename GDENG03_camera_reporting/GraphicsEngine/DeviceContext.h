#pragma once
#include "d3d11.h"
#include "../Resource/Texture.h"

class SwapChain;
class ViewTexture;
class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;
class DepthStencilState;

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* deviceContext);
	void ClearRenderTargetColor(ID3D11RenderTargetView* rtv, ID3D11DepthStencilView* dsv, float r, float g, float b, float a);
	void ClearRenderTargetColor(SwapChain* swapChain, float r, float g, float b, float a);
	void ClearRenderTargetColor(ViewTexture* viewTexture, float r, float g, float b, float a);
	void SetVertexBuffer(VertexBuffer* vertexBuffer);
	void SetIndexBuffer(IndexBuffer* indexBuffer);
	void DrawTriangleList(UINT vertexCount, UINT vertexStartIndex);
	void DrawIndexedTriangleList(UINT indexCount, UINT vertexStartIndex, UINT indexStartLoc);
	void DrawTriangleStrip(UINT vertexCount, UINT vertexStartIndex);
	void DrawLineList(UINT vertexCount, UINT vertexStartIndex);
	void DrawLineStrip(UINT vertexCount, UINT vertexStartIndex);

	void SetViewportSize(UINT width, UINT height);
	void SetViewportSize(SwapChain* swapChain);
	void SetViewportSize(ViewTexture* viewTexture);

	void SetVertexShader(VertexShader* vertexShader);
	void SetPixelShader(PixelShader* pixelShader);

	void SetTexture(VertexShader* vertexShader, Texture* texture);
	void SetTexture(PixelShader* pixelShader, Texture* texture);

	void SetConstantBuffer(VertexShader* vertexShader, ConstantBuffer* buffer);
	void SetConstantBuffer(PixelShader* pixelShader, ConstantBuffer* buffer);

	void SetDepthStencilState(DepthStencilState* dsState);

	ID3D11DeviceContext* GetDeviceContext();
	bool Release();
	~DeviceContext();

private:
	ID3D11DeviceContext* deviceContext;

private:
	friend class ConstantBuffer;
};

