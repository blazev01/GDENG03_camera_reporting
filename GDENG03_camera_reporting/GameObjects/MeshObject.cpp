#include "MeshObject.h"
#include "../GraphicsEngine/Structs.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../SceneCamera/SceneCameraHandler.h"
#include "../Resource/TextureManager.h"
#include "../Resource/MeshManager.h"
#include "../Resource/TextureManager.h"
#include "../GraphicsEngine/ShaderLibrary.h"

MeshObject::MeshObject(std::string name, void* shaderBytes, size_t shaderSize) : GameObject(name)
{
	Constant cc = Constant();
	cc.time = 0;

	this->constantBuffer = GraphicsEngine::CreateConstantBuffer();
	this->constantBuffer->Load(&cc, sizeof(Constant));
}

MeshObject::~MeshObject()
{

}

void MeshObject::Update(float deltaTime)
{

}

void MeshObject::Draw(Matrix4x4 view, Matrix4x4 proj)
{
	Constant cc = Constant();
	cc.time = this->ticks;
	cc.world = this->transform;
	cc.view = view;
	cc.proj = proj;

	this->constantBuffer->Update(GraphicsEngine::GetImmediateDeviceContext(), &cc);
	GraphicsEngine::GetImmediateDeviceContext()->SetConstantBuffer(this->vertexShader, this->constantBuffer);
	GraphicsEngine::GetImmediateDeviceContext()->SetConstantBuffer(this->pixelShader, this->constantBuffer);

	GraphicsEngine::GetImmediateDeviceContext()->SetVertexShader(this->vertexShader);
	GraphicsEngine::GetImmediateDeviceContext()->SetPixelShader(this->pixelShader);

	if (this->texture)
	{
		GraphicsEngine::GetImmediateDeviceContext()->SetTexture(this->vertexShader, this->texture);
		GraphicsEngine::GetImmediateDeviceContext()->SetTexture(this->pixelShader, this->texture);
	}

	if (this->mesh)
	{
		GraphicsEngine::GetImmediateDeviceContext()->SetVertexBuffer(this->mesh->GetVertexBuffer());
		GraphicsEngine::GetImmediateDeviceContext()->SetIndexBuffer(this->mesh->GetIndexBuffer());

		GraphicsEngine::GetImmediateDeviceContext()->DrawIndexedTriangleList(this->mesh->GetIndexBuffer()->GetIndexListSize(), 0, 0);
	}
}

void MeshObject::Destroy()
{
	GameObject::Destroy();

	delete this;
}

void MeshObject::SetMesh(Mesh* mesh)
{
	this->mesh = mesh;
}

void MeshObject::SetTexture(Texture * texture)
{
	this->texture = texture;
}
