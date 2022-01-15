#pragma once
#include "GameScript.h"
#include "Transform.h"
#include "Component.h"
#include "Button.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"


class UI_RewardSelection : public GameScript
{
public:
	UI_RewardSelection(void);
	~UI_RewardSelection(void);

	/*=====WIP=====
	* vector<string> rewards will be converted to
	* vector<Artifact> so that the button rewards
	* will reflect the image and description
	*///===========

	void CreateRewardSelection(Vector2 position, int sortingLayer, vector<string> rewards);
	void StartRewardSelection(void);
	void CloseRewardSelection(void);

private:

	SpriteRenderer* header, * background;
	TextRenderer* headerText;
	vector<Button*> buttonList;
};
