#include "Scene_Battle.h"
#include "Component.h"
#include "Entity.h"
#include "BallBehavior.h"
#include "SpriteRenderer.h"

// ------------------------------------ Battle ------------------------------------

GameObject* test;

void Battle::Start(void)
{
	test = new GameObject();
	test->AddComponent<SpriteRenderer>()->Size(500, 500);
	test->transform->SetPosition(Vector2(-500, 10));
	test->AddComponent<BallBehavior>()->Test();
}

void Battle::Update(void)
{
    //set background color
	test->transform->SetPosition(Vector2(test->transform->localposition.x+1, test->transform->localposition.y));
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
}

void Battle::Render(void)
{
	test->GetComponent<SpriteRenderer>()->Render();
}

void Battle::Free(void)
{
	test->GetComponent<SpriteRenderer>()->Free();
}