#pragma once
#include "AEEngine.h"
#include <iostream>
#include <stdio.h>

using namespace std;

#define EventManager _eventManager::Instance()
#define SceneManager _sceneManager::Instance()
#define DeltaTime AEFrameRateControllerGetFrameTime()

class _eventManager
{
private:
    static _eventManager* instance;
    _eventManager();
    ~_eventManager();

public:
    static _eventManager& Instance(void);
};

class Scene
{
public:
    virtual void Start(void);
    virtual void Update(void);
};

class _sceneManager
{
private:
    static _sceneManager* instance;
    _sceneManager();
    ~_sceneManager();
    Scene* scene;
    bool notStarted, notAwake;

public:
    static _sceneManager& Instance(void);
    void LoadScene(Scene* newScene);
    Scene* GetScene(void);
    void Update(void);
};
