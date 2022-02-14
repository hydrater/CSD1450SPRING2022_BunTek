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
    FadeTransition = 1
};

enum class TransitionStage : short
{
    TransitionStart = 0,
    TransitionIn = 1,
    TransitionScene = 2,
    TransitionOut = 3,
};

class Scene
{
public:
    virtual void Start(void);
    virtual void EarlyUpdate(void);
    virtual void Update(void);
    virtual void LateUpdate(void);
    virtual ~Scene() = default;
};

class _sceneManager
{
private:
    _sceneManager(void);
    ~_sceneManager(void);
    Scene* scene, *nextScene;
    bool notStarted, notAwake, transitioning;
    float transitionTimer = 0, loadingTimer = 0;
    const float transitionStageDuration = 0.5f;
    const float loadingTimerDuration = 1.0f;
    TransitionType currentTransitionTypes;
    TransitionStage currentTransitionStage;
    AEGfxVertexList* transitionMesh;
    float transitionTransparency;
    bool deleteScene = true;
    bool ResetScene(void);

public:
    static _sceneManager& Instance(void);
    void LoadScene(Scene* newScene, TransitionType TransitionType, bool deleteCurrScene);
    Scene* GetScene(void);
    void EarlyUpdate(void);
    void Update(void);
    void LateUpdate(void);
    void FadeTransition(void);
};

class _gameScriptManager
{
private:
    _gameScriptManager(void);
    ~_gameScriptManager(void);
    vector<GameScript*> gameScriptList;

public:
    static _gameScriptManager& Instance(void);
    void AddToList(GameScript* gameScript);
    void Update(void);
    void Clear(void);
};
