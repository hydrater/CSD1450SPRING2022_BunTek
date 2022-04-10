/*!*****************************************************************************
\file UI_EnemyNodeBox.h
\project Beyond Aurorean Skies
\author: Bryan Boh Tai Hong (90%)
\co-authors: Algene Tan Chuan Hong (2.5%), Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Eneny node boxes' UI
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/
#pragma once
#include "GameScript.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"

class UI_EnemyNodeBox : public GameScript
{
public:
	UI_EnemyNodeBox(void);
	~UI_EnemyNodeBox(void);
	void Start(void) override;
	void Update(void) override;
	void LoadFromFile(string flag);
	//void AssignObjReferences(void);
	//void StartEnemyNode(void);
	//void CloseEnemyNode(void);
	void CreateEnemyNode(GameObject* button, int sortingLayer, int ArtifactTypes);
	GameObject* GetEnemyNode(void);
	GameObject* GetArtifactGrid(void);

	//SpriteRenderer* Name, * display, * background;
	//TextRenderer* NameText, * descriptionText;

	//vector<string> artifactList;
	//string name, description, ballartifact;
	vector<string> descriptList;
	int descriptNo = 0;

private:
	GameObject* enemynode = 0;
	GameObject* artifactgrid = 0;

	const float nodeBckgrndSize = 300.f;
};