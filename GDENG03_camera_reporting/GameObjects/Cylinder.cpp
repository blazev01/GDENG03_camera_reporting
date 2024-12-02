#include "Cylinder.h"
#include "DirectXMath.h"

#include "../Math/Colors.h"
#include "../GraphicsEngine/Structs.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../SceneCamera/SceneCameraHandler.h"
#include "../Resource/TextureManager.h"

Cylinder::Cylinder(std::string name, void* shaderBytes, size_t shaderSize) : GameObject(name, CYLINDER)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    const int slices = 30;
    const float radius = 0.5f;
    const float height = 1.0f;

    for (int i = 0; i < slices; i++)
    {
        float theta = i * 2 * DirectX::XM_PI / slices;
        float x = radius * cosf(theta);
        float z = radius * sinf(theta);

        vertices.push_back({ { x, height / 2, z }, { (float)i / slices, 0.0f }, RGBA_WHITE });
        vertices.push_back({ { x, -height / 2, z }, { (float)i / slices, 1.0f }, RGBA_WHITE });
    }

    vertices.push_back({ { 0.0f, height / 2, 0.0f }, { 0.5f, 0.0f }, RGBA_WHITE });
    vertices.push_back({ { 0.0f, -height / 2, 0.0f }, { 0.5f, 1.0f }, RGBA_WHITE });

    for (int i = 0; i < slices; i++)
    {
        int top1 = i * 2;
        int top2 = (i * 2 + 2) % (slices * 2);
        int bottom1 = i * 2 + 1;
        int bottom2 = (i * 2 + 3) % (slices * 2);

        indices.push_back(top2);
        indices.push_back(top1);
        indices.push_back(vertices.size() - 2);

        indices.push_back(bottom2);
        indices.push_back(vertices.size() - 1);
        indices.push_back(bottom1);
    }

    for (int i = 0; i < slices; i++)
    {
        float theta = i * 2 * DirectX::XM_PI / slices;
        float x = radius * cosf(theta);
        float z = radius * sinf(theta);

        vertices.push_back({ { x, height / 2, z }, { (float)i / slices, 0.0f }, RGBA_WHITE });
        vertices.push_back({ { x, -height / 2, z }, { (float)i / slices, 1.0f }, RGBA_WHITE });
    }

    for (int i = 0; i < slices; i++)
    {
        int top1 = slices * 2 + 2 + i * 2;
        int top2 = slices * 2 + 2 + (i * 2 + 2) % (slices * 2);
        int bottom1 = slices * 2 + 2 + i * 2 + 1;
        int bottom2 = slices * 2 + 2 + (i * 2 + 3) % (slices * 2);

        indices.push_back(bottom1);
        indices.push_back(top1);
        indices.push_back(bottom2);

        indices.push_back(bottom2);
        indices.push_back(top1);
        indices.push_back(top2);
    }

    int lastTop = slices * 2 + 2 + (slices - 1) * 2;
    int firstTop = slices * 2 + 2;
    int lastBottom = slices * 2 + 2 + (slices - 1) * 2 + 1;
    int firstBottom = slices * 2 + 3;

    indices.push_back(lastBottom);
    indices.push_back(lastTop);
    indices.push_back(firstBottom);

    indices.push_back(firstBottom);
    indices.push_back(lastTop);
    indices.push_back(firstTop);

    this->vertexBuffer = GraphicsEngine::CreateVertexBuffer();
    this->indexBuffer = GraphicsEngine::CreateIndexBuffer();
    this->vertexBuffer->Load(vertices.data(), sizeof(Vertex), vertices.size(), shaderBytes, shaderSize);
    this->indexBuffer->Load(indices.data(), indices.size());

    Constant cc = Constant();
    cc.time = 0;
    this->constantBuffer = GraphicsEngine::CreateConstantBuffer();
    this->constantBuffer->Load(&cc, sizeof(Constant));
}




Cylinder::~Cylinder()
{
}

void Cylinder::Update(float deltaTime)
{
    this->deltaTime = deltaTime;
    this->deltaRot += this->deltaTime * this->speed;
}

void Cylinder::Draw(Matrix4x4 view, Matrix4x4 proj)
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

void Cylinder::Destroy()
{
    GameObject::Destroy();

    this->vertexBuffer->Release();
    this->indexBuffer->Release();
    this->constantBuffer->Release();

    delete this;
}

void Cylinder::SetAnimationSpeed(float speed)
{
    this->speed = speed;
}
