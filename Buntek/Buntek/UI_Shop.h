/*!*****************************************************************************
\file UI_Shop.h
\project Beyond Aurorean Skies
\author: Isaiah Lim Ji Rong (90%)
\co-authors: Algene Tan Chuan Hong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Shop UI
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/

#pragma once
#include "Transform.h"
#include "Component.h"
#include "Button.h"
#include "TextRenderer.h"
#include "ArtifactDatabase.h"
#include "MapGenerator.h"


class UI_Shop : public GameScript
{
public:
	UI_Shop(void);
	~UI_Shop(void);

	void CreateShop(short sortingLayer, _mapData::ShopArtifacts shop);
	void StartShop(void);
	void CloseShop(void);
	void DeleteShop(void);
	void SetClickable(bool _canClick);

	struct ArtifactGoods {
		GameObject* DisplayArtifactOwner = 0;
		unsigned long ArtifactID = 0;
		bool purchased = false;
		int price = 0;
	};

	vector<ArtifactGoods> ArtifactOnSale = {};
	_mapData::ShopArtifacts DisplayedShop;

	TextRenderer* currencyTxt = 0;

private:
	Vector2 buttonArtifactSize = Vector2(175, 250);
	vector<Vector2> buttonArtifactPos = { Vector2(-buttonArtifactSize.x * 3, buttonArtifactSize.y/ 1.15f), Vector2(0.f, buttonArtifactSize.y / 1.15f),
		Vector2(buttonArtifactSize.x * 3, buttonArtifactSize.y / 1.15f), Vector2(-buttonArtifactSize.x * 3, -buttonArtifactSize.y / 1.45f),
		Vector2(0.f, -buttonArtifactSize.y / 1.45f), Vector2(buttonArtifactSize.x * 3, -buttonArtifactSize.y / 1.45f)};

	Vector2 stastHolderSize = Vector2(buttonArtifactSize.x * 2, buttonArtifactSize.y);

	SpriteRenderer* header = 0;
	TextRenderer* headerText = 0;
	Button* leaveButton = 0;
	vector<Button*> buttonArtifactList;

	int ShopID = 0;

	const int RP_Common = 10, RP_Uncommon = 20, RP_Rare = 30;

	const float headerXSize = 700.f, headerYSize = 100.f;
	const Vector2 headerPos = Vector2(0.f, AEGetWindowHeight() / 2.25f);
	const short headerOffset = 1;

	const float currencyXSize = 300.f, currencyYSize = 100.f;
	const Vector2 currencyPos = Vector2(-AEGetWindowWidth() / 2.5f, AEGetWindowHeight() / 2.25f);
	const short currencyOffset = 1;

	const float currencyIconXSize = 80.f, currencyIconYSize = 80.f;
	const float currencyIconXOffset = -100.f;
	const short currencyIconOffset = 2;

	const float currencyPriceXSize = 180.f, currencyPriceYSize = 80.f;
	const float currencyPriceXOffset = 50.f;
	const short currencyPriceOffset = 3;

	const float leaveXSize = 785.f, leaveYSize = 70.f;
	const Vector2 leavePos = Vector2(0.f, -450.f);
	const short leaveOffset = 2;

	const short artifactButtonSpriteOffset = 2, artifactButtonTextOffset = 3;
};