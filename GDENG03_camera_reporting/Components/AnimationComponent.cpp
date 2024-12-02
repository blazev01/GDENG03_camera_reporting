#include "AnimationComponent.h"
#include "BaseComponentSystem.h"
#include "AnimationSystem.h"
#include "../GameObjects/GameObject.h"

AnimationComponent::AnimationComponent(std::string name, GameObject* owner) : Component(name, Animation, owner)
{
    BaseComponentSystem::GetAnimationSystem()->RegisterComponent(this);
    AddKeyframe();
}

AnimationComponent::~AnimationComponent()
{

}

void AnimationComponent::Perform(float deltaTime)
{
    time += deltaTime;
    if (time > timeStamps[timeStamps.size() - 1]) {
        if (isLoop)
            time = 0;
        else
            return;
    }
        
    Vector3D pos, scale, rotation;// = owner->GetTransform().GetScale();

    float prevTimestamp = 0;
    float nextTimestamp = 0;

    for (float t : timeStamps) {
        // t is before currFrame
        if (t < time) {
            prevTimestamp = t;
        }

        // t is after currFrame
        else if (t > time) {
            nextTimestamp = t;
            break;
        }
    }

    if (prevTimestamp == nextTimestamp)
        return;

    float a = (time - prevTimestamp) / (nextTimestamp - prevTimestamp);
    pos = Vector3D::Lerp(keyframeTable[prevTimestamp].GetPosition(), keyframeTable[nextTimestamp].GetPosition(), a);
    scale = Vector3D::Lerp(keyframeTable[prevTimestamp].GetScale(), keyframeTable[nextTimestamp].GetScale(), a);
    rotation = Vector3D::Lerp(keyframeTable[prevTimestamp].GetRotation(), keyframeTable[nextTimestamp].GetRotation(), a);
    
    this->owner->SetPosition(pos);
    this->owner->SetScale(scale);
    this->owner->SetRotation(rotation);

    this->owner->Recalculate();
}

void AnimationComponent::Reset()
{
    time = 0;
    this->owner->Recalculate();
}

void AnimationComponent::Destroy()
{
    BaseComponentSystem::GetAnimationSystem()->UnregisterComponent(this);
    delete this;
}

bool AnimationComponent::GetIsLoop()
{
    return this->isLoop;
}

void AnimationComponent::SetLoop(bool ToF)
{
    this->isLoop = ToF;
}


void AnimationComponent::AddKeyframe()
{
    this->keyframeTable[time] = owner->GetTransform();
    RecalcKeys();
}

void AnimationComponent::RemoveKeyframe(float t)
{
    keyframeTable.erase(t);
    RecalcKeys();
}


void AnimationComponent::UpdateTimeStamp(float oldT, float newT)
{
    this->keyframeTable[newT] = this->keyframeTable[oldT];
    RemoveKeyframe(oldT);
}

std::vector<float> AnimationComponent::GetTimeStamps()
{
    return timeStamps;
}

std::map<float, Matrix4x4> AnimationComponent::GetKeyframes()
{
    return keyframeTable;
}

void AnimationComponent::RecalcKeys()
{
    timeStamps.clear();
    for (auto it = keyframeTable.begin(); it != keyframeTable.end(); ++it)
    {
        timeStamps.push_back(it->first);
    }
}