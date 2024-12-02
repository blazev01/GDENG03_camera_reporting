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
    
    Vector3D pos = Vector3D::Lerp(keyframePos[prevTimestamp], keyframePos[nextTimestamp], a);
    Vector3D rotation = Vector3D::Lerp(keyframeRot[prevTimestamp], keyframeRot[nextTimestamp], a);
    Vector3D scale = Vector3D::Lerp(keyframeScale[prevTimestamp], keyframeScale[nextTimestamp], a);
    
    //pos = Vector3D::Lerp(keyframeTable[prevTimestamp].GetPosition(), keyframeTable[nextTimestamp].GetPosition(), a);
    //scale = Vector3D::Lerp(keyframeTable[prevTimestamp].GetScale(), keyframeTable[nextTimestamp].GetScale(), a);
    //rotation = Vector3D::Lerp(keyframeTable[prevTimestamp].GetRotation(), keyframeTable[nextTimestamp].GetRotation(), a);
    

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
    Matrix4x4 mat = owner->GetTransform();
    
    keyframePos[time] = mat.GetPosition();
    keyframeRot[time] = mat.GetRotation();
    keyframeScale[time] = mat.GetScale();
    
    RecalcKeys();
}

void AnimationComponent::RemoveKeyframe(float t)
{
    //keyframeTable.erase(t);
    
    keyframePos.erase(t);
    keyframeRot.erase(t);
    keyframeScale.erase(t);
    
    RecalcKeys();
}


void AnimationComponent::UpdateTimeStamp(float oldT, float newT)
{
    //this->keyframeTable[newT] = this->keyframeTable[oldT];
    
    this->keyframePos[newT] = this->keyframePos[oldT];
    this->keyframeRot[newT] = this->keyframeRot[oldT];
    this->keyframeScale[newT] = this->keyframeScale[oldT];

    RemoveKeyframe(oldT);
}

void AnimationComponent::UpdateKeyframe(float t, Matrix4x4 mat)
{
    //this->keyframeTable[t] = mat;

    keyframePos[t] = mat.GetPosition();
    keyframeRot[t] = mat.GetRotation();
    keyframeScale[t] = mat.GetScale();
}

std::vector<float> AnimationComponent::GetTimeStamps()
{
    return timeStamps;
}

void AnimationComponent::UpdateKeyedPos(float t, Vector3D pos)
{
    this->keyframePos[t] = pos;
}
void AnimationComponent::UpdateKeyedRot(float t, Vector3D rot)
{
    this->keyframeRot[t] = rot;
}
void AnimationComponent::UpdateKeyedScale(float t, Vector3D scale)
{
    this->keyframeScale[t] = scale;
}


Vector3D AnimationComponent::GetKeyedPos(float t)
{
    return this->keyframePos[t];
}

Vector3D AnimationComponent::GetKeyedRot(float t)
{
    return this->keyframeRot[t];
}

Vector3D AnimationComponent::GetKeyedScale(float t)
{
    return this->keyframeScale[t];
}

void AnimationComponent::RecalcKeys()
{
    timeStamps.clear();
    //for (auto it = keyframeTable.begin(); it != keyframeTable.end(); ++it)
    for (auto it = keyframePos.begin(); it != keyframePos.end(); ++it)
    {
        timeStamps.push_back(it->first);
    }
}