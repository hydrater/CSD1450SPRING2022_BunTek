/*!*****************************************************************************
\file BattleHandler.cpp
\author: Goh Kiat Beng (60%)
\co-authors: Algene Tan Chuan Hong (10%), Isaiah Lim Ji Rong (10%), Steven Koe (10%), Bryan Boh Tai Hong (10%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief:File is used for handling of battles
*******************************************************************************/

#include "BattleHandler.h"
#include "SpriteRenderer.h"
#include "Collider2D.h"
#include "System.h"
#include "BattleInput.h"
#include "AudioEngine.h"
#include "AssetManager.h"
#include "GameManager.h"
#include "UI_Hp.h"
#include "SaveManager.h"

BattleHandler::BattleHandler(void) {
}
BattleHandler::~BattleHandler(void) {
	CollisionManager2D.RemoveAll();
	AudioManager.StopMusic();
	AudioManager.UnloadMusic("hysteric.ogg");
	AudioManager.UnloadMusic("www.ogg");
	AudioManager.UnloadSound("Reflect0.wav");
	AudioManager.UnloadSound("Reflect1.wav");
	AudioManager.UnloadSound("Reflect2.wav");

	if (GameManager.GetEnemyType() == 3)
	{
		AssetManager.UnloadTexture("Anim/Face.png");
		AssetManager.UnloadTexture("Anim/FaceShading.png");
		AssetManager.UnloadTexture("Anim/Hand0.png");
		AssetManager.UnloadTexture("Anim/Hand1.png");
		AssetManager.UnloadTexture("Anim/Hand2.png");
		AssetManager.UnloadTexture("Anim/Hand3.png");
		AssetManager.UnloadTexture("Anim/Hand4.png");
		AssetManager.UnloadTexture("Anim/Hand5.png");
		AssetManager.UnloadTexture("Anim/Hand6.png");
	}
}
void BattleHandler::Start(void) {
	

}

void BattleHandler::StartBattle(float _selfHp, float _selfMaxHp, float _enemyHp, float _enemyMaxHp, int enemyHpBarCount) {

	battleStarted = true;
	if (RandIntMinMax(0, 1))
	{
		AudioManager.LoadMusic("hysteric.ogg");
		AudioManager.PlayMusic("hysteric.ogg");
	}
	else
	{
		AudioManager.LoadMusic("www.ogg");
		AudioManager.PlayMusic("www.ogg");
	}

	// Ball sounds
	AudioManager.LoadSound("Reflect0.wav");
	AudioManager.LoadSound("Reflect1.wav");
	AudioManager.LoadSound("Reflect2.wav");

	GameManager.InitBattleProfile(GameManager.playerArtifactList, SaveManager.artifactSaveData);
	SpawnArtifactList(Vector2(-880, -300), SaveManager.artifactSaveData, 1, 1);

	map<unsigned long, int> enemyArtifactList = GameManager.GenerateArtifactList(GameManager.level + 1 * 2 * GameManager.GetEnemyType());
	GameManager.InitBattleProfile(GameManager.enemyArtifactList, enemyArtifactList);
	SpawnArtifactList(Vector2(880, 340), enemyArtifactList, -1, -1);

	ArtifactDatabase.ApplyArtifactBehavior(GameManager.playerArtifactList.behaviorList_Passive, true);
	ArtifactDatabase.ApplyArtifactBehavior(GameManager.enemyArtifactList.behaviorList_Passive, false);

	float selfMaxHp = (_selfMaxHp + GameManager.playerProfile.bonusHp);
	float selfHp = (AEClamp(_selfHp, 0, selfMaxHp));
	float enemyMaxHp = (_enemyMaxHp + GameManager.enemyProfile.bonusHp);
	// Artificial scaling
	enemyMaxHp += GameManager.GetEnemyType() * GameManager.level * 10;
	float enemyHp = enemyMaxHp;

	// Setting up the scene
	GameManager.cameraLerpBack = true;

	inputHandler = new GameObject();
	inputHandler->AddComponent<BattleInput>();
	ballList = &inputHandler->GetComponent<BattleInput>()->ballList;

	SpriteRenderer* tempRenderer;

	background = new GameObject();
	background->AddComponent<SpriteRenderer>()->Size(1920, 1080);
	background->GetComponent<SpriteRenderer>()->SetTexture("Battlescreen.png");
	background->GetComponent<SpriteRenderer>()->SetLayer(-1);

	friendlyArea = new GameObject();
	tempRenderer = friendlyArea->AddComponent<SpriteRenderer>();
	tempRenderer->Size(750, 400);
	tempRenderer->SetTexture("WhiteTexture.png");
	tempRenderer->SetColor(0, 0, 0);
	tempRenderer->SetOpacity(0.5f);
	friendlyArea->transform->SetPosition(Vector2(0, -250));

	neutralArea = new GameObject();
	tempRenderer = neutralArea->AddComponent<SpriteRenderer>();
	tempRenderer->Size(750, 100);
	tempRenderer->SetTexture("WhiteTexture.png");
	tempRenderer->SetColor(0, 0.5f, 0.5f);
	tempRenderer->SetOpacity(0.5f);
	neutralArea->transform->SetPosition(Vector2(0, 0));

	hostileArea = new GameObject();
	tempRenderer = hostileArea->AddComponent<SpriteRenderer>();
	tempRenderer->Size(750, 400);
	tempRenderer->SetTexture("WhiteTexture.png");
	tempRenderer->SetColor(0, 0, 0);
	tempRenderer->SetOpacity(0.5f);
	hostileArea->transform->SetPosition(Vector2(0, 250));

	playerpaddle = new GameObject();
	tempRenderer = playerpaddle->AddComponent<SpriteRenderer>();
	tempRenderer->Size(100, 20);
	tempRenderer->SetTexture("WhiteTexture.png");
	tempRenderer->SetColor(0, 0, 1);
	tempRenderer->SetLayer(2);
	playerpaddle->transform->SetPosition(Vector2(-590, 70));
	playerpaddle->transform->Rotate(0);
	PaddleBehavior* temppaddle = playerpaddle->AddComponent<PaddleBehavior>();
	temppaddle->setplayerpaddle(true);
	temppaddle->setMaxspeed(500 * GameManager.playerProfile.bonusPaddleSpeed);
	temppaddle->sr = tempRenderer;
	BoxCollider* tempcol;
	tempcol = playerpaddle->AddComponent<BoxCollider>();

	inputHandler->GetComponent<BattleInput>()->playerpaddle = temppaddle;

	AIpaddle = new GameObject();
	tempRenderer = AIpaddle->AddComponent<SpriteRenderer>();
	tempRenderer->Size(100, 20);
	tempRenderer->SetTexture("WhiteTexture.png");
	tempRenderer->SetColor(1, 0, 0);
	tempRenderer->SetLayer(2);
	AIpaddle->transform->SetPosition(Vector2(590, 70));
	AIpaddle->transform->Rotate(0);
	temppaddle = AIpaddle->AddComponent<PaddleBehavior>();
	temppaddle->setplayerpaddle(false);
	temppaddle->sr = tempRenderer;
	tempcol = AIpaddle->AddComponent<BoxCollider>();

	inputHandler->GetComponent<BattleInput>()->AIPaddle = temppaddle;

	playercursor = new GameObject();
	CursorBehaviour* tempcursor;
	tempcursor = playercursor->AddComponent<CursorBehaviour>();
	tempcursor->setplayerpossess(true);
	tempcursor->sr = tempRenderer;

	inputHandler->GetComponent<BattleInput>()->playerCursor = tempcursor;

	AIcursor = new GameObject();
	tempcursor = AIcursor->AddComponent<CursorBehaviour>();
	tempcursor->setplayerpossess(false);
	tempcursor->sr = tempRenderer;

	inputHandler->GetComponent<BattleInput>()->AICursor = tempcursor;

	GameManager.areaTopBoundary = hostileArea->transform->worldposition.y + hostileArea->GetComponent<SpriteRenderer>()->GetHalfHeight();
	GameManager.areaBottomBoundary = friendlyArea->transform->worldposition.y - friendlyArea->GetComponent<SpriteRenderer>()->GetHalfHeight();
	GameManager.areaLeftBoundary = friendlyArea->transform->worldposition.x - friendlyArea->GetComponent<SpriteRenderer>()->GetHalfWidth();
	GameManager.areaRightBoundary = friendlyArea->transform->worldposition.x + friendlyArea->GetComponent<SpriteRenderer>()->GetHalfWidth();
	GameManager.friendlyAreaY = friendlyArea->transform->worldposition.y + friendlyArea->GetComponent<SpriteRenderer>()->GetHalfHeight();
	GameManager.hostileAreaY = hostileArea->transform->worldposition.y - hostileArea->GetComponent<SpriteRenderer>()->GetHalfHeight();

	enemyhpBar = new GameObject();
	enemyhpBar->transform->SetPosition(Vector2(660, 400));

	//Set boss to multiple bars
	if (GameManager.GetEnemyType() == 3) {
		enemyHpBarCount = GameManager.level + 1;
		temppaddle->setMaxspeed((250+100* GameManager.level) * GameManager.enemyProfile.bonusPaddleSpeed);
	}
	else {
		enemyHpBarCount = 1;
		temppaddle->setMaxspeed((200 + 50 * GameManager.level) * GameManager.enemyProfile.bonusPaddleSpeed);
	}

	enemyhpBar->AddComponent<UI_Hp>()->GenerateHpBar(false, enemyHp, enemyMaxHp, enemyHpBarCount);

	hpBar = new GameObject();
	hpBar->transform->SetPosition(Vector2(-660, -400));
	hpBar->AddComponent<UI_Hp>()->GenerateHpBar(true, selfHp , selfMaxHp);

	playerBallSpawnTimer = playerBallSpawnTimerMax * GameManager.playerProfile.bonusBallSpawnRate;
	AIBallSpawnTimer = AIBallSpawnTimerMax * GameManager.enemyProfile.bonusBallSpawnRate;

	GameManager.InitBattle(selfHp, enemyHp); // Inits Player and Enemy HP
	GameManager.battleOver = false;
}

void BattleHandler::Update(void) {
	
	if (battleStarted) {
		if (GameManager.optionMenuOpen || GameManager.pauseMenuOpen || GameManager.howToPlayMenuOpen || SceneManager.transitioning) {
			timeScalar = 0;
		}
		else if (hitPauseTimer > 0) {
			hitPauseTimer -= DeltaTime;
			timeScalar = 0;
		}
		else {
			timeScalar = mainTimeScalar;
		}
		
		// Timescale setting
		// Ball Timescale
		for (int i = 0; i < ballList->size(); i++ ) {
			ballList->at(i)->timeScalar = timeScalar;
			if (ballList->at(i)->causeHitPause) {
				ballList->at(i)->causeHitPause = false;
				hitPauseTimer = ballList->at(i)->hitPauseTimer > hitPauseTimer ? ballList->at(i)->hitPauseTimer : hitPauseTimer;
			}
		}
		// AI and paddle timescale
		BattleInput* _bInput = inputHandler->GetComponent<BattleInput>();
		_bInput->timeScalar = timeScalar;
		
		// Status
		for (size_t i = 0; i < GameManager.playerArtifactList.statusEffect.size(); ++i)
		{
			if (GameManager.playerArtifactList.statusEffect[i].statusTimer > 0) {
				GameManager.playerArtifactList.statusEffect[i].statusTimer -= DeltaTime;
			}
			else if (GameManager.playerArtifactList.statusEffect[i].statusCount == 0) {
				GameManager.playerArtifactList.statusEffect.erase(GameManager.playerArtifactList.statusEffect.begin() + i);
			}
		}
		for (size_t i = 0; i < GameManager.enemyArtifactList.statusEffect.size(); ++i)
		{
			if (GameManager.enemyArtifactList.statusEffect[i].statusTimer > 0) {
				GameManager.enemyArtifactList.statusEffect[i].statusTimer -= DeltaTime;
			}
			else if (GameManager.enemyArtifactList.statusEffect[i].statusCount == 0) {
				GameManager.enemyArtifactList.statusEffect.erase(GameManager.enemyArtifactList.statusEffect.begin() + i);
			}
		}

		AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
		playerBallSpawnTimer -= DeltaTime * timeScalar ;
		AIBallSpawnTimer -= DeltaTime * timeScalar;

		if (playerBallSpawnTimer <= 0)
		{
			SpawnBall(true);
			playerBallSpawnTimer = playerBallSpawnTimerMax * GameManager.playerProfile.bonusBallSpawnRate;
		}

		if (AIBallSpawnTimer <= 0)
		{
			SpawnBall(false);
			AIBallSpawnTimer = AIBallSpawnTimerMax * GameManager.enemyProfile.bonusBallSpawnRate;
		}

		//HP Bar Logic
		if (hpBar != 0) {
			hpBar->GetComponent<UI_Hp>()->SetHp(GameManager.playerHp);
		}
		if (enemyhpBar != 0) {
			enemyhpBar->GetComponent<UI_Hp>()->SetHp(GameManager.enemyHp);
		}
	}
	
}
void BattleHandler::SpawnBall(bool isPlayerBall) {
	SpriteRenderer* tempRenderer;
	BallBehavior* tempBall;
	CircleCollider* tempcol;

	ball = new GameObject();
	tempRenderer = ball->AddComponent<SpriteRenderer>();
	tempRenderer->SetLayer(2);
	tempRenderer->Size(20, 20);
	tempRenderer->SetTexture("hdCircle.png");
	tempcol = ball->AddComponent<CircleCollider>();
	tempBall = ball->AddComponent<BallBehavior>();
	tempBall->battleInput = inputHandler->GetComponent<BattleInput>();

	bool dir = isPlayerBall;
	tempBall->playerPossess = !isPlayerBall;
	tempBall->velocity = Vector2(RandFloatMinMax(-1, 1), (float)(dir ? 1 : -1));
	tempBall->velocity.Normalize();
	tempBall->radius = 10;

	tempBall->sr = tempRenderer;
	dir ?  tempRenderer->SetColor(1, 0, 0) : tempRenderer->SetColor(0, 0, 1);
	tempBall->col = tempcol;

	// Set ball spawn position
	if (tempBall->playerPossess) {
		ball->transform->SetPosition(Vector2(playerpaddle->transform->worldposition.x, playerpaddle->transform->worldposition.y+5));
		tempBall->ballDamage += GameManager.playerProfile.bonusDamage;
		tempBall->SetSpeed(tempBall->GetSpeed() * GameManager.playerProfile.bonusBallSpeed);
	}
	else {
		ball->transform->SetPosition(Vector2(AIpaddle->transform->worldposition.x, AIpaddle->transform->worldposition.y - 5));
		tempBall->ballDamage += GameManager.enemyProfile.bonusDamage;
		tempBall->SetSpeed(tempBall->GetSpeed() * GameManager.enemyProfile.bonusBallSpeed);
	}

	GameObject* newParticle = new GameObject();
	ParticleSystem* newSystem = newParticle->AddComponent<ParticleSystem>();
	newParticle->transform->SetPosition(ball->transform->worldposition);
	newSystem->SetEmittingParticle(particlePos, particleSpawnRate, particleAngleSpread, particlePowerMin, particlePowerMax, particleRotationMin,
		particleRotationMax, particleXDimension, particleYDimension, "hdCircle.png", ball->transform->worldposition, particleRenderLayer, (short)AE_GFX_BM_BLEND, false, true);

	tempBall->ballParticle = newParticle;
	tempBall->ballParticleSystem = newSystem;

	ballList->push_back(tempBall);
}

void BattleHandler::SpawnArtifactList(Vector2 pos, map<unsigned long, int> artifactList, float xDir, float yDir)
{
	float i = 0, j = 0;
	for (const auto& kv : artifactList)
	{
		devTools.CreateArtifactObject(pos + Vector2(xOffset * i * xDir, yOffset * j * yDir), kv.first, kv.second, xDir, 5);
		++i;
		if (i >= maxRow)
		{
			i = 0;
			++j;
		}
	}
}
