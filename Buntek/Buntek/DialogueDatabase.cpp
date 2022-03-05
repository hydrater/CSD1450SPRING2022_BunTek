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
	break;
	case 2:
	{
		AssetManager.LoadTexture("Concepts/Full-ArticMounts.png");
		textureList.push_back("Concepts/Full-ArticMounts.png");

		GameObject* splashimage1 = devTools.CreateSpriteGameObject("Concepts/Full-ArticMounts.png", 1920, 1080, AE_GFX_BM_BLEND, Vector2(0, 0));
		dialogueSceneObjList.push_back(splashimage1);
	}
	break;
	case 3:
	{
		AssetManager.LoadTexture("Concepts/Full-CrystalCaves.png");
		textureList.push_back("Concepts/Full-CrystalCaves.png");

		GameObject* splashimage1 = devTools.CreateSpriteGameObject("Concepts/Full-CrystalCaves.png", 1920, 1080, AE_GFX_BM_BLEND, Vector2(0, 0));
		dialogueSceneObjList.push_back(splashimage1);
	}
	break;
	case 4:
	{
		AssetManager.LoadTexture("Concepts/Full-Rainforest.png");
		textureList.push_back("Concepts/Full-Rainforest.png");

		GameObject* splashimage1 = devTools.CreateSpriteGameObject("Concepts/Full-Rainforest.png", 1920, 1080, AE_GFX_BM_BLEND, Vector2(0, 0));
		dialogueSceneObjList.push_back(splashimage1);
	}
	break;
	case 5:
	{
		AssetManager.LoadTexture("Concepts/Full-Volcano.png");
		textureList.push_back("Concepts/Full-Volcano.png");

		GameObject* splashimage1 = devTools.CreateSpriteGameObject("Concepts/Full-Volcano.png", 1920, 1080, AE_GFX_BM_BLEND, Vector2(0, 0));
		dialogueSceneObjList.push_back(splashimage1);
	}
	break;
	case 6:
	{
		AssetManager.LoadTexture("Concepts/Full-Yggdrasil.png");
		textureList.push_back("Concepts/Full-Yggdrasil.png");

		GameObject* splashimage1 = devTools.CreateSpriteGameObject("Concepts/Full-Yggdrasil", 1920, 1080, AE_GFX_BM_BLEND, Vector2(0, 0));
		dialogueSceneObjList.push_back(splashimage1);
	}
	break;
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
