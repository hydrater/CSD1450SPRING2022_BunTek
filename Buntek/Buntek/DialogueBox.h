#pragma once
#include "GameScript.h"
#include "Transform.h"
#include "Component.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"

class DialogueBox : public GameScript
{
public:
	DialogueBox(void);
	~DialogueBox(void);
	//void Start(void) override;
	//void Update(void) override;

	/*void StartDialogueEvent(string flag);
	void CloseDialogueEvent(void);
	void WriteToDialogue(void);
	void NextDialogue(void);*/

	bool isMainDialogue = false;
	bool isOpen = false;

	SpriteRenderer* actorSprite = 0, *dialogueSprite = 0;
	TextRenderer* actorTxt = 0, *dialogueTxtObj = 0;

	// If DialogueBox holds the dialogue
	DialogueBox* actorBox = 0;

private:
	void LoadFromFile(string flag);
	string name, dialogueTxt, dialogueDisplayTxt;
	vector<string> dialogueList;
	int dialogueNo = 0;

	float displayTimer = 0;
	const float displaySpeed = 0.001f; // No of char per sec
	int displayNo = 0;
	float doneDisplay = true;

	Transform* transform = 0;
};