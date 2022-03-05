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

	vector<GameObject*> dialogueSceneObjList;
	vector<string> textureList;
	void InitDialogueScene(string id);
	void ClearDialogueSceneObjs(void);
private:
};
