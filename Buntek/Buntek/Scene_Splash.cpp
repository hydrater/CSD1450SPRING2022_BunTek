#include "Scene_Splash.h"
#include "Scene_MainMenu.h"
#include "AssetManager.h"
#include "AudioEngine.h"

void Scene_Splash::Start(void) 
{
	AssetManager.LoadTexture("Logo/Digipen_Logo.png");
	splash = new GameObject();
	splash->AddComponent<SpriteRenderer>()->SetTransparency(1);
	splashRenderer = splash->GetComponent<SpriteRenderer>();
	splashRenderer->SetTexture("Logo/Digipen_Logo.png");
	splashRenderer->Size(1220, 356);
	splash->transform->SetPosition(Vector2(0, 0));
	splashRenderer->SetTransparency(0);
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
		splashTransform->SetScale(Vector2(splashTransform->worldscale.x + DeltaTime * 0.2f, splashTransform->worldscale.y + DeltaTime * 0.2f));
		splashRenderer->SetTransparency(splashRenderer->GetTransparency() + DeltaTime);
		break;
	case 1:
	{
		/*GameObject* test = new GameObject();
		test->Delete();*/
		if (canPlayAudio)
		{
			AudioManager.LoadSound("splash.mp3");
			AudioManager.PlayClip("splash.mp3");
		}
		canPlayAudio = false;
	}
		break;
	case 2:
		splashRenderer->SetTransparency(splashRenderer->GetTransparency() - DeltaTime);
		break;
	case 3:
		//splashTransform->SetScale(Vector2(splashTransform->worldscale.x + DeltaTime, splashTransform->worldscale.y + DeltaTime));
		//splashTransform->SetPosition(Vector2(0.0f, splashTransform->worldposition.y + DeltaTime * 200));
		
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
	AssetManager.UnloadTexture("Logo/Digipen_Logo.png");
	AudioManager.UnloadSound("splash.mp3");
	splash->Delete();
	//delete splash;
}
