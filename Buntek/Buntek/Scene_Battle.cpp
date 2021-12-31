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

GameObject* test;
GameObject* test2;
GameObject* background, *ball, *friendlyArea, *hostileArea, *neutralArea;

void Scene_Battle::Start(void)
{
	// Setting up the scene
	AudioManager.PlayMusic("Summer.mp3");
	AudioManager.SetMusicVolume(0.1f);

	background = new GameObject();
	background->AddComponent<SpriteRenderer>()->Size(1920, 1080);
	background->GetComponent<SpriteRenderer>()->SetTexture("Background.jpg");

	friendlyArea = new GameObject();
	friendlyArea->AddComponent<SpriteRenderer>()->Size(620, 800);
	friendlyArea->GetComponent<SpriteRenderer>()->SetTexture("BlackTexture.png");
	friendlyArea->GetComponent<SpriteRenderer>()->SetTransparency(0.5f);
	friendlyArea->transform->SetPosition(Vector2(-590, 70));

	neutralArea = new GameObject();
	neutralArea->AddComponent<SpriteRenderer>()->Size(560, 800);
	neutralArea->GetComponent<SpriteRenderer>()->SetTexture("YellowTexture.png");
	neutralArea->GetComponent<SpriteRenderer>()->SetColor(0, 0.5f, 0.5f);
	neutralArea->GetComponent<SpriteRenderer>()->SetTransparency(1.0f);
	neutralArea->transform->SetPosition(Vector2(0, 70));

	hostileArea = new GameObject();
	hostileArea->AddComponent<SpriteRenderer>()->Size(620, 800);
	hostileArea->GetComponent<SpriteRenderer>()->SetTexture("BlackTexture.png");
	hostileArea->GetComponent<SpriteRenderer>()->SetTransparency(0.5f);
	hostileArea->transform->SetPosition(Vector2(590, 70));

	ball = new GameObject();
	ball->AddComponent<SpriteRenderer>()->Size(20, 20);
	ball->GetComponent<SpriteRenderer>()->SetTexture("ball.png");
	ball->GetComponent<SpriteRenderer>()->SetColor(0, 1, 0);
	ball->AddComponent<BallBehavior>()->radius = 10;

	//test = new GameObject();
	//test->AddComponent<SpriteRenderer>()->Size(500, 500);
	//test->transform->SetPosition(Vector2(-500, 10));
	//test->AddComponent<BallBehavior>()->radius = 250;
	//test->transform->Rotate(90);
	//test->AddComponent<CircleCollider>()->radius = 250;
	//test->AddComponent<Cursor>();

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
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
}

