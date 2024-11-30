#pragma once
class SaveSystem
{
public:
	static void Initialize();
	static SaveSystem* GetInstance();
	void SaveScene();
	void LoadScene();
private:
	SaveSystem();
	~SaveSystem();
	SaveSystem(SaveSystem const&) {};
	SaveSystem& operator=(SaveSystem const&) {};

	static SaveSystem* instance;
};

