#pragma once
#include "Transform.h"
#include "Component.h"
#include "Button.h"
#include "TextRenderer.h"


class UI_Shop : public GameScript
{
public:
	UI_Shop(void);
	~UI_Shop(void);

	/*=====WIP=====
	* vector<string> artifacts will be converted to
	* vector<Artifact> so that the button rewards
	* will reflect the image and description
	* (Same with vector<strgin> stats)
	*///===========

	void CreateShop(int sortingLayer, vector<string> artifacts, vector<string> stats);
	void StartShop(void);
	void CloseShop(void);
	void SetClickable(bool _canClick);

private:
	Vector2 buttonArtifactSize = Vector2(175, 250);
	vector<Vector2> buttonArtifactPos = { Vector2(-buttonArtifactSize.x * 3, buttonArtifactSize.y/1.25f), Vector2(-buttonArtifactSize.x, buttonArtifactSize.y / 1.25f),
		Vector2(buttonArtifactSize.x, buttonArtifactSize.y / 1.25f), Vector2(buttonArtifactSize.x * 3, buttonArtifactSize.y / 1.25f),
		Vector2(-buttonArtifactSize.x * 2, -buttonArtifactSize.y / 2), Vector2(buttonArtifactSize.x * 2, -buttonArtifactSize.y / 2)};

	Vector2 stastHolderSize = Vector2(buttonArtifactSize.x * 2, buttonArtifactSize.y);

	Vector2 buttonStatsSize = Vector2(stastHolderSize.x/3, stastHolderSize.y/2);
	vector<Vector2> buttonStatsPos = { Vector2(-buttonStatsSize.x, buttonStatsSize.y / 2), Vector2(0.f, buttonStatsSize.y / 2),
		Vector2(buttonStatsSize.x, buttonStatsSize.y / 2), Vector2(-buttonStatsSize.x, -buttonStatsSize.y / 2),
		Vector2(0.f, -buttonStatsSize.y / 2), Vector2(buttonStatsSize.x, -buttonStatsSize.y / 2) };

	SpriteRenderer* header, *statsHolder;
	TextRenderer* headerText;
	Button* leaveButton;
	vector<Button*> buttonArtifactList;
	vector<Button*> buttonStatsList;
};