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
#include "UI_Hp.h"

void BtnFuncHover_Artifacts(Button* button);

void Scene_Navigation::Start(void)
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	if (MapData.nodeList.size() == 0)
		MapData.GenerateMapData();

	MapData.GenerateMapObject();

	if (MapData.travelHistoryIDs.size() > 0)
		MapData.DisplayNodeHistory();

	AudioManager.LoadMusic("NavigationBGM.mp3");
	AudioManager.PlayMusic("NavigationBGM.mp3");

	AssetManager.LoadTexture("UI/Start.png");
	AssetManager.LoadTexture("UI/Enemy.png");
	AssetManager.LoadTexture("UI/Elite.png");
	AssetManager.LoadTexture("UI/Encounter.png");
	AssetManager.LoadTexture("UI/Rest.png");
	AssetManager.LoadTexture("UI/Shop.png");
	AssetManager.LoadTexture("UI/Boss.png");
	AssetManager.LoadTexture("UI/Stardust.png");
	AssetManager.LoadTexture("ShopBackground.png");

	splashimage1 = devTools.CreateSpriteGameObject("Static Stars 1.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0), -3);
	splashimage1->AddComponent<AlphaChanger>()->SetOscillation(5.0f, 1.0f, 0.5f, 0);
	splashimage2 = devTools.CreateSpriteGameObject("Static Stars 2.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0), -3);
	splashimage2->AddComponent<AlphaChanger>()->SetOscillation(5.0f, 1.0f, 0.5f, PI);
	splashimage3 = devTools.CreateSpriteGameObject("More Stars 1.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0), -3);
	splashimage3->AddComponent<AlphaChanger>()->SetOscillation(5.0f, 1.0f, 0.5f, 3 * PI / 2);
	splashimage4 = devTools.CreateSpriteGameObject("More Stars 2.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0), -3);
	splashimage4->AddComponent<AlphaChanger>()->SetOscillation(5.0f, 1.0f, 0.5f, PI / 2);
	splashimage5 = devTools.CreateSpriteGameObject("NebulaBig.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0), -3);
	splashimage5->AddComponent<AlphaChanger>()->SetOscillation(6.0f, 1.0f, 0.8f, PI / 2);

	spawner = new GameObject();
	spawner->transform->worldposition = Vector2(0, 0);
	ParticleSystem* _spawnerPs = spawner->AddComponent<ParticleSystem>();

	_spawnerPs->SetScrollingParticle(
		Vector2(-1, 0), 60.0f,
		3960, 1080, "NebulaCloudBig.png",
		Vector2(-3960, 0), -2, (short)AE_GFX_BM_ADD);

	currentArea = devTools.CreateSpriteGameObject("hdCircle.png", MapData.playerTravelDistance * 2, MapData.playerTravelDistance * 2, AE_GFX_BM_BLEND, MapData.currentNode->pos, -2, 0.5f);
	currentArea->GetComponent<SpriteRenderer>()->SetColor(0, 0, 0.1f);

	playerHp = new GameObject();
	playerHp->transform->SetPosition(Vector2(-660.0f, (-AEGetWindowHeight() / 2.25f)));
	playerHp->AddComponent<UI_Hp>()->GenerateHpBar(true, GameManager.playerProfile.hp, GameManager.playerProfile.basemaxhp + GameManager.playerProfile.bonusHp);

	playerCurrency = devTools.CreateSpriteGameObject("WhiteTexture.png", 200, 100, AE_GFX_BM_BLEND, Vector2(AEGetWindowWidth() / 2.5f, -AEGetWindowHeight() / 2.25f), 2, 1);
	SpriteRenderer* tempCurrencySprite = playerCurrency->GetComponent<SpriteRenderer>();
	tempCurrencySprite->SetColor(0.85f, 0.5f, 0.5f);
	GameObject* tempCurrencyIcon = devTools.CreateSpriteGameObject("UI/Stardust.png", 80, 80, AE_GFX_BM_BLEND,
		Vector2(playerCurrency->transform->worldposition.x - 50, playerCurrency->transform->worldposition.y), 3, 1);
	playerCurrencyText = devTools.CreateSpriteGameObject("UI/Stardust.png", 180, 80, AE_GFX_BM_BLEND, Vector2(playerCurrency->transform->worldposition.x + 80, playerCurrency->transform->worldposition.y), 3, 0);
	devTools.AddTextToSpriteGameObject(playerCurrencyText, "Gabriola.ttf", to_string(GameManager.playerProfile.stardust), TextRenderer::xAlignmentTypes::Left, TextRenderer::yAlignmentTypes::Mid, 72.f, 3);
	playerCurrency->AddChild(tempCurrencyIcon);
	playerCurrency->AddChild(playerCurrencyText);

	playerArtifactsBtn = devTools.CreateSpriteGameObject("UI/Button.png", 200, 100, AE_GFX_BM_BLEND, Vector2(AEGetWindowWidth() / 3.5f, -AEGetWindowHeight() / 2.25f), 2, 1);
	TextRenderer* tempText = devTools.AddTextToSpriteGameObject(playerArtifactsBtn, "Gabriola.ttf", "Artifacts", TextRenderer::xAlignmentTypes::Mid, TextRenderer::yAlignmentTypes::Mid, 72.f, 3);
	Button* button = playerArtifactsBtn->AddComponent<Button>();
	button->sr = playerArtifactsBtn->GetComponent<SpriteRenderer>();
	button->tr = tempText;
	button->ButtonEffect = &BtnFuncHover_Artifacts;
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

	if (UIDialogueManager.UIOpen || UIDialogueManager.UIDecision || GameManager.battleRewardPending) {
		playerHp->Deactivate();
		playerCurrency->Deactivate();
		playerArtifactsBtn->Deactivate();
	}
	else {
		playerHp->Activate();
		playerCurrency->Activate();
		playerArtifactsBtn->Activate();
	}

	if (GameManager.battleRewardPending)
	{
		GameManager.battleRewardPending = false;
		Artifact rew1, rew2, rew3;
		rew1.ID = ArtifactDatabase.DrawArtifact();
		rew2.ID = ArtifactDatabase.DrawArtifact();
		rew3.ID = ArtifactDatabase.DrawArtifact();
		vector<Artifact> reward_Artifact{ rew1, rew2, rew3 };
		UIDialogueManager.CreateRewardSelPreset(reward_Artifact, 5, true);
	}
}

void Scene_Navigation::Update(void)
{
	// [To ADD: Node travelling Animation]
	while (MapData.isTravelling)
	{
		MapData.isTravelling = false;
		MapData.Travel(MapData.destinationNode);
		currentArea->transform->SetPosition(MapData.currentNode->pos);
	}

	playerCurrencyText->GetComponent<TextRenderer>()->SetText(to_string(GameManager.playerProfile.stardust));
	playerHp->GetComponent<UI_Hp>()->health = GameManager.playerProfile.hp;
}

void Scene_Navigation::LateUpdate(void)
{
	if (MapData.shopUI && MapData.shopUI->IsActive())
		MapData.shopUI->GetComponent<UI_Shop>()->SetClickable(true);
	UIDialogueManager.SetDialogueClickable(true);
}

Scene_Navigation::~Scene_Navigation(void)
{
	AssetManager.UnloadTexture("UI/Start.png");
	AssetManager.UnloadTexture("UI/Enemy.png");
	AssetManager.UnloadTexture("UI/Elite.png");
	AssetManager.UnloadTexture("UI/Encounter.png");
	AssetManager.UnloadTexture("UI/Rest.png");
	AssetManager.UnloadTexture("UI/Shop.png");
	AssetManager.UnloadTexture("UI/Boss.png");
	AssetManager.UnloadTexture("UI/Stardust.png");
	AssetManager.UnloadTexture("ShopBackground.png");
	AudioManager.UnloadMusic("NavigationBGM.mp3");
	MapData.penaltyZone = nullptr;
}

void BtnFuncHover_Artifacts(Button* button) {
	button->Owner()->GetComponent<SpriteRenderer>()->SetTexture("Menu/Button.png");
	GameManager.DisplayArtifactList();
}