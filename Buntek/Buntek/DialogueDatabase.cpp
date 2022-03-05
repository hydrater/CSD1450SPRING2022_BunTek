#include "DialogueDatabase.h"
#include "Parallaxer.h"
#include "AlphaChanger.h"
#include "ParticleSystem.h"
#include "AssetManager.h"

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
		GameObject* splashimage1 = devTools.CreateSpriteGameObject("Background.jpg", 1920, 1080, AE_GFX_BM_BLEND, Vector2(0, 0));

		dialogueSceneObjList.push_back(splashimage1);
	}
		break;
	case 1:
	{
		AssetManager.LoadTexture("Concepts/Full-Cave.png");
		textureList.push_back("Concepts/Full-Cave.png");

		GameObject* splashimage1 = devTools.CreateSpriteGameObject("Concepts/Full-Cave.png", 1920, 1080, AE_GFX_BM_BLEND, Vector2(0, 0));
		dialogueSceneObjList.push_back(splashimage1);
	}
	default:
		break;
	}
}

void _dialogueDatabase::ClearDialogueSceneObjs(void)
{
	if (dialogueSceneObjList.size() == 0 && textureList.size() == 0)
		return;

	for (int i = 0; i < dialogueSceneObjList.size(); i++)
		dialogueSceneObjList[i]->Delete();

	for (int i = 0; i < textureList.size(); i++)
		AssetManager.UnloadTexture(textureList[i]);

	dialogueSceneObjList.clear();
}
