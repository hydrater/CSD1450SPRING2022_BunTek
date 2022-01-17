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
};