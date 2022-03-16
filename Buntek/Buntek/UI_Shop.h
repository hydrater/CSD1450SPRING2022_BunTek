/*!*****************************************************************************
\file UI_Shop.h
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Shop UI
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
	int RP_Common = 10, RP_Uncommon = 20, RP_Rare = 30;
};