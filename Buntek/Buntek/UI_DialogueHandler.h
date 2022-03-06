#pragma once
#include "GameScript.h"
#include "Transform.h"
#include "Component.h"
#include "ArtifactDatabase.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "Button.h"

#define UIDialogueManager UI_DialogueHandler::Instance()

void RemoveDialogue(Button* button);

class UI_DialogueHandler
{
public:
	UI_DialogueHandler(void);
	~UI_DialogueHandler(void);

	static UI_DialogueHandler& Instance(void);
	void Update(void);

	void CreateDialoguePreset(string flag, short sortingLayer);
	// For only after battle (random loot), so it will only show the reward selection part without any dialogue
	void CreateRewardSelPreset(vector<Artifact> artifact, short sortingLayer, bool canDecline);
	void SetDialogueClickable(bool _canClick);
	void SkipDialogue(void);
	void DeleteDialogueEvent(void);
	string GenerateRandomDialogueID(void);		// REMEMBER TO UPDATE THIS WHEN YOU ADD MORE ARTIFACTS

	// Dialogue_Function
	void DF_DisplayArtifact(Button* button, unsigned long ID);

	bool UIOpen = false, UIDecision = false;	// UIDecision: Prevents user from clicking to next dialogue 

	struct ArtifactLoot {
		GameObject* DisplayArtifactOwner = 0;
		unsigned long ArtifactID = 0;
	};

	vector<ArtifactLoot> ArtifactChoices = {};

	// Set to public for DialogueDatabase to get the button ID
	vector<Button*> dialogueButtonList;
	vector<string> dialogueButtonIDList;

private:

	void WriteToDialogue(void);

	// Normal Dialogue (From dialogue.txt / Preset Artifacts)
	void CreateDialogue(string flag, short sortingLayer);
	void StartDialogueEvent(string flag);

	// Battle End Reward Selection (Normally called in-game / Random Artifacts)
	void CreateRewardSel(vector<Artifact> artifact, short sortingLayer, bool canDecline);

	// Dialogue Tools
	void CreatePreset(short sortingLayer); // To create all the objects
	void LoadFromFile(string flag);
	bool CheckNextCommand(char command);
	void AssignArtifact(GameObject* owner, string selArtifact);

	string selectedFlag = "";
	vector<string> dialogueList;
	int dialogueNo = 0;
	GameObject* dialogueBox = 0;

	// Dialogue
	TextRenderer* actorTxt = 0, * dialogueTxt = 0;
	string name, dialogueOutput, dialogueFinalDisplayTxt;
	int dialogueButtonNo = 0;
	vector<Button*> rewardButtonList;
	int rewardButtonNo = 0;

	short dialogueSortingLayer = 0;
	float displayTimer = 0;
	const float displaySpeed = 0.001f; // No of char per sec
	int displayNo = 0;
	float doneDisplay = true;
};