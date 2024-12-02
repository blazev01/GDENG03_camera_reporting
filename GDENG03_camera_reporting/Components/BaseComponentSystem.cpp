#include "BaseComponentSystem.h"

BaseComponentSystem* BaseComponentSystem::instance = NULL;

void BaseComponentSystem::Initialize()
{
    instance = new BaseComponentSystem();
    instance->physicsSystem = new PhysicsSystem();
    instance->rendererSystem = new RendererSystem();
    instance->animationSystem = new AnimationSystem();
}

void BaseComponentSystem::Destroy()
{
    delete instance->physicsSystem;
    delete instance->rendererSystem;
    delete instance->animationSystem;
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

AnimationSystem* BaseComponentSystem::GetAnimationSystem()
{
    return instance->animationSystem;
}

BaseComponentSystem::BaseComponentSystem()
{
    
}

BaseComponentSystem::~BaseComponentSystem()
{

}
