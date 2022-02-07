#include "BattleHandler.h"
#include "SpriteRenderer.h"
#include "Collider2D.h"
#include "System.h"
#include "BattleInput.h"
#include "AudioEngine.h"
#include "GameManager.h"
#include "UI_Hp.h"
#include "Scene_Battle.h"
#include "Component.h"
#include "Entity.h"

BattleHandler::BattleHandler(void) {
	
}
BattleHandler::~BattleHandler(void) {
	CollisionManager2D.RemoveAll();
	AudioManager.StopMusic();
	AudioManager.UnloadMusic("Dream.ogg");
	AudioManager.UnloadMusic("www.ogg");
}
void BattleHandler::Start(void) {
	

}

void BattleHandler::StartBattle(void) {
	battleStarted = true;
	if (RandIntMinMax(0, 1))
	{
		AudioManager.LoadMusic("Dream.ogg");
		AudioManager.PlayMusic("Dream.ogg");
	}
	else
	{
		AudioManager.LoadMusic("www.ogg");
		AudioManager.PlayMusic("www.ogg");
	}
	
	AudioManager.SetMusicVolume(0.1f);

	// Setting up the scene
	GameManager.cameraLerpBack = true;

	inputHandler = new GameObject();
	inputHandler->AddComponent<BattleInput>();
	ballList = &inputHandler->GetComponent<BattleInput>()->ballList;

	SpriteRenderer* tempRenderer;

	background = new GameObject();
	background->AddComponent<SpriteRenderer>()->Size(1920, 1080);
	background->GetComponent<SpriteRenderer>()->SetTexture("Background.jpg");
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
	tempRenderer->SetTexture("paddle.png");
	tempRenderer->SetColor(0, 0, 1);
	tempRenderer->SetLayer(1);
	playerpaddle->transform->SetPosition(Vector2(-590, 70));
	playerpaddle->transform->Rotate(0);
	PaddleBehavior* temppaddle = playerpaddle->AddComponent<PaddleBehavior>();
	temppaddle->setplayerpaddle(true);
	temppaddle->setMaxspeed(500);
	temppaddle->sr = tempRenderer;
	BoxCollider* tempcol;
	tempcol = playerpaddle->AddComponent<BoxCollider>();

	inputHandler->GetComponent<BattleInput>()->playerpaddle = temppaddle;

	AIpaddle = new GameObject();
	tempRenderer = AIpaddle->AddComponent<SpriteRenderer>();
	tempRenderer->Size(100, 20);
	tempRenderer->SetTexture("paddle.png");
	tempRenderer->SetColor(1, 0, 0);
	tempRenderer->SetLayer(1);
	AIpaddle->transform->SetPosition(Vector2(590, 70));
	AIpaddle->transform->Rotate(0);
	temppaddle = AIpaddle->AddComponent<PaddleBehavior>();
	temppaddle->setplayerpaddle(false);
	temppaddle->setMaxspeed(500);
	temppaddle->sr = tempRenderer;
	tempcol = AIpaddle->AddComponent<BoxCollider>();

	inputHandler->GetComponent<BattleInput>()->AIPaddle = temppaddle;

	playercursor = new GameObject();
	tempRenderer = playercursor->AddComponent<SpriteRenderer>();
	tempRenderer->Size(50, 50);
	tempRenderer->SetTexture("ball.png");
	tempRenderer->SetColor(0.5f, 0.5f, 1);
	CursorBehaviour* tempcursor;
	tempcursor = playercursor->AddComponent<CursorBehaviour>();
	tempcursor->setplayerpossess(true);
	tempcursor->sr = tempRenderer;

	inputHandler->GetComponent<BattleInput>()->playerCursor = tempcursor;

	AIcursor = new GameObject();
	tempRenderer = AIcursor->AddComponent<SpriteRenderer>();
	tempRenderer->Size(50, 50);
	tempRenderer->SetTexture("ball.png");
	tempRenderer->SetColor(1, 0.5f, 0.5f);
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


	GameManager.InitBattle(100, 100); // Inits Player and Enemy HP
}


void BattleHandler::Update(void) {
	

	if (battleStarted) {
		
		if (hitPauseTimer > 0) {
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
		
		
		AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
		ballSpawnTimer -= DeltaTime * timeScalar;
		scalingTimer += DeltaTime * timeScalar;
		if (ballSpawnTimer < 0)
		{
			SpriteRenderer* tempRenderer;
			BallBehavior* tempBall;
			CircleCollider* tempcol;


			ball = new GameObject();
			tempRenderer = ball->AddComponent<SpriteRenderer>();
			tempRenderer->SetLayer(2);
			tempRenderer->Size(20, 20);
			tempRenderer->SetTexture("ball.png");
			tempcol = ball->AddComponent<CircleCollider>();
			tempBall = ball->AddComponent<BallBehavior>();
			tempBall->battleInput = inputHandler->GetComponent<BattleInput>();
			
			bool dir = RandIntMinMax(0, 1);
			tempBall->playerPossess = (dir ? true : false);
			tempBall->velocity = Vector2(RandFloatMinMax(-1, 1), (float)(dir ? -1 : 1));
			tempBall->velocity.Normalize();
			tempBall->radius = 10;
			tempBall->SetSpeed(tempBall->GetSpeed());
			tempBall->sr = tempRenderer;
			dir ? tempRenderer->SetColor(1, 0, 0) : tempRenderer->SetColor(0, 0, 1);
			tempBall->col = tempcol;

			ballList->push_back(tempBall);

			ballSpawnTimer = 2 - scalingTimer * 0.01f;
		}
		
	}
	
}
