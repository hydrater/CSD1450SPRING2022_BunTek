#include "Scene_Test.h"
#include "AudioEngine.h"
#include "Parallaxer.h"

void Scene_Test::Start(void)
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	splashimage1 = devTools.createSpriteGameObject("Stars3.png", 1920 * 1.1, 1080 * 1.1, AE_GFX_BM_ADD, Vector2(0, 0));
	splashimage1->AddComponent<Parallaxer>()->distance = 50;
	
	/*
	splashimage2 = new GameObject();
	splashimage2->AddComponent<SpriteRenderer>()->SetTransparency(1);
	testRenderer2 = splashimage2->GetComponent<SpriteRenderer>();
	testRenderer2->SetStretch(0.3f, 1.0f, 1.0f, 1.0f);
	testRenderer2->SetTexture("splash.png");
	testRenderer2->Size(300, 300);
	testRenderer2->SetLayer(100);

	//testRenderer2->SetTexture("Stars2.png");
	//testRenderer2->Size(1920*1.1, 1080 * 1.1);
	//testRenderer2->SetBlendMode(AE_GFX_BM_ADD);
	//testRenderer2->SetBlendMode(AE_GFX_BM_BLEND);
	splashimage2->transform->SetPosition(Vector2(0, 0));
	splashimage2->AddComponent<Parallaxer>()->distance = 30;

	splashimage3 = new GameObject();
	splashimage3->AddComponent<SpriteRenderer>()->SetTransparency(1);
	testRenderer3 = splashimage3->GetComponent<SpriteRenderer>();
	testRenderer3->SetTexture("More Stars 1.png");
	testRenderer3->SetBlendMode(AE_GFX_BM_ADD);
	testRenderer3->Size(3960, 1080);
	splashimage3->transform->SetPosition(Vector2(-990, 0));

	splashimage3 = new GameObject();
	splashimage3->AddComponent<SpriteRenderer>()->SetTransparency(1);
	testRenderer3 = splashimage3->GetComponent<SpriteRenderer>();
	testRenderer3->SetTexture("More Stars 2.png");
	testRenderer3->SetBlendMode(AE_GFX_BM_ADD);
	testRenderer3->Size(3960, 1080);
	splashimage3->transform->SetPosition(Vector2(-990, 0));

	splashimage3 = new GameObject();
	splashimage3->AddComponent<SpriteRenderer>()->SetTransparency(1);
	testRenderer3 = splashimage3->GetComponent<SpriteRenderer>();
	testRenderer3->SetTexture("Static Stars 1.png");
	testRenderer3->SetBlendMode(AE_GFX_BM_ADD);
	testRenderer3->Size(3960, 1080);
	splashimage3->transform->SetPosition(Vector2(-990, 0));

	splashimage3 = new GameObject();
	splashimage3->AddComponent<SpriteRenderer>()->SetTransparency(1);
	testRenderer3 = splashimage3->GetComponent<SpriteRenderer>();
	testRenderer3->SetTexture("Static Stars 1.png");
	testRenderer3->SetBlendMode(AE_GFX_BM_ADD);
	testRenderer3->Size(3960, 1080);
	splashimage3->transform->SetPosition(Vector2(-990, 0));

	*/
}

void Scene_Test::Update(void)
{
	Vector2 addPos = Vector2((float)(0.5f * DeltaTime), (float)0);
	//splashimage3->transform->worldposition += addPos;
	
}
