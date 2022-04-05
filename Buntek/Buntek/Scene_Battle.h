/*!*****************************************************************************
\file Scene_Battle.h
\author: Algene Tan Chuan Hong (90%)
\co-authors: Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Scene Battle Screen
*******************************************************************************/
#pragma once
#include "System.h"
#include "UI_Hp.h"

class Scene_Battle : public Scene
{
public:
    void Start(void) override;
    void EarlyUpdate(void) override;
    void Update(void) override;
    GameObject* BattleManager = 0;

    GameObject* EnemyHPBar = 0;
    GameObject* SelfHPBar = 0;

    float EnemyHp = 100;
    float SelfHP = 100;

private:
    ~Scene_Battle(void) override;
    
};
