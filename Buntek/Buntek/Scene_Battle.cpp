#include "Scene_Battle.h"
#include "Component.h"
#include "Entity.h"
#include "BallBehavior.h"
#include "SpriteRenderer.h"
#include "Collider2D.h"
#include "System.h"
#include "BattleInput.h"
#include "AudioEngine.h"
#include "GameManager.h"
#include "hisMath.h"

using namespace Math;

// ------------------------------------ Battle ------------------------------------
GameObject* cursorManager;
GameObject* background, *ball, *friendlyArea, *hostileArea, *neutralArea;
vector<BallBehavior*> *ballList;

float ballSpawnTimer = 0, scalingTimer = 0;

void Scene_Battle::Start(void)
{
	// Setting up the scene
	AudioManager.PlayMusic("Evans.mp3");
	AudioManager.SetMusicVolume(0.1f);

	cursorManager = new GameObject();
	cursorManager->AddComponent<BattleInput>();
	ballList = &cursorManager->GetComponent<BattleInput>()->ballList;

	SpriteRenderer* tempRenderer;
	BallBehavior* tempBall;

	background = new GameObject();
	background->AddComponent<SpriteRenderer>()->Size(1920, 1080);
	background->GetComponent<SpriteRenderer>()->SetTexture("Background.jpg");

	friendlyArea = new GameObject();
	tempRenderer = friendlyArea->AddComponent<SpriteRenderer>();
	tempRenderer->Size(620, 800);
	tempRenderer->SetTexture("BlackTexture.png");
	tempRenderer->SetTransparency(0.5f);
	friendlyArea->transform->SetPosition(Vector2(-590, 70));

	neutralArea = new GameObject();
	tempRenderer = neutralArea->AddComponent<SpriteRenderer>();
	tempRenderer->Size(560, 800);
	tempRenderer->SetTexture("YellowTexture.png");
	tempRenderer->SetColor(0, 0.5f, 0.5f);
	tempRenderer->SetTransparency(0.5f);
	neutralArea->transform->SetPosition(Vector2(0, 70));

	hostileArea = new GameObject();
	tempRenderer = hostileArea->AddComponent<SpriteRenderer>();
	tempRenderer->Size(620, 800);
	tempRenderer->SetTexture("BlackTexture.png");
	tempRenderer->SetTransparency(0.5f);
	hostileArea->transform->SetPosition(Vector2(590, 70));

	/*ball = new GameObject();
	tempRenderer = ball->AddComponent<SpriteRenderer>();
	tempRenderer->Size(20, 20);
	tempRenderer->SetTexture("ball.png");
	tempRenderer->SetColor(0, 1, 0);
	tempBall = ball->AddComponent<BallBehavior>();
	tempBall->velocity = Vector2(-1, 0);
	tempBall->radius = 10;
	
	ballList->push_back(tempBall);*/

	GameManager.areaTopBoundary = neutralArea->transform->worldposition.y + neutralArea->GetComponent<SpriteRenderer>()->GetHalfHeight();
	GameManager.areaBottomBoundary = neutralArea->transform->worldposition.y - neutralArea->GetComponent<SpriteRenderer>()->GetHalfHeight();
	GameManager.areaLeftBoundary = friendlyArea->transform->worldposition.x - friendlyArea->GetComponent<SpriteRenderer>()->GetHalfWidth();
	GameManager.areaRightBoundary = hostileArea->transform->worldposition.x + hostileArea->GetComponent<SpriteRenderer>()->GetHalfWidth();
	GameManager.friendlyAreaX = friendlyArea->transform->worldposition.x + hostileArea->GetComponent<SpriteRenderer>()->GetHalfWidth();
	GameManager.hostileAreaX = hostileArea->transform->worldposition.x - hostileArea->GetComponent<SpriteRenderer>()->GetHalfWidth();

	//test2 = new GameObject();
	//test2->AddComponent<SpriteRenderer>()->Size(500, 500);
	//test2->transform->SetPosition(Vector2(0, 10));
	//test2->AddComponent<BallBehavior>()->radius = 250;
	//test2->AddComponent<CircleCollider>()->radius = 250;
	//test2->AddComponent<Cursor>();
}	

void Scene_Battle::Update(void)
{
	ballSpawnTimer -= DeltaTime;
	scalingTimer += DeltaTime;

	if (ballSpawnTimer < 0)
	{
		SpriteRenderer* tempRenderer;
		BallBehavior* tempBall;

		ball = new GameObject();
		tempRenderer = ball->AddComponent<SpriteRenderer>();
		tempRenderer->Size(20, 20);
		tempRenderer->SetTexture("ball.png");
		tempRenderer->SetColor(0, 1, 0);
		tempBall = ball->AddComponent<BallBehavior>();
		bool dir = RandIntMinMax(0, 1);
		tempBall->playerPossess = (dir? true : false);
		tempBall->velocity = Vector2((float) (dir?-1:1), RandFloatMinMax(0, 1));
		tempBall->radius = 10;
		tempBall->SetSpeed(6+(scalingTimer*0.03f));

		ballList->push_back(tempBall);

		ballSpawnTimer = 2- scalingTimer * 0.05f;
	}
	
    //set background color
	//test->transform->SetPosition(Vector2(test->transform->worldposition.x+1, test->transform->worldposition.y));
	//test2->transform->SetPosition(Vector2(test2->transform->worldposition.x + 1, test2->transform->worldposition.y));
	//test->transform->Rotate(20*DeltaTime);

	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
}

