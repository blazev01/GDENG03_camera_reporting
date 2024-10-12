#include "InputSystem.h"
#include "Windows.h"

InputSystem* InputSystem::instance = NULL;

void InputSystem::Initialize()
{
    instance = new InputSystem();
}

void InputSystem::Update()
{
    if (::GetKeyboardState(instance->keysState))
    {
        for (unsigned int i = 0; i < 256; i++)
        {
            if ((instance->keysState[i] & 0x80))
            {
                if (instance->keysState[i] != instance->oldKeysState[i])
                {
                    std::unordered_set<InputListener*>::iterator it = instance->listenerSet.begin();
                    while (it != instance->listenerSet.end())
                    {
                        (*it)->OnKeyDown(i);
                        ++it;
                    }
                }
                else
                {
                    std::unordered_set<InputListener*>::iterator it = instance->listenerSet.begin();
                    while (it != instance->listenerSet.end())
                    {
                        (*it)->OnKey(i);
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
                        (*it)->OnKeyUp(i);
                        ++it;
                    }
                }
            }
        }

        ::memcpy(instance->oldKeysState, instance->keysState, sizeof(unsigned char) * 256);
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

InputSystem::InputSystem()
{

}

InputSystem::~InputSystem()
{

}
