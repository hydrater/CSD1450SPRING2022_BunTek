#pragma once
#include "AEEngine.h"
#include <iostream>
#include <stdio.h>

using namespace std;

#define eventManager EventManager::Instance()
#define sceneManager SceneManager::Instance()

class EventManager
{
private:
    static EventManager* instance;
    EventManager();
    ~EventManager();

public:
    void Test();
    static EventManager& Instance(void);
};

class Scene
{
public:
    virtual void Awake(void);
    virtual void Start(void);
    virtual void Update(void);
    virtual void Render(void);
    virtual void Free(void);
};

class SceneManager
{
private:
    static SceneManager* instance;
    SceneManager();
    ~SceneManager();
    Scene* scene;

public:
    static SceneManager& Instance(void);

    void UpdateScene(Scene* newScene);
    Scene* CurrentScene(void);
};

class GameObject
{
public:
    void Instantiate(void);
    virtual void Update(void);
};