/*!*****************************************************************************
\file UI_Menu.h
\author: Bryan Boh Tai Hong (80%)
\co-authors: Algene Tan Chuan Hong (5%), Isaiah Lim Ji Rong (5%), Steven Koe (5%), Goh Kiat Beng (5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Menu behaviour
*******************************************************************************/

#pragma once
#include "Component.h"
#include "GameScript.h"


class UI_OptionMenu : public GameScript
{
public:
	UI_OptionMenu(void);
	~UI_OptionMenu(void);
	void CreateOptionMenu(short sortingLayer);

	GameObject* tempBckgrnd =0;
    GameObject* header = 0;
    GameObject* musicSliderHeader = 0;
    GameObject* musicSlider = 0;
    GameObject* soundSliderHeader = 0;
    GameObject* soundSlider = 0;
    GameObject* fullScreenBtn = 0;
    GameObject* LeaveBtn = 0;
    float defaultHeaderTextSize = 48.f;
    float defaultElementTextSize = 24.f;
    float defaultBckgrndXPos = 0;
    float defaultBckgrndYPos = 100;
    float defaultHeaderXSize = 200;
    float defaultHeaderYSize = 100;
    float defaultmusicSliderHeaderXSize = 100;
    float defaultmusicSliderHeaderYSize = 60;
    float defaultsoundSliderHeaderXSize = 100;
    float defaultsoundSliderHeaderYSize = 60;
    float defaultfullScreenBtnXSize = 380;
    float defaultfullScreenBtnYSize = 40;
    float defaultLeaveBtnXSize = 380;
    float defaultLeaveBtnYSize = 40;
private:

};

class UI_PauseMenu : public GameScript
{
public:
    UI_PauseMenu(void);
    ~UI_PauseMenu(void);
    void CreatePauseMenu(short sortingLayer);

    GameObject* tempBckgrnd = 0;
    GameObject* Header = 0;
    GameObject* resumeBtn = 0;
    GameObject* howToPlayBtn = 0;
    GameObject* optionBtn = 0;
    GameObject* surrenderBtn = 0;
    GameObject* quitBtn = 0;

    float defaultHeaderTextSize = 48.f;
    float defaultElementTextSize = 24.f;
    float defaultBckgrndXPos = 0;
    float defaultBckgrndYPos = 100;
    float defaultHeaderXSize = 200;
    float defaultHeaderYSize = 100;
    float defaultElementXSize = 380;
    float defaultElementYSize = 40;
private:

};

class UI_HowToPlayMenu : public GameScript
{
public:
    UI_HowToPlayMenu(void);
    ~UI_HowToPlayMenu(void);
    void CreateHowToPlayMenu(short sortingLayer);

    GameObject* tempBckgrnd = 0;
    GameObject* backBtn = 0;
    float defaultHeaderTextSize = 48.f;
    float defaultElementTextSize = 24.f;
    float defaultBckgrndXPos = 0;
    float defaultBckgrndYPos = 0;
    float defaultbackBtnXSize = 300;
    float defaultbackBtnYSize = 40;
    float defaultbackBtnXPos = 750.f;
    float defaultbackBtnYPos = -400.f;
private:

};