#include "Window.h"
#include "../IMGUI/imgui.h"
#include "../EngineTime/EngineTime.h"
#include "../InputSystem/InputSystem.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Window::Window()
{
    this->hwnd = NULL;
    this->isRunning = false;
}

Window::~Window()
{

}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam)) {
        return true;
    }

    switch (msg)
    {
    case WM_CREATE:
    {
        Window* window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
        window->SetHWND(hwnd);
        window->OnCreate();
        break;
    }
    case WM_SETFOCUS:
    {
        Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        window->OnFocus();
        break;
    }
    case WM_KILLFOCUS:
    {
        Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        window->OnKillFocus();
        break;
    }
    case WM_DESTROY:
    {
        Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        window->OnDestroy();
        ::PostQuitMessage(0);
        break;
    }
    default:
        return ::DefWindowProc(hwnd, msg, wparam, lparam);
        break;
    }

    return NULL;
}

bool Window::Init()
{
    WNDCLASSEX wc = {};
    wc.cbClsExtra = NULL;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.cbWndExtra = NULL;
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = NULL;
    wc.lpszClassName = L"MyWindowClass";
    wc.lpszMenuName = L"";
    wc.style = NULL;
    wc.lpfnWndProc = &WndProc;

    if (!::RegisterClassEx(&wc)) return false;

    this->hwnd = ::CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        L"MyWindowClass",
        L"DirectX Application",
        WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1024,
        768,
        NULL,
        NULL,
        NULL,
        this);
    
    if (!this->hwnd) return false;

    ::ShowWindow(hwnd, SW_SHOW);
    ::UpdateWindow(this->hwnd);

    this->isRunning = true;
    
    return true;
}

bool Window::Broadcast()
{
    EngineTime::LogFrameStart();
    this->OnUpdate();

    MSG msg;

    while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    Sleep(1);
    EngineTime::LogFrameEnd();

    return false;
}

bool Window::Release()
{
    if (!::DestroyWindow(this->hwnd))
        return false;
        
    return true;
}

bool Window::IsRunning()
{
    return this->isRunning;
}

RECT Window::GetWindowRect()
{
    RECT rect;
    ::GetClientRect(this->hwnd, &rect);
    return rect;
}

void Window::SetHWND(HWND hwnd)
{
    this->hwnd = hwnd;
}

void Window::OnFocus()
{

}

void Window::OnKillFocus()
{

}

void Window::OnDestroy()
{
    this->isRunning = false;
}
