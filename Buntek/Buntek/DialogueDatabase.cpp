#include "DialogueDatabase.h"
#include "UI_DialogueHandler.h"
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

void LaunchButtonEffect(Button* button)
{
	// Get ButtonID and pathID
	string buttonCommand = "";
	for (int i{ 0 }; i < UIDialogueManager.dialogueButtonList.size(); ++i)
	{
		if (UIDialogueManager.dialogueButtonList[i] == button && i < UIDialogueManager.dialogueButtonIDList.size())
		{
			buttonCommand = UIDialogueManager.dialogueButtonIDList[i];
			break;
		}
	}

	if (buttonCommand == "")
		return;

	// If there is a path to go to
	string buttonID = buttonCommand;
	string buttonPath = "";

	if (buttonCommand.find("|") != string::npos)
	{
		buttonID = buttonCommand.substr(0, buttonCommand.find("|"));
		buttonPath = buttonCommand.substr(buttonCommand.find("|") + 1, buttonCommand.length());
	}

	// [TODO! Obtain the possible loot choice and assign it to the creation]
	Artifact test1, test2, test3;
	test1.ID = 400;
	test2.ID = 400;
	test3.ID = 400;
	vector<Artifact> fakeArtifacts{ test1, test2, test3 };


	float truemaxhp = GameManager.playerProfile.basemaxhp + GameManager.playerProfile.bonusHp;

	// -------------- Types of button effects ----------------
	switch (stoi(buttonID))
	{
	case 1:
			// Creates a choose loot / rng loot
			UIDialogueManager.CreateRewardSelPreset(fakeArtifacts, 3, true);
			break;
	case 2:
			// Go to a specific dialogue/encounter
			UIDialogueManager.CreateDialoguePreset(buttonPath, 3);
			break;
	case 3:
			// Heal player by 50%
			GameManager.playerProfile.hp += GameManager.playerProfile.basemaxhp / 2;

			if (GameManager.playerProfile.hp > truemaxhp)
				GameManager.playerProfile.hp = truemaxhp;
			RemoveDialogue(button);
			break;
	case 4:
			// Check if player can select this button (Can afford price)
			if (GameManager.playerProfile.stardust < DialogueDatabase.fullHealthCost)
			{
				button->SetClickable(false);
				button->Owner()->GetComponent<SpriteRenderer>()->SetOpacity(0.5f);
				button->Owner()->GetComponent<TextRenderer>()->SetTextColor(1.0f, 0.f, 0.f);
				break;
			}

			// Heal player by Full by using stardust
			GameManager.playerProfile.stardust -= DialogueDatabase.fullHealthCost;
			GameManager.playerProfile.hp = truemaxhp;
			RemoveDialogue(button);
			break;
	default:
			// Force close if nothing can happen
			RemoveDialogue(button);
			break;
	}
}