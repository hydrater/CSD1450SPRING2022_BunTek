#pragma once
/*!*****************************************************************************
\file Scene_GameOver.h
\author: Algene Tan Chuan Hong (90%)
\co-authors: Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Scene Credits Screen
*******************************************************************************/
#include "System.h"
#include "TextRenderer.h"
#include "SpriteRenderer.h"

class Scene_GameOver : public Scene
{
public:
    void Start(void) override;
    //void EarlyUpdate(void) override;
    void Update(void) override;
    //void LateUpdate(void) override;
    //GameObject* GetObjRef(short type);
private:
    ~Scene_GameOver(void) override;
    GameObject* header = 0, * gameOverBackground = 0;
    SpriteRenderer* gameOverFade = 0;
    float gameOverTime = 0;
    TextRenderer* gameOverTxt = 0;
};
