#pragma once
#include "GameScript.h"
#include "Transform.h"
#include "Component.h"
#include "Button.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"

class EncounterBox : public GameScript
{
public:
	EncounterBox(void);
	~EncounterBox(void);

	void AssignObjReferences(SpriteRenderer* _header, SpriteRenderer* _display, SpriteRenderer* _background, TextRenderer* _headerText, TextRenderer* _descriptionText, vector<Button*> _buttonList);
	void StartEncounterEvent(string flag);
	void CloseEncounterEvent(void);
	void WriteToEncounterEvent(void);

private:
	void LoadFromFile(string flag);

	SpriteRenderer* header, * display, * background;
	TextRenderer* headerText, *descriptionText;
	vector<Button*> buttonList;
	int buttonNo = 0;

	string name, description;
	vector<string> descriptList;
	int descriptNo = 0;
};
