#include "Scene_Test.h"
#include "AudioEngine.h"
#include "GameManager.h"



void Scene_Test::Start(void)
{
	splash = new GameObject();
	splash->AddComponent<SpriteRenderer>()->SetTransparency(1);
	testRenderer = splash->GetComponent<SpriteRenderer>();
	testRenderer->SetTexture("splash.png");
	testRenderer->Size(750, 899);
	splash->transform->SetPosition(Vector2(0, 0));
}

void Scene_Test::Update(void)
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	Transform* splashTransform = splash->transform;

}
