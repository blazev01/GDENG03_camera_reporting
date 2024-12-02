#include "Sphere.h"
#include "DirectXMath.h"

#include "../Math/Colors.h"
#include "../GraphicsEngine/Structs.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../SceneCamera/SceneCameraHandler.h"
#include "../Resource/TextureManager.h"

const Vector4D WHITE(1.0f, 1.0f, 1.0f, 1.0f);
const Vector4D GREY(0.5f, 0.5f, 0.5f, 1.0f);

Sphere::Sphere(std::string name, void* shaderBytes, size_t shaderSize) : GameObject(name, SPHERE)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	const int latitudeBands = 30;
	const int longitudeBands = 30;
	const float radius = 0.5f;
	for (int latNumber = 0; latNumber <= latitudeBands; latNumber++)
	{
		float theta = latNumber * DirectX::XM_PI / latitudeBands; 
		float sinTheta = sinf(theta); 
		float cosTheta = cosf(theta);

		for (int longNumber = 0; longNumber <= longitudeBands; longNumber++)
		{
			float phi = longNumber * 2 * DirectX::XM_PI / longitudeBands;
			float sinPhi = sinf(phi);
			float cosPhi = cosf(phi);

			Vector3D position = { radius * cosPhi * sinTheta, radius * cosTheta, radius * sinPhi * sinTheta };
			Vector2D texCoord = { (float)longNumber / longitudeBands, (float)latNumber / latitudeBands };

			float blendFactor = (position.y + radius) / (2.0f * radius);

			Vector4D color = Vector4D(WHITE.x * blendFactor + GREY.x * (1 - blendFactor),
									  WHITE.y * blendFactor + GREY.y * (1 - blendFactor),
									  WHITE.z * blendFactor + GREY.z * (1 - blendFactor),
									  1.0f);
						
			vertices.push_back({ position, texCoord, color });
		}
	}

	for (int latNumber = 0; latNumber < latitudeBands; latNumber++)
	{
		for (int longNumber = 0; longNumber < longitudeBands; longNumber++)
		{
			int first = latNumber * (longitudeBands + 1) + longNumber;
			int second = first + longitudeBands + 1;

			indices.push_back(first);
			indices.push_back(first + 1);
			indices.push_back(second);

			indices.push_back(second);
			indices.push_back(first + 1);
			indices.push_back(second + 1);
		}
	}

	this->vertexBuffer = GraphicsEngine::CreateVertexBuffer();
	this->indexBuffer = GraphicsEngine::CreateIndexBuffer();
	this->vertexBuffer->Load(vertices.data(), sizeof(Vertex), vertices.size(), shaderBytes, shaderSize);
	this->indexBuffer->Load(indices.data(), indices.size());

	Constant cc = Constant();
	cc.time = 0;
	this->constantBuffer = GraphicsEngine::CreateConstantBuffer();
	this->constantBuffer->Load(&cc, sizeof(Constant));
}

Sphere::~Sphere()
{
}

void Sphere::Update(float deltaTime)
{
	this->deltaTime = deltaTime;
	this->deltaRot += this->deltaTime * this->speed;
}

void Sphere::Draw(Matrix4x4 view, Matrix4x4 proj)
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

	if (this->texture) {
		GraphicsEngine::GetImmediateDeviceContext()->SetTexture(this->vertexShader, this->texture);
		GraphicsEngine::GetImmediateDeviceContext()->SetTexture(this->pixelShader, this->texture);
	}

	GraphicsEngine::GetImmediateDeviceContext()->SetVertexBuffer(this->vertexBuffer);
	GraphicsEngine::GetImmediateDeviceContext()->SetIndexBuffer(this->indexBuffer);

	GraphicsEngine::GetImmediateDeviceContext()->DrawIndexedTriangleList(this->indexBuffer->GetIndexListSize(), 0, 0);
}

void Sphere::Destroy()
{
	GameObject::Destroy();

	this->vertexBuffer->Release();
	this->indexBuffer->Release();
	this->constantBuffer->Release();

	delete this;
}

void Sphere::SetAnimationSpeed(float speed)
{
	this->speed = speed;
}
