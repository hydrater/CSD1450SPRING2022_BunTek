#pragma once
#include <AEEngine.h>
#include <iostream>
#include <stdio.h>
#include "GameScript.h"
#include "Devtools.h"
using namespace std;

#define EventManager _eventManager::Instance()
#define SceneManager _sceneManager::Instance()
#define GameScriptManager _gameScriptManager::Instance()
#define DeltaTime (float)AEFrameRateControllerGetFrameTime()

enum class TransitionType : short
{
    None = 0,
    FadeToBlack = 1
};

class _eventManager
{
private:
    static _eventManager* instance;
    _eventManager(void);
    ~_eventManager(void);

public:
    static _eventManager& Instance(void);
};

template<typename T>
class IEvent
{
public:
    virtual ~IEvent();

    virtual void Subscribe(T listener);

    virtual bool Unsubscribe(T listener);

    virtual void Notify() = 0;

protected:
    vector<T> listeners;
};

class Scene
{
public:
    virtual void Start(void);
    virtual void EarlyUpdate(void);
    virtual void Update(void);
    virtual void LateUpdate(void);
};

class _sceneManager
{
private:
    static _sceneManager* instance;
    _sceneManager(void);
    ~_sceneManager(void);
    Scene* scene, *nextScene;
    bool notStarted, notAwake, transitioning, transitionInDone, transitionDone;
    float transitionTimer;
    const float transitionStageDuration = 0.3f;
    const float transitionDuration = 0.1f;
    TransitionType currentTransitionTypes;
    AEGfxVertexList* transitionMesh;
    float transitionTransparency;

public:
    static _sceneManager& Instance(void);
    void LoadScene(Scene* newScene, TransitionType TransitionType);
    Scene* GetScene(void);
    void EarlyUpdate(void);
    void Update(void);
    void LateUpdate(void);
    void FadeToBlack(void);
};

class _gameScriptManager
{
private:
    static _gameScriptManager* instance;
    _gameScriptManager(void);
    ~_gameScriptManager(void);
    vector<GameScript*> gameScriptList;

public:
    static _gameScriptManager& Instance(void);
    void AddToList(GameScript* gameScript);
    void Update(void);
    void ClearList(void);
};