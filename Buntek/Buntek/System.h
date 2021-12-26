#pragma once
#include "AEEngine.h"
#include <iostream>
#include <stdio.h>

using namespace std;

class EventManager
{
private:
    static EventManager* instance;
    EventManager();
    ~EventManager();

public:
    void Test();
    static EventManager& Instance();
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

class GameObject
{
public:
    void Instantiate(void);
    virtual void Update(void);
};