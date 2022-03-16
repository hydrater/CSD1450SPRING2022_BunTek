/*!*****************************************************************************
\file DialogueDatabase.h
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Dialogue Database
*******************************************************************************/

#pragma once
#include <string>
#include <vector>
#include "Button.h"
#include "Entity.h"
using namespace std;

#define DialogueDatabase _dialogueDatabase::Instance()

void LaunchButtonEffect(Button* button);

class _dialogueDatabase
{
public:
	_dialogueDatabase();
	~_dialogueDatabase();
	static _dialogueDatabase& Instance(void);

	vector<GameObject*> dialogueSceneObjList;
	vector<string> textureList;
	void InitDialogueScene(string id);
	void ClearDialogueSceneObjs(void);

	string forceCommand = "";		// Use this to call a function in LaunchButtonEffect if button is a nullptr
	int fullHealthCost = 10;		// Cost to heal to max hp
private:
};
