#pragma once
#include "System.h"

class Scene_Navigation : public Scene
{
public:
    void Start(void) override;
    void EarlyUpdate(void) override;
    void Update(void) override;
private:
    ~Scene_Navigation(void);
    GameObject* inputHandler, *background;
    AEGfxVertexList* mesh = 0;
};
