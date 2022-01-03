#pragma once
#include "System.h"

class Scene_Navigation : public Scene
{
public:
    void Start(void) override;
    void Update(void) override;
private:
    GameObject* inputHandler;
};
