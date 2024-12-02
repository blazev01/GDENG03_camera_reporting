#pragma once
#include "../Enum/Enums.h"
#include "../Components/PhysicsSystem.h"
#include "json/json.h"
#include "json/forwards.h"
class SaveSystem
{
public:
	static void Initialize();
	static SaveSystem* GetInstance();
	void SaveScene();
	void LoadScene();
	void AdoptionPeriod(Json::Value data);
	PrimitiveType PrimitiveTypeToEnum(int type);
	BodyType BodyTypetoEnum(std::string BodyType);
private:
	SaveSystem();
	~SaveSystem();
	SaveSystem(SaveSystem const&) {};
	SaveSystem& operator=(SaveSystem const&) {};

	static SaveSystem* instance;
};

