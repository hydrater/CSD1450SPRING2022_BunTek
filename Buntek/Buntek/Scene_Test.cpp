#include "Scene_Test.h"
#include "AudioEngine.h"
#include "Parallaxer.h"

void Scene_Test::Start(void)
{
	splashimage1 = new GameObject();
	splashimage1->AddComponent<SpriteRenderer>()->SetTransparency(1);
	testRenderer1 = splashimage1->GetComponent<SpriteRenderer>();
	testRenderer1->SetTexture("splash.png");
	testRenderer1->Size(800, 800);
	splashimage1->transform->SetPosition(Vector2(0, 0));
	splashimage1->AddComponent<Parallaxer>()->distance = 15;

	splashimage2 = new GameObject();
	splashimage2->AddComponent<SpriteRenderer>()->SetTransparency(1);
	testRenderer2 = splashimage2->GetComponent<SpriteRenderer>();
	testRenderer2->SetTexture("splash.png");
	testRenderer2->Size(400, 400);
	splashimage2->transform->SetPosition(Vector2(0, 0));
	splashimage2->AddComponent<Parallaxer>()->distance = 10;
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
}

void Scene_Test::Update(void)
{
	//AEGfxSetBlendMode(AE_GFX_BM_ADD);

	
}
