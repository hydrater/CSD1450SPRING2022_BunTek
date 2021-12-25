#pragma once
#include "System.h"

class Battle : public Scene
{
public:
    void Awake(void);
    void Start(void);
    void Update(void);
    void Render(void);
    void Free(void);
};
