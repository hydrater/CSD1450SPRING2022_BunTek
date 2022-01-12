#include "Scene_Test.h"
#include "AudioEngine.h"
#include "Parallaxer.h"

void Scene_Test::Start(void)
{
	splashimage2 = new GameObject();
	splashimage2->AddComponent<SpriteRenderer>()->SetTransparency(1);
	testRenderer2 = splashimage2->GetComponent<SpriteRenderer>();
	testRenderer2->SetTexture("Stars3.png");
	testRenderer2->Size(1920 * 1.1, 1080 * 1.1);
	testRenderer2->SetBlendMode(AE_GFX_BM_ADD);
	splashimage2->transform->SetPosition(Vector2(0, 0));
	splashimage2->AddComponent<Parallaxer>()->distance = 50;
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	splashimage2 = new GameObject();
	splashimage2->AddComponent<SpriteRenderer>()->SetTransparency(1);
	testRenderer2 = splashimage2->GetComponent<SpriteRenderer>();
	testRenderer2->SetTexture("Stars2.png");
	testRenderer2->Size(1920*1.1, 1080 * 1.1);
	testRenderer2->SetBlendMode(AE_GFX_BM_ADD);
	splashimage2->transform->SetPosition(Vector2(0, 0));
	splashimage2->AddComponent<Parallaxer>()->distance = 30;

	/*splashimage1 = new GameObject();
	splashimage1->AddComponent<SpriteRenderer>()->SetTransparency(1);
	testRenderer1 = splashimage1->GetComponent<SpriteRenderer>();
	testRenderer1->SetTexture("Stars1.png");
	testRenderer2->SetBlendMode(AE_GFX_BM_ADD);
	testRenderer1->Size(1920, 1080);
	splashimage1->transform->SetPosition(Vector2(0, 0));
	splashimage1->AddComponent<Parallaxer>()->distance = 12;*/

	

	
}

void Scene_Test::Update(void)
{
	Vector2 addPos = Vector2((float)(10 * DeltaTime), (float)0);
	splashimage2->GetComponent<Parallaxer>()->anchorPoint += addPos;
	
}
