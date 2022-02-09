#pragma once
#include "GameScript.h"
#include "Transform.h"
#include "Component.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "Button.h"

#define UIDialogueManager UI_DialogueHandler::Instance()

class UI_DialogueHandler : public GameScript
{
public:
	UI_DialogueHandler(void);
	~UI_DialogueHandler(void);

	static UI_DialogueHandler& Instance(void);

	void Start(void) override;
	void Update(void) override;

	void CreateDialoguePreset(string flag, short sortingLayer);
	void SetDialogueClickable(bool _canClick);
	void SkipDialogue(void);
	void DeleteDialogueEvent(void);

	bool UIOpen = false, UIDecision = false;	// UIDecision: Prevents user from clicking to next dialogue 

private:

	void WriteToDialogue(void);

	// Dialogue
	void CreateDialogue(string flag, short sortingLayer);
	void StartDialogueEvent(string flag);

	void LoadFromFile(string flag);
	bool CheckNextCommand(char command);
	void AssignButton(Button* button, char buttonType, char selchar);

	string selectedFlag = "";
	vector<string> dialogueList;
	int dialogueNo = 0;
	GameObject* dialogueBox = 0, * rewardSel = 0;

	// Dialogue
	TextRenderer* actorTxt = 0, * dialogueTxt = 0;
	string name, dialogueOutput, dialogueFinalDisplayTxt;
	vector<Button*> dialogueButtonList;
	int dialogueButtonNo = 0;
	vector<Button*> rewardButtonList;
	int rewardButtonNo = 0;

	float displayTimer = 0;
	const float displaySpeed = 0.001f; // No of char per sec
	int displayNo = 0;
	float doneDisplay = true;

	enum ButtonFunctionType {
		BF_Leave = 0,
		BF_Sample1
	};

	enum ChoiceFunctionType {
		CF_Leave = 0,
		CF_Sample1
	};
};