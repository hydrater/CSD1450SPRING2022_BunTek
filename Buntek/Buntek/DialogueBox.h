#pragma once
#include "Transform.h"
#include "Component.h"

class DialogueBox : public Component
{
public:
	DialogueBox(void);
	~DialogueBox(void);
	void LoadFromFile(string flag);

private:
	string name, dialogue;
	vector<string> dialogueList;
};