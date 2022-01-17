#pragma once
#include "System.h"

class Scene_Navigation : public Scene
{
public:
    void Start(void) override;
    void EarlyUpdate(void) override;
    void Update(void) override;
    void LateUpdate(void) override;
private:
    ~Scene_Navigation(void);
    GameObject* inputHandler = 0, *background = 0;
    AEGfxVertexList* mesh = 0;
};
