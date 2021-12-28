#include "Scene_Battle.h"
#include "Component.h"
#include "Entity.h"
#include "BallBehavior.h"
#include "SpriteRenderer.h"

// ------------------------------------ Battle ------------------------------------

GameObject* test;
GameObject* test2;

void Battle::Start(void)
{
	test = new GameObject();
	test->AddComponent<SpriteRenderer>()->Size(500, 500);
	//test->RemoveComponent<SpriteRenderer>();
	
	test->transform->SetPosition(Vector2(-500, 10));
	test->AddComponent<BallBehavior>()->Test();
	test2 = new GameObject();
	test2->AddComponent<SpriteRenderer>()->Size(500, 500);
	test2->transform->SetPosition(Vector2(0, 10));
}

void Battle::Update(void)
{
    //set background color
	test->transform->SetPosition(Vector2(test->transform->localposition.x+1, test->transform->localposition.y));
	test2->transform->SetPosition(Vector2(test2->transform->localposition.x + 1, test2->transform->localposition.y));
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
}
