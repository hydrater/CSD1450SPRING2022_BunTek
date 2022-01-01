#include "Scene_Battle.h"
#include "Component.h"
#include "Entity.h"
#include "BallBehavior.h"
#include "SpriteRenderer.h"
#include "Collider2D.h"
#include "System.h"
#include "Cursor.h"
#include "AudioEngine.h"
#include "GameManager.h"

// ------------------------------------ Battle ------------------------------------
GameObject* cursorManager, *origin, *origin2;
GameObject* background, *ball, *friendlyArea, *hostileArea, *neutralArea;

void Scene_Battle::Start(void)
{
	// Setting up the scene
	//AudioManager.PlayMusic("Summer.mp3");
	AudioManager.SetMusicVolume(0.1f);

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

	ball = new GameObject();
	tempRenderer = ball->AddComponent<SpriteRenderer>();
	tempRenderer->Size(20, 20);
	tempRenderer->SetTexture("ball.png");
	tempRenderer->SetColor(0, 1, 0);
	tempBall = ball->AddComponent<BallBehavior>();
	tempBall->radius = 10;
	tempBall->AreaTopBoundary = neutralArea->transform->worldposition.y + neutralArea->GetComponent<SpriteRenderer>()->GetHalfHeight();
	tempBall->AreaBottomBoundary = neutralArea->transform->worldposition.y - neutralArea->GetComponent<SpriteRenderer>()->GetHalfHeight();
	tempBall->AreaLeftBoundary = friendlyArea->transform->worldposition.x - friendlyArea->GetComponent<SpriteRenderer>()->GetHalfWidth();
	tempBall->AreaRightBoundary = hostileArea->transform->worldposition.x + hostileArea->GetComponent<SpriteRenderer>()->GetHalfWidth();

	cursorManager = new GameObject();
	cursorManager->AddComponent<Cursor>();

	origin = new GameObject();
	tempRenderer = origin->AddComponent<SpriteRenderer>();
	tempRenderer->Size(50, 50);
	tempRenderer->SetTexture("ball.png");
	tempRenderer->SetTransparency(1.0f);
	origin->transform->SetPosition(Vector2(0, 0));

	origin2 = new GameObject();
	tempRenderer = origin2->AddComponent<SpriteRenderer>();
	tempRenderer->Size(50, 50);
	tempRenderer->SetTexture("ball.png");
	tempRenderer->SetTransparency(1.0f);
	tempRenderer->SetColor(1, 0 , 0);
	origin2->transform->SetPosition(Vector2(0, 25));

	//test2 = new GameObject();
	//test2->AddComponent<SpriteRenderer>()->Size(500, 500);
	//test2->transform->SetPosition(Vector2(0, 10));
	//test2->AddComponent<BallBehavior>()->radius = 250;
	//test2->AddComponent<CircleCollider>()->radius = 250;
	//test2->AddComponent<Cursor>();
}	

void Scene_Battle::Update(void)
{
    //set background color
	//test->transform->SetPosition(Vector2(test->transform->worldposition.x+1, test->transform->worldposition.y));
	//test2->transform->SetPosition(Vector2(test2->transform->worldposition.x + 1, test2->transform->worldposition.y));
	//test->transform->Rotate(20*DeltaTime);
	origin->transform->Rotate(DeltaTime * 10);

	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
}

