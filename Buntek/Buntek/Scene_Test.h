#pragma once
#include "System.h"
#include "SpriteRenderer.h"
#include "Button.h"

class Scene_Test : public Scene
{
private:
	GameObject* splashimage1 = 0;

	GameObject* splashimage2 = 0;

	GameObject* splashimage3 = 0;

	GameObject* splashimage4 = 0;

	GameObject* splashimage5 = 0;

	GameObject* splashimage6 = 0;

	GameObject* spawner = 0;

	GameObject* testrun1 = 0;
	SpriteRenderer* testrun2 = 0;
	TextRenderer* testrun3 = 0;

	string selectedFlag = "";
	vector<string> dialogueList;
	int dialogueNo = 0;
	GameObject* dialogueBox = 0;

	// Dialogue
	TextRenderer* actorTxt = 0, * dialogueTxt = 0;
	string name, dialogueOutput, dialogueFinalDisplayTxt;
	vector<Button*> dialogueButtonList;
	int dialogueButtonNo = 0;
	vector<Button*> rewardButtonList;

public:
    void Start(void) override;
    void Update(void) override;
};
