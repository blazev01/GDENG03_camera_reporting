#include "ActionHistory.h"
#include "EngineBackend.h"

ActionHistory* ActionHistory::instance = NULL;

void ActionHistory::Initialize()
{
    instance = new ActionHistory();
}

void ActionHistory::Destroy()
{
    instance->Clear();
    delete instance;
}

void ActionHistory::RecordAction(GameObject* gameObject)
{
    if (EngineBackend::GetMode() == EngineBackend::EDITOR)
    {
        instance->actionsPerformed.push(new EditorAction(gameObject));
    }
}

bool ActionHistory::HasRemainingUndoActions()
{
    return !instance->actionsPerformed.empty();
}

bool ActionHistory::HasRemainingRedoActions()
{
    return !instance->actionsCancelled.empty();
}

EditorAction* ActionHistory::UndoAction()
{
    EditorAction* action = NULL;
    if (EngineBackend::GetMode() == EngineBackend::EDITOR)
    {
        if (instance->HasRemainingUndoActions())
        {
            action = instance->actionsPerformed.top();
            instance->actionsCancelled.push(action);
            instance->actionsPerformed.pop();
        }
    }

    return action;
}

EditorAction* ActionHistory::RedoAction()
{
    EditorAction* action = NULL;
    if (EngineBackend::GetMode() == EngineBackend::EDITOR)
    {
        if (instance->HasRemainingRedoActions())
        {
            action = instance->actionsCancelled.top();
            instance->actionsPerformed.push(action);
            instance->actionsCancelled.pop();
        }
    }

    return action;
}

void ActionHistory::Clear()
{
    while (!instance->actionsPerformed.empty())
    {
        delete instance->actionsPerformed.top();
        instance->actionsPerformed.pop();
    }

    while (!instance->actionsCancelled.empty())
    {
        delete instance->actionsCancelled.top();
        instance->actionsCancelled.pop();
    }
}

ActionHistory::ActionHistory()
{

}

ActionHistory::~ActionHistory()
{

}