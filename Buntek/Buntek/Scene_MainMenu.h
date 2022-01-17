#pragma once
#include "System.h"

class Scene_MainMenu : public Scene
{
public:

    void Start(void) override;
    void Update(void) override;

    GameObject* encounter = 0, * rewardsel = 0, * enemynode = 0, * shopui = 0;
private:
    GameObject* background = 0, * Battle = 0, * dialogue = 0;
};
