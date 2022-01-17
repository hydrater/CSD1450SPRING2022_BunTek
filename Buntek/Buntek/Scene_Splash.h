#pragma once
#include "System.h"
#include "SpriteRenderer.h"

class Scene_Splash : public Scene
{
public:
    void Start(void) override;
    void Update(void) override;
    ~Scene_Splash(void) override;
private:
    GameObject* splash;
    float timer = 0;
    int cycle = 0;
    SpriteRenderer* splashRenderer;
    bool canPlayAudio = true;
};
