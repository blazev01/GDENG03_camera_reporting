#include "DepthStencilState.h"
#include "GraphicsEngine.h"

DepthStencilState::DepthStencilState()
{
	this->dsState = NULL;
}

DepthStencilState::~DepthStencilState()
{

}

bool DepthStencilState::Load()
{
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = true;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	if (FAILED(GraphicsEngine::GetDevice()->CreateDepthStencilState(&dsDesc, &this->dsState)))
		return false;

	return true;
}

bool DepthStencilState::LoadDrawMask()
{
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};

	dsDesc.DepthEnable = false;
	//dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	//dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

	dsDesc.StencilEnable = true;
	dsDesc.StencilReadMask = 0xFF;
	dsDesc.StencilWriteMask = 0xFF;

	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_INCR_SAT;

	dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_NEVER;
	dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;

	if (FAILED(GraphicsEngine::GetDevice()->CreateDepthStencilState(&dsDesc, &this->dsState)))
		return false;

	return true;
}

bool DepthStencilState::LoadApplyMask()
{
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};

	dsDesc.DepthEnable = true;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	//dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

	dsDesc.StencilEnable = true;
	dsDesc.StencilReadMask = 0xFF;
	dsDesc.StencilWriteMask = 0xFF;

	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_LESS;
	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;

	dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_NEVER;
	dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;

	if (FAILED(GraphicsEngine::GetDevice()->CreateDepthStencilState(&dsDesc, &this->dsState)))
		return false;

	return true;
}

bool DepthStencilState::Release()
{
	this->dsState->Release();
	delete this;

	return true;
}
