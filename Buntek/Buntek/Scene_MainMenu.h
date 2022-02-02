#pragma once
#include "System.h"
#include "Button.h"

#define menu Scene_MainMenu::instance

class Scene_MainMenu : public Scene
{
public:
    void Start(void) override;
    void Update(void) override;
    ~Scene_MainMenu(void) override;
    GameObject* GetObjRef(short type);
    static Scene_MainMenu * instance;
    const Vector2 battleBtnPos = Vector2(-670, -200), optionBtnPos = Vector2(-670, -300), quitBtnPos = Vector2(-670, -400);
    bool startPlay = true, optionPlay = true, quitPlay = true;

private:
    GameObject* background = 0, *MainMenu = 0;
    GameObject* startBtn = 0, * optionBtn = 0, * quitBtn = 0;
    SpriteRenderer* polkaDotter = 0;
    Transform* disc = 0;
};
