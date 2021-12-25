#pragma once
#include "AEEngine.h"
#include <iostream>
using namespace std;

class Scene
{
public:
    virtual void Awake(void);
    virtual void Start(void);
    virtual void Update(void);
    virtual void Render(void);
    virtual void Free(void);
};