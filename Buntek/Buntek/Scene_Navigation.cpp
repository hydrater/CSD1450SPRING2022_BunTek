#include "Scene_Navigation.h"
#include "GameManager.h"
#include "Component.h"
#include "SpriteRenderer.h"
#include "AssetManager.h"
#include "AudioEngine.h"
#include "MapGenerator.h"
#include "UI_Shop.h"
#include "UI_DialogueHandler.h"
#include "AlphaChanger.h"
#include "ParticleSystem.h"

void Scene_Navigation::Start(void)
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	if (MapData.nodeList.size() == 0)
		MapData.GenerateMapData();

	MapData.GenerateMapObject();

	if (MapData.travelHistoryIDs.size() > 0)
		MapData.DisplayNodeHistory();

	MapData.DisplayNodeRoutes(MapData.playerTravelDistance);
	AudioManager.LoadMusic("NavigationBGM.mp3");
	AudioManager.PlayMusic("NavigationBGM.mp3");
	AudioManager.SetMusicVolume(0.5f);

	AssetManager.LoadTexture("UI/Enemy.png");
	AssetManager.LoadTexture("UI/Elite.png");
	AssetManager.LoadTexture("UI/Encounter.png");
	AssetManager.LoadTexture("UI/Rest.png");
	AssetManager.LoadTexture("UI/Shop.png");
	AssetManager.LoadTexture("UI/Boss.png");

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

	spawner = new GameObject();
	spawner->transform->worldposition = Vector2(0, 0);
	ParticleSystem* _spawnerPs = spawner->AddComponent<ParticleSystem>();

	_spawnerPs->SetScrollingParticle(
		Vector2(-1, 0), 60.0f,
		3960, 1080, "NebulaCloudBig.png",
		Vector2(-3960, 0), 1, (short)AE_GFX_BM_ADD);
}

// Draw all lines
void Scene_Navigation::EarlyUpdate(void)
{	
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition(0.0f, 0.0f);
	MapData.DisplayNodeRoutes(MapData.playerTravelDistance);

	//Draw connected lines
	for (int i = 0; i < MapData.connectedLines.size(); i++)
	{
		AEGfxMeshDraw(MapData.connectedLines[i], AE_GFX_MDM_LINES_STRIP);
	}
	for (int i = 0; i < MapData.travelHistoryLines.size(); i++)
	{
		AEGfxMeshDraw(MapData.travelHistoryLines[i], AE_GFX_MDM_LINES_STRIP);
	}
}

void Scene_Navigation::Update(void)
{
	// [To ADD: Node travelling Animation]
	while (MapData.isTravelling)
	{
		MapData.isTravelling = false;
		MapData.Travel(MapData.destinationNode);
	}
}

void Scene_Navigation::LateUpdate(void)
{
	if (MapData.shopUI && MapData.shopUI->IsActive())
		MapData.shopUI->GetComponent<UI_Shop>()->SetClickable(true);
	UIDialogueManager.SetDialogueClickable(true);
}

Scene_Navigation::~Scene_Navigation(void)
{
	AssetManager.UnloadTexture("UI/Enemy.png");
	AssetManager.UnloadTexture("UI/Elite.png");
	AssetManager.UnloadTexture("UI/Encounter.png");
	AssetManager.UnloadTexture("UI/Rest.png");
	AssetManager.UnloadTexture("UI/Shop.png");
	AssetManager.UnloadTexture("UI/Boss.png");
	AudioManager.UnloadMusic("NavigationBGM.mp3");
}
