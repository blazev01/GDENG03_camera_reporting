#include "InputSystem.h"
#include "Windows.h"

InputSystem* InputSystem::instance = NULL;

void InputSystem::Initialize()
{
    instance = new InputSystem();
}

void InputSystem::Update()
{
    if (!instance->enabled) return;

    instance->oldCursorPos = instance->cursorPos;
    ::memcpy(instance->oldKeysState, instance->keysState, sizeof(unsigned char) * 256);

    POINT currentCursorPos = {};
    ::GetCursorPos(&currentCursorPos);
    instance->cursorPos = Vector2(currentCursorPos.x, currentCursorPos.y);

    if (instance->cursorPos != instance->oldCursorPos)
    {
        std::unordered_set<InputListener*>::iterator it = instance->listenerSet.begin();
        while (it != instance->listenerSet.end())
        {
            Vector2 deltaCursorPos = instance->cursorPos - instance->oldCursorPos;

            (*it)->OnMouseMove(deltaCursorPos);
            ++it;
        }
    }

    if (::GetKeyboardState(instance->keysState))
    {
        for (unsigned int i = 0; i < 256; i++)
        {
            if (instance->keysState[i] & 0x80)
            {
                if (instance->keysState[i] != instance->oldKeysState[i])
                {
                    std::unordered_set<InputListener*>::iterator it = instance->listenerSet.begin();
                    while (it != instance->listenerSet.end())
                    {
                        switch (i)
                        {
                        case VK_LBUTTON:
                        case VK_RBUTTON:
                        case VK_MBUTTON:
                        case VK_XBUTTON1:
                        case VK_XBUTTON2:
                        { (*it)->OnMouseButtonDown(i); break; }

                        default:
                        { (*it)->OnKeyDown(i); break; }
                        }

                        ++it;
                    }
                }
                else
                {
                    std::unordered_set<InputListener*>::iterator it = instance->listenerSet.begin();
                    while (it != instance->listenerSet.end())
                    {
                        switch (i)
                        {
                        case VK_LBUTTON:
                        case VK_RBUTTON:
                        case VK_MBUTTON:
                        case VK_XBUTTON1:
                        case VK_XBUTTON2:
                        { (*it)->OnMouseButton(i); break; }

                        default:
                        { (*it)->OnKey(i); break; }
                        }

                        ++it;
                    }
                }
            }
            else
            {
                if (instance->keysState[i] != instance->oldKeysState[i])
                {
                    std::unordered_set<InputListener*>::iterator it = instance->listenerSet.begin();
                    while (it != instance->listenerSet.end())
                    {
                        switch (i)
                        {
                        case VK_LBUTTON:
                        case VK_RBUTTON:
                        case VK_MBUTTON:
                        case VK_XBUTTON1:
                        case VK_XBUTTON2:
                        { (*it)->OnMouseButtonUp(i); break; }

                        default:
                        { (*it)->OnKeyUp(i); break; }
                        }
                        ++it;
                    }
                }
            }
        }
    }
}

void InputSystem::AddListener(InputListener* listener)
{
    instance->listenerSet.insert(listener);
}

void InputSystem::RemoveListener(InputListener * listener)
{
    instance->listenerSet.erase(listener);
}

Vector2 InputSystem::GetCursorPosition()
{
    POINT currentCursorPos = {};
    ::GetCursorPos(&currentCursorPos);
    Vector2 cursorPos = Vector2(currentCursorPos.x, currentCursorPos.y);

    return cursorPos;
}

void InputSystem::SetCursorPosition(const float& x, const float& y)
{
    ::SetCursorPos(x, y);
}

void InputSystem::SetCursorPosition(const Vector2& position)
{
    ::SetCursorPos(position.x, position.y);
}

void InputSystem::ShowCursor(bool show)
{
    ::ShowCursor(show);
}

bool InputSystem::IsKey(int key)
{
    bool isKey = false;
    if (instance->keysState[key] & 0x80)
        isKey = true;

    return isKey;
}

bool InputSystem::IsKeyDown(int key)
{
    bool isKeyDown = false;
    if ((instance->keysState[key] & 0x80) &&
        instance->keysState[key] != instance->oldKeysState[key])
        isKeyDown = true;

    return isKeyDown;
}

bool InputSystem::IsKeyUp(int key)
{
    bool isKeyUp = false;
    if (!(instance->keysState[key] & 0x80) &&
        instance->keysState[key] != instance->oldKeysState[key])
        isKeyUp = true;

    return isKeyUp;
}

bool InputSystem::GetEnabled()
{
    return instance->enabled;
}

void InputSystem::SetEnabled(bool enabled)
{
    instance->enabled = enabled;
}

InputSystem::InputSystem()
{

}

InputSystem::~InputSystem()
{

}
