#include "Scene_Battle.h"
#include "Component.h"
#include "Entity.h"
#include "BallBehavior.h"
#include "SpriteRenderer.h"
#include "Collider2D.h"
#include "System.h"

// ------------------------------------ Battle ------------------------------------

GameObject* test;
GameObject* test2;

void Scene_Battle::Start(void)
{
	test = new GameObject();
	test->AddComponent<SpriteRenderer>()->Size(500, 500);
	test->transform->SetPosition(Vector2(-500, 10));
	test->AddComponent<BallBehavior>()->radius = 250;
	test->transform->Rotate(90);
	test->AddComponent<CircleCollider>()->radius = 250;

	test2 = new GameObject();
	test2->AddComponent<SpriteRenderer>()->Size(500, 500);
	test2->transform->SetPosition(Vector2(0, 10));
	test2->AddComponent<BallBehavior>()->radius = 250;
	test2->AddComponent<CircleCollider>()->radius = 250;
}	

void Scene_Battle::Update(void)
{
    //set background color
	//test->transform->SetPosition(Vector2(test->transform->worldposition.x+1, test->transform->worldposition.y));
	//test2->transform->SetPosition(Vector2(test2->transform->worldposition.x + 1, test2->transform->worldposition.y));
	//test->transform->Rotate(20*DeltaTime);
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
}

