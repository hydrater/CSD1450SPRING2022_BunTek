#include "Scene_Splash.h"
#include "Scene_MainMenu.h"
#include "AudioEngine.h"

void Scene_Splash::Start(void) 
{
	splash = new GameObject();
	splash->AddComponent<SpriteRenderer>()->SetTransparency(1);
	splashRenderer = splash->GetComponent<SpriteRenderer>();
	splashRenderer->SetTexture("splash.png");
	splashRenderer->Size(750,899);
	splash->transform->SetPosition(Vector2(0, 0));
}

void Scene_Splash::Update(void)
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	timer += DeltaTime;
	Transform* splashTransform = splash->transform;

	switch (cycle)
	{
	default:
		
		break;
	case 0:
		splashTransform->SetScale(Vector2(splashTransform->worldscale.x + DeltaTime, splashTransform->worldscale.y + DeltaTime));
		break;
	case 1:
		if (canPlayAudio)
		{
			AudioManager.LoadSound("splash.mp3");
			AudioManager.PlayClip("splash.mp3");
		}
		canPlayAudio = false;
		break;
	case 2:
		splashTransform->SetPosition(Vector2(0.0f, splashTransform->worldposition.y + DeltaTime * 400));
		break;
	case 3:
		splashTransform->SetScale(Vector2(splashTransform->worldscale.x + DeltaTime, splashTransform->worldscale.y + DeltaTime));
		splashTransform->SetPosition(Vector2(0.0f, splashTransform->worldposition.y + DeltaTime * 200));
		splashRenderer->SetTransparency(splashRenderer->GetTransparency() - DeltaTime);
		break;
	case 4:
		SceneManager.LoadScene(new Scene_MainMenu, TransitionType::None, true);
		break;
	}

	if (timer > 1)
	{
		++cycle;
		timer = 0;
	}
}

Scene_Splash::~Scene_Splash(void)
{
	AudioManager.UnloadSound("splash.mp3");
}
