#pragma once
#include "System.h"

class Scene_MainMenu : public Scene
{
public:
    void Start(void) override;
    void Update(void) override;
private:
    GameObject* background, *Battle, *dialogue;
    bool TestDialogueDisplay = false; // [TO REMOVE] This code is just to test DialogueBox functionality
};
