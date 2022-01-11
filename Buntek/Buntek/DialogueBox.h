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

	void AssignObjReferences(SpriteRenderer* _actorSprite, SpriteRenderer* _dialogueSprite, TextRenderer* _actorTxt, TextRenderer* _dialogueTxt);
	void StartDialogueEvent(string flag);
	void CloseDialogueEvent(void);
	void WriteToDialogue(void);

	TextRenderer* actorTxt = 0, *dialogueTxt = 0;

private:
	void LoadFromFile(string flag);
	string name, dialogueOutput, dialogueFinalDisplayTxt;
	vector<string> dialogueList;
	int dialogueNo = 0;

	float displayTimer = 0;
	const float displaySpeed = 0.001f; // No of char per sec
	int displayNo = 0;
	float doneDisplay = true;
};