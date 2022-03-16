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
    float playerLocScaleSpeed = 0.0025f, playerLocTargetScale = 1.f;
    float playerLocScale = 1, playerLocMinScale = 0.5f, playerLocMaxScale = 1.f;
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
