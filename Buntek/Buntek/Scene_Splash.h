#pragma once
#include "System.h"

class Splash : public Scene
{
public:
    void Awake(void) override;
    void Start(void) override;
    void Update(void) override;
    void Render(void) override;
    void Free(void) override;
};
