#include "Scene_Battle.h"
#include "Component.h"
#include "Entity.h"
#include "BallBehavior.h"
#include "SpriteRenderer.h"

// ------------------------------------ Battle ------------------------------------

Entity* test;

void Battle::Awake(void)
{
	
}

void Battle::Start(void)
{
	test = new Entity();
	test->AddComponent<SpriteRenderer>()->Size(100, 100);
	test->AddComponent<BallBehavior>()->Test();
}

void Battle::Update(void)
{
    //set background color
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