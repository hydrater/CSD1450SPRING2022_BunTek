#include "Scene_Battle.h"
#include "Component.h"
#include "Entity.h"
#include "SpriteRenderer.h"
#include "Collider2D.h"
#include "System.h"
#include "BattleInput2.h"
#include "AudioEngine.h"
#include "GameManager.h"

using namespace Math;

void Scene_Battle::Start(void)
{
	// Setting up the scene
	AudioManager.PlayMusic("Evans.mp3");
	AudioManager.SetMusicVolume(0.1f);

	GameManager.cameraLerpBack = true;

	inputHandler = new GameObject();
	inputHandler->AddComponent<BattleInput2>();
	ballList = &inputHandler->GetComponent<BattleInput2>()->ballList;

	SpriteRenderer* tempRenderer;

	background = new GameObject();
	background->AddComponent<SpriteRenderer>()->Size(1920, 1080);
	background->GetComponent<SpriteRenderer>()->SetTexture("Background.jpg");

	friendlyArea = new GameObject();
	tempRenderer = friendlyArea->AddComponent<SpriteRenderer>();
	tempRenderer->Size(620, 800);
	tempRenderer->SetTexture("WhiteTexture.png");
	tempRenderer->SetColor(0, 0, 0);
	tempRenderer->SetTransparency(0.5f);
	friendlyArea->transform->SetPosition(Vector2(-590, 70));

	neutralArea = new GameObject();
	tempRenderer = neutralArea->AddComponent<SpriteRenderer>();
	tempRenderer->Size(560, 800);
	tempRenderer->SetTexture("WhiteTexture.png");
	tempRenderer->SetColor(0, 0.5f, 0.5f);
	tempRenderer->SetTransparency(0.5f);
	neutralArea->transform->SetPosition(Vector2(0, 70));

	hostileArea = new GameObject();
	tempRenderer = hostileArea->AddComponent<SpriteRenderer>();
	tempRenderer->Size(620, 800);
	tempRenderer->SetTexture("WhiteTexture.png");
	tempRenderer->SetColor(0, 0, 0);
	tempRenderer->SetTransparency(0.5f);
	hostileArea->transform->SetPosition(Vector2(590, 70));

	playerpaddle = new GameObject();
	tempRenderer = playerpaddle->AddComponent<SpriteRenderer>();
	tempRenderer->Size(20, 100);
	tempRenderer->SetTexture("paddle.png");
	tempRenderer->SetColor(0, 0, 1);
	playerpaddle->transform->SetPosition(Vector2(-590, 70));
	PaddleBehavior* temppaddle;
	temppaddle = playerpaddle->AddComponent<PaddleBehavior>();
	temppaddle->setplayerpaddle(true);
	temppaddle->setMaxspeed(1200);
	temppaddle->setMinMoveDist(10);
	temppaddle->sr = tempRenderer;

	inputHandler->GetComponent<BattleInput2>()->playerpaddle = temppaddle;

	AIpaddle = new GameObject();
	tempRenderer = AIpaddle->AddComponent<SpriteRenderer>();
	tempRenderer->Size(20, 100);
	tempRenderer->SetTexture("paddle.png");
	tempRenderer->SetColor(1, 0, 0);
	AIpaddle->transform->SetPosition(Vector2(590, 70));
	temppaddle = AIpaddle->AddComponent<PaddleBehavior>();
	temppaddle->setplayerpaddle(false);
	temppaddle->setMaxspeed(1200);
	temppaddle->setMinMoveDist(10);
	temppaddle->sr = tempRenderer;

	inputHandler->GetComponent<BattleInput2>()->AIPaddle = temppaddle;

	playercursor = new GameObject();
	tempRenderer = playercursor->AddComponent<SpriteRenderer>();
	tempRenderer->Size(50, 50);
	tempRenderer->SetTexture("ball.png");
	tempRenderer->SetColor(0.5f, 0.5f, 1);
	CursorBehaviour* tempcursor;
	tempcursor = playercursor->AddComponent<CursorBehaviour>();
	tempcursor->setplayerpossess(true);
	tempcursor->sr = tempRenderer;

	inputHandler->GetComponent<BattleInput2>()->playerCursor = tempcursor;

	AIcursor = new GameObject();
	tempRenderer = AIcursor->AddComponent<SpriteRenderer>();
	tempRenderer->Size(50, 50);
	tempRenderer->SetTexture("ball.png");
	tempRenderer->SetColor(1, 0.5f, 0.5f);
	tempcursor = AIcursor->AddComponent<CursorBehaviour>();
	tempcursor->setplayerpossess(false);
	tempcursor->sr = tempRenderer;

	inputHandler->GetComponent<BattleInput2>()->AICursor = tempcursor;

	GameManager.areaTopBoundary = neutralArea->transform->worldposition.y + neutralArea->GetComponent<SpriteRenderer>()->GetHalfHeight();
	GameManager.areaBottomBoundary = neutralArea->transform->worldposition.y - neutralArea->GetComponent<SpriteRenderer>()->GetHalfHeight();
	GameManager.areaLeftBoundary = friendlyArea->transform->worldposition.x - friendlyArea->GetComponent<SpriteRenderer>()->GetHalfWidth();
	GameManager.areaRightBoundary = hostileArea->transform->worldposition.x + hostileArea->GetComponent<SpriteRenderer>()->GetHalfWidth();
	GameManager.friendlyAreaX = friendlyArea->transform->worldposition.x + friendlyArea->GetComponent<SpriteRenderer>()->GetHalfWidth();
	GameManager.hostileAreaX = hostileArea->transform->worldposition.x - hostileArea->GetComponent<SpriteRenderer>()->GetHalfWidth();
}	

void Scene_Battle::Update(void)
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	ballSpawnTimer -= DeltaTime;
	scalingTimer += DeltaTime;

	if (ballSpawnTimer < 0)
	{
		SpriteRenderer* tempRenderer;
		BallBehavior* tempBall;

		//Create Trail first (Render Trail before Ball)
		GameObject* tempballTrail = new GameObject();
		SpriteRenderer* tempballTrailRenderer;
		tempballTrailRenderer = tempballTrail->AddComponent<SpriteRenderer>();
		tempballTrailRenderer->Size(20, 20);
		tempballTrailRenderer->SetTexture("Trail.png");
		tempballTrailRenderer->SetColor(1, 1, 1);
		tempballTrailRenderer->SetTransparency(0.5f);

		ball = new GameObject();
		tempRenderer = ball->AddComponent<SpriteRenderer>();
		tempRenderer->Size(20, 20);
		tempRenderer->SetTexture("ball.png");
		tempBall = ball->AddComponent<BallBehavior>();
		//tempBall->battleInput = cursorManager->GetComponent<BattleInput>();
		tempBall->ballTrail = tempballTrail;
		tempBall->srBallTrail = tempballTrailRenderer;
		bool dir = RandIntMinMax(0, 1);
		tempBall->playerPossess = (dir? true : false);
		tempBall->velocity = Vector2((float) (dir?-1:1), RandFloatMinMax(0, 1));
		tempBall->radius = 10;
		tempBall->SetSpeed(tempBall->GetSpeed() +(scalingTimer * 3));
		tempBall->sr = tempRenderer;
		dir ? tempRenderer->SetColor(1, 0, 0) : tempRenderer->SetColor(0, 0, 1);

		ballList->push_back(tempBall);
		
		ballSpawnTimer = 2- scalingTimer * 0.01f;
	}
	
    //set background color
	//test->transform->SetPosition(Vector2(test->transform->worldposition.x+1, test->transform->worldposition.y));
	//test2->transform->SetPosition(Vector2(test2->transform->worldposition.x + 1, test2->transform->worldposition.y));
	//test->transform->Rotate(20*DeltaTime);
}

