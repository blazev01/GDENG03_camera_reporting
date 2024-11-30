#include "BaseComponentSystem.h"

BaseComponentSystem* BaseComponentSystem::instance = NULL;

void BaseComponentSystem::Initialize()
{
    instance = new BaseComponentSystem();
    instance->physicsSystem = new PhysicsSystem();
    instance->rendererSystem = new RendererSystem();
}

void BaseComponentSystem::Destroy()
{
    delete instance->physicsSystem;
    delete instance->rendererSystem;
    delete instance;
}

PhysicsSystem* BaseComponentSystem::GetPhysicsSystem()
{
    return instance->physicsSystem;
}

RendererSystem* BaseComponentSystem::GetRendererSystem()
{
    return instance->rendererSystem;
}

BaseComponentSystem::BaseComponentSystem()
{
    
}

BaseComponentSystem::~BaseComponentSystem()
{

}
