#include "AppWindow.h"
#include "Windows.h"
#include "../GraphicsEngine/GraphicsEngine.h"
#include "../EngineTime/EngineTime.h"
#include "../InputSystem/InputSystem.h"

AppWindow::AppWindow()
{
	this->swapChain = NULL;
	this->vertexShader = NULL;
	this->pixelShader = NULL;
	this->quad = NULL;
	this->cube = NULL;
}

AppWindow::~AppWindow()
{

}

void AppWindow::OnCreate()
{
	InputSystem::Initialize();
	InputSystem::AddListener(this);

	GraphicsEngine::GetInstance()->Init();
	this->swapChain = GraphicsEngine::GetInstance()->CreateSwapChain();

	RECT rect = this->GetWindowRect();
	this->swapChain->Init(this->hwnd, rect.right - rect.left, rect.bottom - rect.top);

	void* shaderBytes = nullptr;
	size_t shaderSize = 0;

	GraphicsEngine::GetInstance()->CompileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderBytes, &shaderSize);
	this->vertexShader = GraphicsEngine::GetInstance()->CreateVertexShader(shaderBytes, shaderSize);

	this->vsBytes = shaderBytes;
	this->vsSize = shaderSize;

	GraphicsEngine::GetInstance()->CompilePixelShader(L"PixelShader.hlsl", "psmain", &shaderBytes, &shaderSize);
	this->pixelShader = GraphicsEngine::GetInstance()->CreatePixelShader(shaderBytes, shaderSize);

	GraphicsEngine::GetInstance()->ReleaseCompiledShader();

	this->quad = new Quad("kwad", this->vsBytes, this->vsSize);

	this->cube = new Cube("coob", this->vsBytes, this->vsSize);
	this->cube->SetAnimationSpeed(5.0f);
	this->cube->SetPosition(0.5f, 0.2f, 0.0f);
	this->cube->SetScale(Vector3(0.8f));

	this->SpawnCircles();
}

void AppWindow::OnUpdate()
{
	InputSystem::Update();

	//this->deltaRot += EngineTime::GetDeltaTime();
	//this->cube->SetRotation(Vector3(-0.1f * (1.0f - this->deltaRot)) + (0.1f * this->deltaRot));
	this->cube->SetRotation(Vector3(this->rotX, this->rotY, 0.0f));
	this->cube->Update(EngineTime::GetDeltaTime());
	this->quad->Update(EngineTime::GetDeltaTime());

	if (this->spawn)
	{
		this->spawn = false;
		this->SpawnCircles();
	}

	else if (this->despawn)
	{
		this->despawn = false;
		this->DespawnCircles();
	}

	else if (this->despawnAll)
	{
		this->despawnAll = false;
		this->DespawnAllCircles();
	}

	if (!this->circles.empty())
	{
		for (int i = 0; i < this->circles.size(); i++)
			this->circles[i]->Update(EngineTime::GetDeltaTime());
	}
}

void AppWindow::OnRender()
{
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->ClearRenderTargetColor(this->swapChain, 0.0f, 0.0f, 0.0f, 0.0f);

	RECT rect = this->GetWindowRect();
	GraphicsEngine::GetInstance()->GetImmediateDeviceContext()->SetViewportSize(rect.right - rect.left, rect.bottom - rect.top);

	float width = (this->GetWindowRect().right - this->GetWindowRect().left) / 300.0f;
	float height = (this->GetWindowRect().bottom - this->GetWindowRect().top) / 300.0f;

	//this->cube->Draw(width, height, this->vertexShader, this->pixelShader);
	//this->quad->Draw(width, height, this->vertexShader, this->pixelShader);

	if (!this->circles.empty())
	{
		for (int i = 0; i < this->circles.size(); i++)
			this->circles[i]->Draw(width, height, this->vertexShader, this->pixelShader);
	}

	this->swapChain->Present(true);
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();
	this->swapChain->Release();
	this->vertexShader->Release();
	this->pixelShader->Release();

	this->quad->Release();
	this->cube->Release();

	if (!this->circles.empty())
	{
		for (int i = 0; i < this->circles.size(); i++)
			this->circles[i]->Release();
	}

	GraphicsEngine::GetInstance()->Release();
}

void AppWindow::OnKey(int key)
{

}

void AppWindow::OnKeyDown(int key)
{
	switch (key)
	{
	case 'W':
	{
		this->rotX += 3.14f * EngineTime::GetDeltaTime();
		break;
	}
	case 'S':
	{
		this->rotX -= 3.14f * EngineTime::GetDeltaTime();
		break;
	}
	case 'A':
	{
		this->rotY += 3.14f * EngineTime::GetDeltaTime();
		break;
	}
	case 'D':
	{
		this->rotY -= 3.14f * EngineTime::GetDeltaTime();
		break;
	}
	case VK_SPACE:
	{
		std::cout << "SPACE" << "\n";
		this->spawn = true;
		break;
	}
	case VK_BACK:
	{
		std::cout << "BACKSPACE" << "\n";
		this->despawn = true;
		break;
	}
	case VK_DELETE:
	{
		std::cout << "DELETE" << "\n";
		this->despawnAll = true;
		break;
	}
	case VK_ESCAPE:
	{
		std::cout << "ESCAPE" << "\n";
		exit(0);
		break;
	}
	default:
		break;
	}
}

void AppWindow::OnKeyUp(int key)
{

}

void AppWindow::SpawnCircles()
{
	int size = this->circles.size();
	for (int i = size; i < size + this->spawnSize; i++)
	{
		this->circles.push_back(new Circle("circle", this->vsBytes, this->vsSize));
		this->circles[i]->SetScale(Vector3(0.2f));
		this->circles[i]->SetVelocity(Vector3(sinf(rand()), sinf(rand()), 0.0f));
	}
}

void AppWindow::DespawnCircles()
{
	if (!this->circles.empty())
	{
		int size = this->circles.size();
		for (int i = size - 1; i >= size - this->spawnSize; i--)
		{
			this->circles[i]->Release();
			this->circles.pop_back();
		}
	}
}

void AppWindow::DespawnAllCircles()
{
	if (!this->circles.empty())
	{
		int size = this->circles.size();
		for (int i = size - 1; i >= 0; i--)
		{
			this->circles[i]->Release();
			this->circles.pop_back();
		}
	}
}
