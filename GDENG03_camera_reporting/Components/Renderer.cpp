#include "Renderer.h"
#include "BaseComponentSystem.h"
#include "../GraphicsEngine/Structs.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../GraphicsEngine/ShaderLibrary.h"
#include "../GraphicsEngine/DeviceContext.h"
#include "../SceneCamera/SceneCameraHandler.h"
#include "../Backend/Debug.h"
#include "filesystem"

Renderer::Renderer(
    std::string name,
    GameObject* owner,
    VertexShader* vertexShader,
    PixelShader* pixelShader) :
    Component(name, ComponentType::Renderer, owner)
{
    BaseComponentSystem::GetRendererSystem()->RegisterComponent(this);

    this->vertexShader = vertexShader;
    this->pixelShader = pixelShader;

    this->cc = Constant();
    this->cc.time = 0;

    this->constantBuffer = GraphicsEngine::CreateConstantBuffer();
    this->constantBuffer->Load(&this->cc, sizeof(Constant));
}

Renderer::~Renderer()
{

}

void Renderer::Perform(float deltaTime)
{
    this->cc.time += deltaTime;
    this->constantBuffer->Update(GraphicsEngine::GetImmediateDeviceContext(), &this->cc);

    GraphicsEngine::GetImmediateDeviceContext()->SetConstantBuffer(this->vertexShader, this->constantBuffer);
    GraphicsEngine::GetImmediateDeviceContext()->SetConstantBuffer(this->pixelShader, this->constantBuffer);

    GraphicsEngine::GetImmediateDeviceContext()->SetVertexShader(this->vertexShader);
    GraphicsEngine::GetImmediateDeviceContext()->SetPixelShader(this->pixelShader);

    if (this->texture)
    {
        //GraphicsEngine::GetImmediateDeviceContext()->SetTexture(this->vertexShader, this->texture);
        //GraphicsEngine::GetImmediateDeviceContext()->SetTexture(this->pixelShader, this->texture);
    }

    if (this->mesh)
    {
        GraphicsEngine::GetImmediateDeviceContext()->SetVertexBuffer(this->mesh->GetVertexBuffer());
        GraphicsEngine::GetImmediateDeviceContext()->SetIndexBuffer(this->mesh->GetIndexBuffer());

        GraphicsEngine::GetImmediateDeviceContext()->DrawIndexedTriangleList(this->mesh->GetIndexBuffer()->GetIndexListSize(), 0, 0);
    }
}

void Renderer::Destroy()
{
    BaseComponentSystem::GetRendererSystem()->UnregisterComponent(this);
    if (this->constantBuffer) this->constantBuffer->Release();
    this->constantBuffer = nullptr;
}

void Renderer::DetachOwner()
{
    PixelShader* pixelShader = ShaderLibrary::GetPixelShader(L"PixelShader.hlsl");
    this->owner->SetPixelShader(pixelShader);

    this->owner = NULL;
    this->Destroy();
}

VertexShader* Renderer::GetVertexShader()
{
    return this->vertexShader;
}

void Renderer::SetVertexShader(VertexShader* vertexShader)
{
    this->vertexShader = vertexShader;
}

PixelShader* Renderer::GetPixelShader()
{
    return this->pixelShader;
}

void Renderer::SetPixelShader(PixelShader* pixelShader)
{
    this->pixelShader = pixelShader;
}

Mesh* Renderer::GetMesh()
{
    return this->mesh;
}

void Renderer::SetMesh(Mesh* mesh)
{
    this->mesh = mesh;
}

Texture* Renderer::GetTexture()
{
    return this->texture;
}

void Renderer::SetTexture(Texture* texture)
{
    if (this->texture != texture) {
        this->texture = texture;
        this->owner->SetTexture(this->texture);
        std::cout << "Texture assigned: " << texture << " for Renderer: " << this->owner->GetName() << std::endl;
    }
}

std::wstring Renderer::GetTextureFilePath()
{
    return this->texFilePath;
}

void Renderer::SetTextureFilePath(std::wstring path)
{
    std::wstring relativePath = L"..\\Assets\\Textures\\" + std::filesystem::path(path).filename().wstring(); 
    this->texFilePath = relativePath;

    this->texture = TextureManager::LoadTexture(relativePath);
    if (this->texture)
        std::wcout << L"Texture loaded and assigned: " << this->texFilePath << std::endl;

    else
        std::wcout << L"Failed to load texture: " << this->texFilePath << std::endl;
}

void Renderer::SetWorld(const Matrix4x4& world)
{
    this->cc.world = world;
}

void Renderer::SetView(const Matrix4x4& view)
{
    this->cc.view = view;
}

void Renderer::SetProjection(const Matrix4x4& projection)
{
    this->cc.proj = projection;
}
