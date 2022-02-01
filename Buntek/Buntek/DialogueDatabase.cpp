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
		AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
		GameObject* splashimage1 = 0;
		GameObject* splashimage2 = 0;
		GameObject* splashimage3 = 0;
		GameObject* splashimage4 = 0;
		GameObject* splashimage5 = 0;
		GameObject* splashimage6 = 0;
		GameObject* spawner = 0;
		splashimage1 = devTools.CreateSpriteGameObject("Static Stars 1.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0));
		splashimage1->AddComponent<AlphaChanger>()->SetOscillation(5.0f, 1.0f, 0.5f, 0);
		splashimage2 = devTools.CreateSpriteGameObject("Static Stars 2.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0));
		splashimage2->AddComponent<AlphaChanger>()->SetOscillation(5.0f, 1.0f, 0.5f, PI);
		splashimage3 = devTools.CreateSpriteGameObject("More Stars 1.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0));
		splashimage3->AddComponent<AlphaChanger>()->SetOscillation(5.0f, 1.0f, 0.5f, 3 * PI / 2);
		splashimage4 = devTools.CreateSpriteGameObject("More Stars 2.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0));
		splashimage4->AddComponent<AlphaChanger>()->SetOscillation(5.0f, 1.0f, 0.5f, PI / 2);
		splashimage5 = devTools.CreateSpriteGameObject("NebulaBig.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0));
		splashimage5->AddComponent<AlphaChanger>()->SetOscillation(6.0f, 1.0f, 0.8f, PI / 2);
		//splashimage6 = devTools.CreateSpriteGameObject("NebulaCloudBig.png", 3960, 1080, AE_GFX_BM_BLEND, Vector2(0, 0),(short)1);
		//splashimage1->AddComponent<Parallaxer>()->distance = 50;

		spawner = new GameObject();
		spawner->transform->worldposition = Vector2(0, 0);
		ParticleSystem* _spawnerPs = spawner->AddComponent<ParticleSystem>();

		_spawnerPs->SetScrollingParticle(
			Vector2(-1, 0), 60.0f,
			3960, 1080, "NebulaCloudBig.png",
			Vector2(-3960, 0), 1, (short)AE_GFX_BM_ADD);
	}
		break;
	default:
		break;
	}
}
