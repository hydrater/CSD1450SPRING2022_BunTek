/*!*****************************************************************************
\file Scene_Navigation.h
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Scene Navigation Screen
*******************************************************************************/

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
    ~Scene_Navigation(void) override;
    GameObject* splashimage1 = 0;
    GameObject* splashimage2 = 0;
    GameObject* splashimage3 = 0;
    GameObject* splashimage4 = 0;
    GameObject* splashimage5 = 0;
    GameObject* splashimage6 = 0;
    GameObject* spawner = 0;
    GameObject* currentArea = 0;        //Game Object to show the radius the player can go to
    GameObject* playerLocation = 0;     //Game Object to show where the player is
    float playerLocScaleSpeed = 0.2125f, playerLocTargetScale = 1.f;
    float playerLocScale = 1;           //Scale for player location
    float playerLocTravelScale = 0.25f; //Scale set for travelling
    float playerLocMinScale = 1.f;      //Min scale for idle player location
    float playerLocMaxScale = 2.f;      //Max scale for idle player location
    float playerLocTransSpeed = 0.025f;
    Vector2 velocity = Vector2(0, 0);
    float playerLocSpeed = 0;
    float playerLocTimeScalar = 1.0f;
    float playerLocMaxSpeed = 500;
    float playerLocMinMoveDist = 10;
    GameObject* playerHp = 0;
    GameObject* playerCurrency = 0;
    GameObject* playerCurrencyText = 0;
    GameObject* playerArtifactsBtn = 0;
};
