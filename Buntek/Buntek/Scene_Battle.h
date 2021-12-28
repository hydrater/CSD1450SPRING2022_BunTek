#pragma once
#include "System.h"

class Battle : public Scene
{
public:
    void Start(void) override;
    void Update(void) override;
    void Render(void) override;
    void Free(void) override;
};
