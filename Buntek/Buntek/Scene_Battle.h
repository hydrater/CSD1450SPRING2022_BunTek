#pragma once
#include "System.h"
#include "UI_Hp.h"

class Scene_Battle : public Scene
{
public:
    void Start(void) override;
    void Update(void) override;
    GameObject* BattleManager = 0;

    GameObject* EnemyHPBar = 0;
    GameObject* SelfHPBar = 0;

    float EnemyHp = 100;
    float SelfHP = 100;

private:
    ~Scene_Battle(void) override;
    
};
