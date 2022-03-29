/*!*****************************************************************************
\file UI_DialogueHandler.h
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles the UI of Dialogues
*******************************************************************************/
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
	void DF_DisplayArtifact(unsigned long ID);

	bool UIOpen = false, UIDecision = false;	// UIDecision: Prevents user from clicking to next dialogue 
	bool UINotification = false;				// UINotification: Pause Dialogue to display to next command
	struct ArtifactLoot {
		GameObject* DisplayArtifactOwner = 0;
		unsigned long ArtifactID = 0;
	};

	vector<ArtifactLoot> ArtifactChoices = {};

	// Set to public for DialogueDatabase to get the button ID
	vector<Button*> dialogueButtonList;
	vector<string> dialogueButtonIDList;
	// Set to public for gameManager to handle rewardButton
	vector<Button*> rewardButtonList;

	short dialogueSortingLayer = 0;

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
	int rewardButtonNo = 0;

	// Dialogue Preset Size
	const Vector2 vectorZero = Vector2(0.f, 0.f);
	const float dialogueBoxXSize = 1900.f, dialogueBoxYSize = 303.f;
	const Vector2 dialogueBoxPos = Vector2(0, -370);
	const float dialogueBoxFontScale = 0.6f;

	const float actorBoxXSize = dialogueBoxXSize / 4.5f, actorBoxYSize = dialogueBoxYSize / 4.f;
	const Vector2 actorBoxPos = Vector2(0.f, dialogueBoxPos.y + dialogueBoxYSize/4.f + 20.f);
	const float actorBoxColorR = 1.f, actorBoxColorG = 0.29f, actorBoxColorB = 0.89f;

	const float buttonXSize = 785.f, buttonYSize = 70.f;
	const float rewardXSize = 350.f, rewardYSize = 500.f;

	// Display Speed
	float displayTimer = 0;
	const float displaySpeed = 0.001f; // No of char per sec
	int displayNo = 0;
	float doneDisplay = true;

	// Values for determing command and parameters
	size_t CommandMinSize = 3;

	enum TxtFileCommand {
		TFC_ActorName = 'a',
		TFC_ButtonAction = 'b',
		TFC_ChoiceType = 'c',
		TFC_DesignBackground = 'd',
		TFC_EncounterAction = 'e'
	};

	enum ActorNameColor {
		ANC_Black = 'a',
		ANC_Blue = 'b',
		ANC_Green = 'g',
		ANC_Cyan = 'c',
		ANC_Red = 'r',
		ANC_Purple = 'p',
		ANC_Yellow = 'y',
		ANC_White = 'w'
	};
};