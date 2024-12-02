#pragma once
#include "Component.h"

#include <map>
#include <vector>
#include "../Math/Matrix4x4.h"

class AnimationComponent : public Component
{
public:
	AnimationComponent(std::string name, GameObject* owner);
	~AnimationComponent();

	void Perform(float deltaTime) override;
	void Reset() override;
	void Destroy() override;

	bool GetIsLoop();
	void SetLoop(bool ToF);

	void AddKeyframe();
	void RemoveKeyframe(float t);

	void UpdateTimeStamp(float oldT, float newT);
	std::vector<float> GetTimeStamps();
	std::map<float, Matrix4x4> GetKeyframes();

private:
	void RecalcKeys();

	bool isLoop = false;
	float time = 0;

	std::map<float, Matrix4x4> keyframeTable;
	std::vector<float> timeStamps;
};