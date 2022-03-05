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
private:
};
