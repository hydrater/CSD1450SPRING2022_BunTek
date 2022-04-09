/*!*****************************************************************************
\file Scene_Splash.h
\author: Algene Tan Chuan Hong (90%)
\co-authors: Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Scene Splash Screen
*******************************************************************************/
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
    GameObject* splash = 0;
    Vector2 splashTargetScale = Vector2(1.35f,1.35f);
    GameObject* splash2 = 0;
    Vector2 splash2TargetScale = Vector2(1.3f, 1.3f);
    GameObject* loading = 0;
    float timer = 0;
    float timer2 = 0;
    float loadingtextsize = 48;
    int cycle = 0;
    int colorType = 0;
    SpriteRenderer* splashRenderer = 0, *splashRenderer2 = 0;
    Transform* splashTransform = 0, *splashTransform2 = 0;
    bool canPlayAudio = true, resetSplash = true, skip = false;
};
