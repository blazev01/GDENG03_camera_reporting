#pragma once
#include "../Enum/Enums.h"
#include "../Components/PhysicsSystem.h"
class SaveSystem
{
public:
	static void Initialize();
	static SaveSystem* GetInstance();
	void SaveScene();
	void LoadScene();
	PrimitiveType PrimitiveTypeToEnum(int type);
	BodyType BodyTypetoEnum(std::string BodyType);
private:
	SaveSystem();
	~SaveSystem();
	SaveSystem(SaveSystem const&) {};
	SaveSystem& operator=(SaveSystem const&) {};

	static SaveSystem* instance;
};

