#pragma once
#include "System.h"

class Scene_Battle : public Scene
{
public:
    void Start(void) override;
    void Update(void) override;
    GameObject* BattleManager = 0;

private:
    ~Scene_Battle(void) override;
    
};
