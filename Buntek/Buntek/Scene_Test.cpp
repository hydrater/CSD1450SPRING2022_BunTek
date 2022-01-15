#include "Scene_Test.h"
#include "AudioEngine.h"
#include "Parallaxer.h"
#include "AlphaChanger.h"

void Scene_Test::Start(void)
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	splashimage1 = devTools.createSpriteGameObject("Static Stars 1.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0));
	splashimage1->AddComponent<AlphaChanger>()->SetOscillation(5.0f, 1.0f, 0.6f, 3.0f);

	splashimage2 = devTools.createSpriteGameObject("Static Stars 2.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0));
	splashimage2->AddComponent<AlphaChanger>()->SetOscillation(5.0f, 1.0f, 0.6f, 2.0f);

	splashimage3 = devTools.createSpriteGameObject("More Stars 1.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0));
	splashimage3->AddComponent<AlphaChanger>()->SetOscillation(6.0f, 1.0f, 0.6f, 1.0f);

	splashimage4 = devTools.createSpriteGameObject("More Stars 2.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0));
	splashimage4->AddComponent<AlphaChanger>()->SetOscillation(5.5f, 1.0f, 0.6f, 2.6f);

	splashimage5 = devTools.createSpriteGameObject("NebulaBig.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0));
	splashimage6 = devTools.createSpriteGameObject("NebulaCloudBig.png", 3960, 1080, AE_GFX_BM_ADD, Vector2(0, 0));
	//splashimage1->AddComponent<Parallaxer>()->distance = 50;
	
	
}

void Scene_Test::Update(void)
{
	Vector2 addPos = Vector2((float)(0.5f * DeltaTime), (float)0);
	//splashimage3->transform->worldposition += addPos;
	
}
