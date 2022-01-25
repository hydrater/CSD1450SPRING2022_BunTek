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
	void DeleteDialogueEvent(void);
	void DeleteRewardSelection(void);


private:

	void WriteToDialogue(void);

	// Dialogue
	void CreateDialogue(string flag, short sortingLayer);
	void StartDialogueEvent(string flag);
	void CloseDialogueEvent(void);

	/*=====WIP=====
	* vector<string> rewards will be converted to
	* vector<Artifact> so that the button rewards
	* will reflect the image and description
	*///===========

	void CreateRewardSelection(string flag, short sortingLayer);
	void StartRewardSelection(string flag);
	void CloseRewardSelection(void);

	static UI_DialogueHandler* instance;

	void LoadFromFile(string flag);
	string selectedFlag = "";
	vector<string> dialogueList;
	int dialogueNo = 0;
	GameObject* dialogueBox = 0, * rewardSel = 0;

	// Dialogue
	TextRenderer* actorTxt = 0, * dialogueTxt = 0;
	string dialogueFlag = "asd";
	string encounterFlag = "aed";
	string name, dialogueOutput, dialogueFinalDisplayTxt;
	vector<Button*> dialogueButtonList;
	int dialogueButtonNo = 0;

	float displayTimer = 0;
	const float displaySpeed = 0.001f; // No of char per sec
	int displayNo = 0;
	float doneDisplay = true;

	// Reward Selection
	string rewardFlag = "rsel";
	SpriteRenderer* header = 0, * background = 0;
	TextRenderer* headerText = 0;
	vector<Button*> rewardButtonList;
	int rewardButtonNo = 0;
};