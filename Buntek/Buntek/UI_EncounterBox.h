#pragma once
#include "GameScript.h"
#include "Transform.h"
#include "Component.h"
#include "Button.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"

/* Encounter /parameters */
// i : image/texture name
// h : Header Name
// b : Button Name


class UI_EncounterBox : public GameScript
{
public:
	UI_EncounterBox(void);
	~UI_EncounterBox(void);

	void CreateEncounter(Vector2 position, short sortingLayer, string flag);
	void AssignObjReferences(SpriteRenderer* _header, SpriteRenderer* _display, SpriteRenderer* _background, TextRenderer* _headerText, TextRenderer* _descriptionText, vector<Button*> _buttonList);
	void StartEncounterEvent(string flag);
	void CloseEncounterEvent(void);
	void WriteToEncounterEvent(void);
	void SetClickable(bool _canClick);

private:
	void LoadFromFile(string flag);

	SpriteRenderer* header = 0, * display = 0, * background = 0;
	TextRenderer* headerText = 0, *descriptionText = 0;
	vector<Button*> buttonList;
	int buttonNo = 0;

	string name, description;
	vector<string> descriptList;
	int descriptNo = 0;
};
