#pragma once
#include "System.h"
#include "SpriteRenderer.h"

class Scene_Splash : public Scene
{
public:
    void Start(void) override;
    void Update(void) override;
private:
    GameObject* splash;
    float timer = 0;
    int cycle = 0;
    SpriteRenderer* splashRenderer;
    bool playSound = true;
};
