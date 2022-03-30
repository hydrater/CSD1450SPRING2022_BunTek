/*!*****************************************************************************
\file Scene_MainMenu.cpp
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Scene Main Menu Screen
*******************************************************************************/
#pragma once
#include "System.h"
#include "Button.h"

#define menu Scene_MainMenu::instance

class Scene_MainMenu : public Scene
{
public:
    void Start(void) override;
    void EarlyUpdate(void) override;
    void Update(void) override;
    ~Scene_MainMenu(void) override;
    GameObject* GetObjRef(short type);
    static Scene_MainMenu * instance;
    const Vector2 battleBtnPos = Vector2(-670, 0), howtoplayBtnPos = Vector2(-670, -100) ,optionBtnPos = Vector2(-670, -200), creditsBtnPos = Vector2(-670, -300), quitBtnPos = Vector2(-670, -400);
    bool startPlay = true, optionPlay = true, quitPlay = true, howtoPlay = true, creditsPlay = true;
    TextRenderer* displayTxt = 0;

private:
    GameObject* background = 0, *mainMenu = 0;
    GameObject* startBtn = 0, * optionBtn = 0, * quitBtn = 0, * howtoplayBtn = 0, * creditsBtn = 0;
    SpriteRenderer* polkaDotter = 0, *mask = 0, *mainArtRenderer = 0, * title = 0;
    Transform* disc = 0, *fake = 0, *bottom = 0, *border = 0;
    float animTimer = 0, artSwitchTimer = 0;
    bool finishedSetup = false;
    short cycle = 0;
};
