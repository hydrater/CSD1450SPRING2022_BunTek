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

	currentArea = devTools.CreateSpriteGameObject("hdCircle.png", MapData.playerTravelDistance * 2, MapData.playerTravelDistance * 2, AE_GFX_BM_BLEND, MapData.currentNode->pos, -3, 0.5f);
	currentArea->GetComponent<SpriteRenderer>()->SetColor(0, 0, 0.1f);

	playerHp = new GameObject();
	playerHp->transform->SetPosition(Vector2(-660.0f, (-AEGetWindowHeight() / 2.25f)));
	for (size_t i = 0; i < GameManager.playerArtifactList.behaviorList_Passive.size(); ++i) {
		if (GameManager.playerArtifactList.behaviorList_Passive[i].ID == 001) {
			GameManager.playerProfile.bonusHp = (float)GameManager.playerArtifactList.behaviorList_Passive[i].count * 10;
		}
	}
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

	playerLocation = devTools.CreateSpriteGameObject("hdCircle.png", 50, 50, AE_GFX_BM_BLEND, MapData.currentNode->pos, -2, 0.5f);
	playerLocation->AddComponent<AlphaChanger>()->SetOscillation(6.f, 0.5f, 0.25f, PI/2.f);
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

	/*if (UIDialogueManager.UIOpen || UIDialogueManager.UIDecision || GameManager.battleRewardPending) {
		playerHp->Deactivate();
		playerCurrency->Deactivate();
		playerArtifactsBtn->Deactivate();
	}
	else {
		playerHp->Activate();
		playerCurrency->Activate();
		playerArtifactsBtn->Activate();
	}*/

	// Needs to be in early update to ensure a smooth transition
	if (GameManager.battleRewardPending)
	{
		GameManager.battleRewardPending = false;
		Artifact rew1, rew2, rew3;
		rew1.ID = ArtifactDatabase.DrawArtifact();
		rew2.ID = ArtifactDatabase.DrawArtifact();
		rew3.ID = ArtifactDatabase.DrawArtifact();
		vector<Artifact> reward_Artifact{ rew1, rew2, rew3 };
		UIDialogueManager.CreateRewardSelPreset(reward_Artifact, (short)10, true);
	}
}

void Scene_Navigation::Update(void)
{
	if (MapData.isTravelling)
	{
		playerLocScale -= playerLocScaleSpeed * (4 * playerLocMaxScale * playerLocScale) * DeltaTime;
		if (playerLocScale < 0.25f)
			playerLocScale = 0.25f;
		//scale = lerpF(scale, targetScale, scaleSpeed);

		playerLocation->transform->SetScale(Vector2(playerLocScale, playerLocScale));

		Vector2 playerPos = playerLocation->transform->worldposition;
		Vector2 targetPos = MapData.destinationNode->nodeObject->transform->worldposition;

		if (!(playerPos.x >= targetPos.x - 0.01f && playerPos.x <= targetPos.x + 0.01f && playerPos.y >= targetPos.y - 0.01f && playerPos.y <= targetPos.y + 0.01f))
		{
			float xDelta = targetPos.x - playerPos.x, yDelta = targetPos.y - playerPos.y;

			float mag = Vector2(xDelta, yDelta).Length();

			if (mag >= playerLocMinMoveDist) {
				playerLocSpeed = playerLocMaxSpeed;
			}
			else {
				playerLocSpeed = (mag / playerLocMinMoveDist) * playerLocMaxSpeed; //(mag)*5;
				mag = mag < playerLocMaxSpeed ? mag : playerLocMaxSpeed;
			}

			if (mag != 0) {
				velocity = Vector2(xDelta / mag, yDelta / mag).Normalize();
				playerLocation->transform->SetPosition(Vector2(playerPos.x + velocity.x * playerLocSpeed * DeltaTime * playerLocTimeScalar, playerPos.y + velocity.y * playerLocSpeed * DeltaTime * playerLocTimeScalar));
				currentArea->transform->SetPosition(playerLocation->transform->worldposition);
			}
		}
		else
		{
			MapData.isTravelling = false;
			MapData.Travel(MapData.destinationNode);
			playerLocation->transform->SetPosition(MapData.currentNode->pos);
			currentArea->transform->SetPosition(MapData.currentNode->pos);
		}
	}
	else
	{
		// Create a Glow Effect
		float scalesign = (playerLocTargetScale == playerLocMaxScale) ? -1.f : 1.f;
		playerLocScale += scalesign * playerLocScaleSpeed * DeltaTime;

		if (playerLocScale >= playerLocMaxScale + 0.01f || playerLocScale <= playerLocMinScale - 0.01f)
			playerLocTargetScale = (playerLocTargetScale == playerLocMaxScale) ? playerLocMinScale : playerLocMaxScale;

		playerLocation->transform->SetScale(Vector2(playerLocScale, playerLocScale));
	}

	playerCurrencyText->GetComponent<TextRenderer>()->SetText(to_string(GameManager.playerProfile.stardust));
	playerHp->GetComponent<UI_Hp>()->health = GameManager.playerProfile.hp;
	for (size_t i = 0; i < GameManager.playerArtifactList.behaviorList_Passive.size(); ++i) {
		if (GameManager.playerArtifactList.behaviorList_Passive[i].ID == 001) {
			GameManager.playerProfile.bonusHp = (float)GameManager.playerArtifactList.behaviorList_Passive[i].count * 10;
		}
	}
	playerHp->GetComponent<UI_Hp>()->maxHealth = (GameManager.playerProfile.basemaxhp + GameManager.playerProfile.bonusHp);
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