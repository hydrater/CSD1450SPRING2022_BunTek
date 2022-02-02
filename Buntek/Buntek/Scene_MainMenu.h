#pragma once
#include "System.h"

class Scene_MainMenu : public Scene
{
public:
    void Start(void) override;
    void Update(void) override;
    ~Scene_MainMenu(void) override;

private:
    GameObject* background = 0, *battleBtn = 0, *optionBtn = 0, *quitBtn = 0;
    GameObject* MainMenu = 0;
    SpriteRenderer* polkaDotter = 0;
};
