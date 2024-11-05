#pragma once
#include "d3d11.h"

class SwapChain;
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
	void ClearRenderTargetColor(SwapChain* swapChain, float r, float g, float b, float a);
	void SetVertexBuffer(VertexBuffer* vertexBuffer);
	void SetIndexBuffer(IndexBuffer* indexBuffer);
	void DrawTriangleList(UINT vertexCount, UINT vertexStartIndex);
	void DrawIndexedTriangleList(UINT indexCount, UINT vertexStartIndex, UINT indexStartLoc);
	void DrawTriangleStrip(UINT vertexCount, UINT vertexStartIndex);
	void DrawLineList(UINT vertexCount, UINT vertexStartIndex);
	void DrawLineStrip(UINT vertexCount, UINT vertexStartIndex);

	void SetViewportSize(UINT width, UINT height);

	void SetVertexShader(VertexShader* vertexShader);
	void SetPixelShader(PixelShader* pixelShader);

	void SetConstantBuffer(VertexShader* vertexShader, ConstantBuffer* buffer);
	void SetConstantBuffer(PixelShader* pixelShader, ConstantBuffer* buffer);

	void SetDepthStencilState(DepthStencilState* dsState);

	ID3D11DeviceContext* GetDeviceContext();
	bool Release();
	~DeviceContext();

private:
	ID3D11DeviceContext* deviceContext;
};

