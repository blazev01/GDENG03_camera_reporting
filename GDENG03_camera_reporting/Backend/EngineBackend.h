#pragma once
class EngineBackend
{
public:
	static void Initialize();
	static void Destroy();

	enum EditorMode
	{
		EDITOR = 0,
		PLAY = 1,
		PAUSED = 2
	};

	static void SetEditorMode(EditorMode mode);
	static void StartFrameStep();
	static void EndFrameStep();
	static bool InsideFrameStep();
	static EditorMode GetMode();

private:
	EngineBackend();
	~EngineBackend();
	EngineBackend(EngineBackend const&) {};
	EngineBackend& operator=(EngineBackend const&) {};

	static EngineBackend* instance;

	EditorMode editorMode = EditorMode::EDITOR;

	bool frameStepping = false;

};

