#pragma once
#include "stack"
#include "EditorAction.h"

class ActionHistory
{
public:
	typedef std::stack<EditorAction*> ActionStack;

	static void Initialize();
	static void Destroy();

	static void RecordAction(GameObject* gameObject);
	static bool HasRemainingUndoActions();
	static bool HasRemainingRedoActions();
	static EditorAction* UndoAction();
	static EditorAction* RedoAction();
	static void ClearCancelled();
	static void Clear();
	
private:
	ActionHistory();
	~ActionHistory();
	ActionHistory(ActionHistory const&) {};
	ActionHistory& operator=(ActionHistory const&) {};

	static ActionHistory* instance;

	EditorAction* currentAction = NULL;
	ActionStack actionsPerformed;
	ActionStack actionsCancelled;
};

