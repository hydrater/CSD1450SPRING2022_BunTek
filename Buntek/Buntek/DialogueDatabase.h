#pragma once
#include <string>
#include <vector>
#include "Entity.h"
using namespace std;

#define DialogueDatabase _dialogueDatabase::Instance()

class _dialogueDatabase
{
public:
	_dialogueDatabase();
	~_dialogueDatabase();
	static _dialogueDatabase& Instance(void);
	static void SpawnEncounterObject(unsigned long id);
	static string GetName(unsigned long id);
	static string GetDescription(unsigned long id);

	vector<GameObject*> dialogueSceneObjList;
	vector<string> textureList;
	void InitDialogueScene(string id);
	void ClearDialogueSceneObjs(void);
private:
};
