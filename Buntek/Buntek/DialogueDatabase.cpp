#include "DialogueDatabase.h"
#include "UI_DialogueHandler.h"
#include "ArtifactDatabase.h"
#include "SaveManager.h"
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
	if (id == "")
	{
		cout << "[DialogueDatabase] WARNING! [" << id << "] is not a number! Not Loading Dialogue Image...\n";
		return;
	}

	switch (stoi(id))
	{
	case 0:
	{
		GameObject* splashimage1 = devTools.CreateSpriteGameObject("Background.jpg", 1920, 1080, AE_GFX_BM_BLEND, Vector2(0, 0), UIDialogueManager.dialogueSortingLayer - 3);

		dialogueSceneObjList.push_back(splashimage1);
	}
	break;
	case 1:
	{
		AssetManager.LoadTexture("Concepts/Full-Cave.png");
		textureList.push_back("Concepts/Full-Cave.png");

		GameObject* splashimage1 = devTools.CreateSpriteGameObject("Concepts/Full-Cave.png", 1920, 1080, AE_GFX_BM_BLEND, Vector2(0, 0), UIDialogueManager.dialogueSortingLayer - 3);
		dialogueSceneObjList.push_back(splashimage1);
	}
	break;
	case 2:
	{
		AssetManager.LoadTexture("Concepts/Full-ArticMounts.png");
		textureList.push_back("Concepts/Full-ArticMounts.png");

		GameObject* splashimage1 = devTools.CreateSpriteGameObject("Concepts/Full-ArticMounts.png", 1920, 1080, AE_GFX_BM_BLEND, Vector2(0, 0), UIDialogueManager.dialogueSortingLayer - 3);
		dialogueSceneObjList.push_back(splashimage1);
	}
	break;
	case 3:
	{
		AssetManager.LoadTexture("Concepts/Full-CrystalCaves.png");
		textureList.push_back("Concepts/Full-CrystalCaves.png");

		GameObject* splashimage1 = devTools.CreateSpriteGameObject("Concepts/Full-CrystalCaves.png", 1920, 1080, AE_GFX_BM_BLEND, Vector2(0, 0), UIDialogueManager.dialogueSortingLayer - 3);
		dialogueSceneObjList.push_back(splashimage1);
	}
	break;
	case 4:
	{
		AssetManager.LoadTexture("Concepts/Full-Rainforest.png");
		textureList.push_back("Concepts/Full-Rainforest.png");

		GameObject* splashimage1 = devTools.CreateSpriteGameObject("Concepts/Full-Rainforest.png", 1920, 1080, AE_GFX_BM_BLEND, Vector2(0, 0), UIDialogueManager.dialogueSortingLayer - 3);
		dialogueSceneObjList.push_back(splashimage1);
	}
	break;
	case 5:
	{
		AssetManager.LoadTexture("Concepts/Full-Volcano.png");
		textureList.push_back("Concepts/Full-Volcano.png");

		GameObject* splashimage1 = devTools.CreateSpriteGameObject("Concepts/Full-Volcano.png", 1920, 1080, AE_GFX_BM_BLEND, Vector2(0, 0), UIDialogueManager.dialogueSortingLayer - 3);
		dialogueSceneObjList.push_back(splashimage1);
	}
	break;
	case 6:
	{
		AssetManager.LoadTexture("Concepts/Full-Yggdrasil.png");
		textureList.push_back("Concepts/Full-Yggdrasil.png");

		GameObject* splashimage1 = devTools.CreateSpriteGameObject("Concepts/Full-Yggdrasil", 1920, 1080, AE_GFX_BM_BLEND, Vector2(0, 0), UIDialogueManager.dialogueSortingLayer - 3);
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
	if (button != nullptr)
	{
		for (int i{ 0 }; i < UIDialogueManager.dialogueButtonList.size(); ++i)
		{
			if (UIDialogueManager.dialogueButtonList[i] == button && i < UIDialogueManager.dialogueButtonIDList.size())
			{
				buttonCommand = UIDialogueManager.dialogueButtonIDList[i];
				break;
			}
		}
	}
	else
	{
		buttonCommand = DialogueDatabase.forceCommand;
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
	
	// -------------- Types of button effects ----------------
	switch (stoi(buttonID))
	{
	case 1:
	{
		// Create a random set of artifact to draw
		Artifact test1, test2, test3;
		test1.ID = ArtifactDatabase.DrawArtifact();
		test2.ID = ArtifactDatabase.DrawArtifact();
		test3.ID = ArtifactDatabase.DrawArtifact();
		vector<Artifact> fakeArtifacts{ test1, test2, test3 };

		// Creates a choose loot / rng loot
		UIDialogueManager.CreateRewardSelPreset(fakeArtifacts, 3, true);
		break;
	}
	case 2:
	{
		// Go to a specific dialogue/encounter
		UIDialogueManager.CreateDialoguePreset(buttonPath, 3);
		break;
	}
	case 3:
	{
		// Gets max hp (Case 3 - 4)
		for (size_t i = 0; i < GameManager.playerArtifactList.behaviorList_Passive.size(); ++i) {
			if (GameManager.playerArtifactList.behaviorList_Passive[i].ID == 001) {
				GameManager.playerProfile.bonusHp = (float)GameManager.playerArtifactList.behaviorList_Passive[i].count * 10;
			}
		}
		float truemaxhp = GameManager.playerProfile.basemaxhp + GameManager.playerProfile.bonusHp;

		// Heal player by 50%
		GameManager.playerProfile.hp += truemaxhp / 2;

		if (GameManager.playerProfile.hp > truemaxhp)
			GameManager.playerProfile.hp = truemaxhp;
		UIDialogueManager.UIDecision = false;
		UIDialogueManager.SkipDialogue();
		break;
	}
	case 4:
	{
		// Gets max hp (Case 3 - 4)
		for (size_t i = 0; i < GameManager.playerArtifactList.behaviorList_Passive.size(); ++i) {
			if (GameManager.playerArtifactList.behaviorList_Passive[i].ID == 001) {
				GameManager.playerProfile.bonusHp = (float)GameManager.playerArtifactList.behaviorList_Passive[i].count * 10;
			}
		}
		float truemaxhp = GameManager.playerProfile.basemaxhp + GameManager.playerProfile.bonusHp;

		// Check if player can select this button (Can afford price)
		if (GameManager.playerProfile.stardust < DialogueDatabase.fullHealthCost)
		{
			if (button != nullptr)
			{
				button->SetClickable(false);
				button->Owner()->GetComponent<SpriteRenderer>()->SetOpacity(0.5f);
				button->Owner()->GetComponent<TextRenderer>()->SetTextColor(1.0f, 0.f, 0.f);
				break;
			}
		}
		// Heal player by Full by using stardust
		GameManager.playerProfile.stardust -= DialogueDatabase.fullHealthCost;
		GameManager.playerProfile.hp = truemaxhp;
		UIDialogueManager.UIDecision = false;
		UIDialogueManager.SkipDialogue();
		break;
	}
	case 5:
	{
		// Draws random artifact (Case 5)
		unsigned long randoID = ArtifactDatabase.DrawArtifact();

		// Assign to allocated vector
		SaveManager.AddToArtifactList(randoID);
		
		UIDialogueManager.DF_DisplayArtifact(randoID);
		DialogueDatabase.InitDialogueScene(buttonPath);
		break;
	}
	case 6:
	{
		// Draws random legendary artifact (Case 6)
		unsigned long randoID = ArtifactDatabase.DrawLegendary();

		// Assign to allocated vector
		SaveManager.AddToArtifactList(randoID);
		
		UIDialogueManager.DF_DisplayArtifact(randoID);
		DialogueDatabase.InitDialogueScene(buttonPath);
		break;
	}
	case 7:
	{
		// Max healing
		for (size_t i = 0; i < GameManager.playerArtifactList.behaviorList_Passive.size(); ++i) {
			if (GameManager.playerArtifactList.behaviorList_Passive[i].ID == 001) {
				GameManager.playerProfile.bonusHp = (float)GameManager.playerArtifactList.behaviorList_Passive[i].count * 10;
			}
		}
		float truemaxhp = GameManager.playerProfile.basemaxhp + GameManager.playerProfile.bonusHp;

		// Heal player to max
		GameManager.playerProfile.hp = truemaxhp;

		UIDialogueManager.UIDecision = false;
		UIDialogueManager.SkipDialogue();
		break;
	}
	case 8:
	{
		// Take damage
		for (size_t i = 0; i < GameManager.playerArtifactList.behaviorList_Passive.size(); ++i) {
			if (GameManager.playerArtifactList.behaviorList_Passive[i].ID == 001) {
				GameManager.playerProfile.bonusHp = (float)GameManager.playerArtifactList.behaviorList_Passive[i].count * 10;
			}
		}
		float truemaxhp = GameManager.playerProfile.basemaxhp + GameManager.playerProfile.bonusHp;

		// 20%
		GameManager.playerProfile.hp -= GameManager.playerProfile.basemaxhp / 5;

		// Shake camera for effect
		GameManager.CameraShake(1, 50, Vector2(0, 0));

		if (GameManager.playerProfile.hp < 0)
		{
			// Game over
			RemoveDialogue(nullptr);
			GameManager.GameOver();
		}
		UIDialogueManager.UIDecision = false;
		UIDialogueManager.SkipDialogue();
		break;
	}
	case 9:
	{
		// Start Battle
		GameManager.StartBattle(2);
		UIDialogueManager.UIDecision = false;
		UIDialogueManager.SkipDialogue();
		break;
	}
	case 10:
	{
		// Buy random artifact
		if (GameManager.playerProfile.stardust >= 20)
		{
			GameManager.playerProfile.stardust -= 20;
			UIDialogueManager.CreateDialoguePreset("R001", 3);
		}
		else
		{
			UIDialogueManager.CreateDialoguePreset("R002", 3);
		}
		break;
	}
	case 11:
	{
		// Obtain 20 stardust
		GameManager.playerProfile.stardust += 20;
		UIDialogueManager.UIDecision = false;
		UIDialogueManager.SkipDialogue();
		break;
	}
	default:
	{
		// Force close if nothing can happen
		UIDialogueManager.UIDecision = false;
		UIDialogueManager.SkipDialogue();
		break;
	}
	}

	// Reset forceCommand
	DialogueDatabase.forceCommand = "";
}