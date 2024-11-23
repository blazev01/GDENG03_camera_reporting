#include "BaseComponentSystem.h"

BaseComponentSystem* BaseComponentSystem::instance = NULL;

void BaseComponentSystem::Initialize()
{
    instance = new BaseComponentSystem();
    instance->physicsSystem = new PhysicsSystem();
}

void BaseComponentSystem::Destroy()
{
    delete instance->physicsSystem;
    delete instance;
}

PhysicsSystem* BaseComponentSystem::GetPhysicsSystem()
{
    return instance->physicsSystem;
}

BaseComponentSystem::BaseComponentSystem()
{
    
}

BaseComponentSystem::~BaseComponentSystem()
{

}
