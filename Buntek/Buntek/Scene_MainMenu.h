#pragma once
#include "System.h"

class Scene_MainMenu : public Scene
{
public:
    void CreateEncounter(Vector2 position, int sortingLayer, string flag);
    void CloseEncounter(void);
    void Start(void) override;
    void Update(void) override;

    GameObject* encounter = 0;
private:
    GameObject* background = 0, *Battle = 0, * dialogue = 0;
};
