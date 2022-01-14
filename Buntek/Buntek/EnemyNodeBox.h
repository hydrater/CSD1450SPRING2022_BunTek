#pragma once
#include "GameScript.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"

class EnemyNodeBox : public GameScript
{
public:
	EnemyNodeBox(void);
	~EnemyNodeBox(void);
	void Start(void) override;
	void Update(void) override;
	//void AssignObjReferences(void);
	//void StartEnemyNode(void);
	//void CloseEnemyNode(void);
	void CreateEnemyNode(GameObject* button, int sortingLayer, int ArtifactTypes);

	//SpriteRenderer* Name, * display, * background;
	//TextRenderer* NameText, * descriptionText;

	//vector<string> artifactList;
	//string name, description, ballartifact;

private:

};