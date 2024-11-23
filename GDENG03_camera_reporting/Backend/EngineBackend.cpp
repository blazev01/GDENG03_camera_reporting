#include "EngineBackend.h"
#include "../GameObjects/GameObjectManager.h"

EngineBackend* EngineBackend::instance = nullptr;

void EngineBackend::Initialize()
{
    instance = new EngineBackend();
}

void EngineBackend::Destroy()
{
    delete instance;
}

void EngineBackend::SetEditorMode(EditorMode mode)
{
    instance->editorMode = mode;
    if (instance->editorMode == PLAY)
        GameObjectManager::SaveEditStates();
    else if (instance->editorMode == EDITOR)
        GameObjectManager::RestoreEditStates();
}

void EngineBackend::StartFrameStep()
{
    instance->frameStepping = true;
}

void EngineBackend::EndFrameStep()
{
    instance->frameStepping = false;
}

bool EngineBackend::InsideFrameStep()
{
    return instance->frameStepping;
}

EngineBackend::EditorMode EngineBackend::GetMode()
{
    return instance->editorMode;
}

EngineBackend::EngineBackend()
{

}

EngineBackend::~EngineBackend()
{

}
