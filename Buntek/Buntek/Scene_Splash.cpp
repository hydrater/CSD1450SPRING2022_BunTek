#include "Scene_Splash.h"
#include "Scene_MainMenu.h"
#include "AssetManager.h"
#include "AudioEngine.h"

void Scene_Splash::Start(void) 
{
	AudioManager.LoadSound("SplashLogo.mp3");

	AssetManager.LoadTexture("Logo/Digipen_Logo.png");
	AssetManager.LoadTexture("Logo/BuntekLogo.png");

	splash = new GameObject();
	splash->AddComponent<SpriteRenderer>()->SetOpacity(1);
	splashRenderer = splash->GetComponent<SpriteRenderer>();
	splashRenderer->SetTexture("Logo/Digipen_Logo.png");
	splashRenderer->Size(1220, 358);
	splash->transform->SetPosition(Vector2(0, 0));
	splashRenderer->SetOpacity(0);

	splash2 = new GameObject();
	splash2->AddComponent<SpriteRenderer>()->SetOpacity(1);
	splashRenderer2 = splash2->GetComponent<SpriteRenderer>();
	splashRenderer2->SetTexture("Logo/BuntekLogo.png");
	splashRenderer2->Size(309, 376);
	splash2->transform->SetPosition(Vector2(0, 0));
	splashRenderer2->SetOpacity(0);

	splashTransform = splash->transform;
	splashTransform2 = splash2->transform;
}

void Scene_Splash::Update(void)
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	timer += cycle == 4 ? DeltaTime* 1.2f: DeltaTime;

	switch (cycle)
	{
	default:
		
		break;
	case 0:
		splashTransform->SetScale(splashTransform->worldscale.Lerp(splashTargetScale,0.07f));
		splashRenderer->SetOpacity(splashRenderer->GetOpacity() + DeltaTime);
		break;
	case 1:
	{
		/*GameObject* test = new GameObject();
		test->Delete();*/
	}
		break;
	case 2:
		splashRenderer->SetOpacity(splashRenderer->GetOpacity() - DeltaTime);
		break;
	case 3:
		splashRenderer->SetOpacity(0);
		break;
	case 4:
	{
		if (canPlayAudio)
		{
			AudioManager.PlayClip("SplashLogo.mp3");
			splashRenderer2->SetOpacity(1);
		}

		timer2 += DeltaTime;
		canPlayAudio = false;

		switch (colorType)
		{
		case 0:
			//AEGfxSetBackgroundColor(1.0f, 0.93f, 0.24f);
			AEGfxSetBackgroundColor(0.5f, 0.0f, 0.0f);
			break;

		case 1:
			//AEGfxSetBackgroundColor(0.14f, 0.65f, 1.0f);
			AEGfxSetBackgroundColor(0.0f, 0.0f, 0.5f);
			break;

		case 2:
			//AEGfxSetBackgroundColor(1.0f, 0.29f, 0.89f);
			AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
			break;

		//case 3:
		//	AEGfxSetBackgroundColor(0.1f, 0.8f, 5.5f);
		//	break;

		default:
			break;
		}

		if (timer2 > 0.07f)
		{
			splashTransform2->SetPosition(Vector2(RandIntMinMax(-800, 800), RandIntMinMax(-400, 400)));
			float temp = RandFloatMinMax(0.5f, 3.0f);
			splashTransform2->SetScale(Vector2(temp, temp));
			++colorType;
			timer2 = 0;
		}

		if (colorType == 3)
			colorType = 0;
	}
		break;
	case 5:
		if (resetSplash)
		{
			AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
			splashTransform2->SetPosition(Vector2(0, 0));
			splashTransform2->SetScale(Vector2(1, 1));
			resetSplash = false;
		}
		//Slowly increase size
		splashTransform2->SetScale(splashTransform2->worldscale.Lerp(splash2TargetScale,0.01f));
		break;
	case 6:
		splashTransform2->SetScale(splashTransform2->worldscale.Lerp(splash2TargetScale, 0.005f));
		splashRenderer2->SetOpacity(splashRenderer2->GetOpacity() - DeltaTime);
		break;
	case 7:
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
	AssetManager.UnloadTexture("Logo/BuntekLogo.png");
	AudioManager.UnloadSound("SplashLogo.mp3");
}
