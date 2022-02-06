#include "DialogueDatabase.h"
#include "Parallaxer.h"
#include "AlphaChanger.h"
#include "ParticleSystem.h"

_dialogueDatabase::_dialogueDatabase()
{
}

_dialogueDatabase::~_dialogueDatabase()
{
}

_dialogueDatabase& _dialogueDatabase::Instance(void)
{
    static _dialogueDatabase instance;
    return instance;
}

void _dialogueDatabase::SpawnEncounterObject(unsigned long id)
{
}

string _dialogueDatabase::GetName(unsigned long id)
{
	return string();
}

string _dialogueDatabase::GetDescription(unsigned long id)
{
	return string();
}

void _dialogueDatabase::InitDialogueScene(string id)
{
	switch (stoi(id))
	{
	case 0:
	{
		GameObject* splashimage1 = 0;

		splashimage1 = devTools.CreateSpriteGameObject("Background.jpg", 1920, 1080, AE_GFX_BM_BLEND, Vector2(0, 0));

		dialogueSceneObjList.push_back(splashimage1);
	}
		break;
	default:
		break;
	}
}

void _dialogueDatabase::ClearDialogueSceneObjs(void)
{
	if (dialogueSceneObjList.size() == 0)
		return;

	for (int i = 0; i < dialogueSceneObjList.size(); i++)
		dialogueSceneObjList[i]->Delete();

	dialogueSceneObjList.clear();
}
