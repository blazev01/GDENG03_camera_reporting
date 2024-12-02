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
	void UpdateKeyframe(float t, Matrix4x4 mat);
	std::vector<float> GetTimeStamps();
	
	void UpdateKeyedPos(float t, Vector3D pos);
	void UpdateKeyedRot(float t, Vector3D rot);
	void UpdateKeyedScale(float t, Vector3D scale);

	
	Vector3D GetKeyedPos(float t);
	Vector3D GetKeyedRot(float t);
	Vector3D GetKeyedScale(float t);

private:
	void RecalcKeys();

	bool isLoop = false;
	float time = 0;


	std::map<float, Vector3D> keyframePos;
	std::map<float, Vector3D> keyframeRot;
	std::map<float, Vector3D> keyframeScale;

	std::vector<float> timeStamps;
};