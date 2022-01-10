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
	void Start(void) override;
	void Update(void) override;

	void LoadFromFile(string flag);
	void WriteToDialogue(void);
	void ToggleDisplay(bool flag);
	void NextDialogue(void);

	bool isMainDialogue = false;
	bool isOpen = false;

	SpriteRenderer* sr = 0;
	TextRenderer* tr = 0;

	// If DialogueBox holds the dialogue
	DialogueBox* actorBox;

private:
	string name, dialogueTxt, dialogueDisplayTxt;
	vector<string> dialogueList;
	int dialogueNo = 0;

	float displayTimer = 0;
	float displaySpeed = 0.001f; // No of char per sec
	int displayNo = 0;

	float doneDisplay = true;

	Transform* transform = 0;
};