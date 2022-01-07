#pragma once
#include "Transform.h"
#include "Component.h"

class DialogueBox : public Component
{
public:
	DialogueBox(void);
	~DialogueBox(void);
	void LoadFromFile(string flag);
	void WriteToDialogue(void);

private:
	string name, dialogueTxt;
	vector<string> dialogueList;
	int dialogueNo = 0;
};