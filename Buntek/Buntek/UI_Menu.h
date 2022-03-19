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
    GameObject* Header = 0;
    GameObject* musicSliderHeader = 0;
    GameObject* musicSlider = 0;
    GameObject* soundSliderHeader = 0;
    GameObject* soundSlider = 0;
    GameObject* fullScreenBtn = 0;
    GameObject* LeaveBtn = 0;
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
    GameObject* musicSliderHeader = 0;
    GameObject* musicSlider = 0;
    GameObject* soundSliderHeader = 0;
    GameObject* soundSlider = 0;
    GameObject* fullScreenBtn = 0;
    GameObject* LeaveBtn = 0;
private:

};