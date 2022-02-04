#include "Scene_MainMenu.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "Scene_Navigation.h"
#include "UI_Shop.h"
#include "AssetManager.h"
#include "GameManager.h"
#include "AudioEngine.h"
#include "Parallaxer.h"
#include "Devtools.h"

void BtnFunc_Start(Button* button);
void BtnFunc_Options(Button* button);
void BtnFunc_Quit(Button* button);
void BtnFuncHover_Start(Button* button);
void BtnFuncHover_Options(Button* button);
void BtnFuncHover_Quit(Button* button);
void BtnFuncUnhover_Start(Button* button);
void BtnFuncUnHover_Options(Button* button);
void BtnFuncUnHover_Quit(Button* button);

Scene_MainMenu* Scene_MainMenu::instance = 0;

void Scene_MainMenu::Start(void)
{
	Scene_MainMenu::instance = this;
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	AudioManager.LoadSound("ButtonHover.mp3");
	AudioManager.LoadMusic("www.ogg");
	AudioManager.PlayMusic("www.ogg");
	AudioManager.SetMusicVolume(0.05f);

	AssetManager.LoadTexture("Menu/MainMenuArt.png");
	AssetManager.LoadTexture("Menu/MainMenuFull.png");
	AssetManager.LoadTexture("Menu/PolkaSquare.png");
	AssetManager.LoadTexture("Menu/Button.png");
	AssetManager.LoadTexture("Menu/ButtonPressed.png");
	AssetManager.LoadTexture("Menu/Disc.png");
	AssetManager.LoadTexture("Menu/Fake.png");
	AssetManager.LoadTexture("Menu/Bottom.png");

	background = new GameObject();
	background->AddComponent<SpriteRenderer>()->Size(1920, 1080);
	background->GetComponent<SpriteRenderer>()->SetTexture("Menu/MainMenuFull.png");
	background->GetComponent<SpriteRenderer>()->SetLayer(-1);
	background->AddComponent<Parallaxer>()->distance = 150.0f;

	MainMenu = new GameObject();
	MainMenu->transform->SetPosition(Vector2(-100, 0));
	polkaDotter = MainMenu->AddComponent<SpriteRenderer>();
	polkaDotter->Size(1900, 1100);
	polkaDotter->SetTexture("Menu/PolkaSquare.png");
	polkaDotter->SetLayer(-2);
	polkaDotter->SetTransparency(0);

	startBtn = new GameObject();
	SpriteRenderer* tempRenderer;
	tempRenderer = startBtn->AddComponent<SpriteRenderer>();
	tempRenderer->Size(471, 71);
	tempRenderer->SetTexture("Menu/Button.png");
	TextRenderer* tempTextRenderer;
	tempTextRenderer = startBtn->AddComponent<TextRenderer>();
	tempTextRenderer->SetFont("GothicA1.ttf");
	tempTextRenderer->SetLayer(1);
	tempTextRenderer->SetTextColor(0, 0, 0);
	tempTextRenderer->SetText("Start");
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
	startBtn->transform->SetPosition(Vector2(-670, -200));
	Button* button;
	button = startBtn->AddComponent<Button>();
	button->sr = tempRenderer;
	button->tr = tempTextRenderer;
	button->ButtonEffect = &BtnFunc_Start;
	button->HoverEffect = &BtnFuncHover_Start;
	button->NotHoverEffect = &BtnFuncUnhover_Start;

	optionBtn = new GameObject();
	tempRenderer = optionBtn->AddComponent<SpriteRenderer>();
	tempRenderer->Size(471, 71);
	tempRenderer->SetTexture("Menu/Button.png");
	tempTextRenderer = optionBtn->AddComponent<TextRenderer>();
	tempTextRenderer->SetFont("GothicA1.ttf");
	tempTextRenderer->SetLayer(1);
	tempTextRenderer->SetTextColor(0, 0, 0);
	tempTextRenderer->SetText("Options");
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
	optionBtn->transform->SetPosition(Vector2(-670, -300));
	button = optionBtn->AddComponent<Button>();
	button->sr = tempRenderer;
	button->tr = tempTextRenderer;
	button->ButtonEffect = &BtnFunc_Options;
	button->HoverEffect = &BtnFuncHover_Options;
	button->NotHoverEffect = &BtnFuncUnHover_Options;

	quitBtn = new GameObject();
	tempRenderer = quitBtn->AddComponent<SpriteRenderer>();
	tempRenderer->Size(471, 71);
	tempRenderer->SetTexture("Menu/Button.png");
	tempTextRenderer = quitBtn->AddComponent<TextRenderer>();
	tempTextRenderer->SetFont("GothicA1.ttf");
	tempTextRenderer->SetLayer(1);
	tempTextRenderer->SetTextColor(0, 0, 0);
	tempTextRenderer->SetText("Quit");
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
	quitBtn->transform->SetPosition(Vector2(-670, -400));
	button = quitBtn->AddComponent<Button>();
	button->sr = tempRenderer;
	button->tr = tempTextRenderer;
	button->ButtonEffect = &BtnFunc_Quit;
	button->HoverEffect = &BtnFuncHover_Quit;
	button->NotHoverEffect = &BtnFuncUnHover_Quit;

	disc = devTools.CreateSpriteGameObject("Menu/Disc.png", 400, 400, AE_GFX_BM_BLEND, Vector2(900, -420), 2)->transform;
	disc->SetScale(Vector2(0, 0));

	fake = devTools.CreateSpriteGameObject("Menu/Fake.png", 2800, 1900, AE_GFX_BM_BLEND, Vector2(0, 0), 0)->transform;
	fake->SetRotation(-180);
	fake->SetScale(Vector2(2, 2));

	bottom = devTools.CreateSpriteGameObject("Menu/Bottom.png", 1920, 83, AE_GFX_BM_BLEND, Vector2(0, -490), 0)->transform;
	bottom->SetScale(Vector2(0.0f, 2.0f));

	// Load save data
	//SaveManager.LoadData();
}

void Scene_MainMenu::Update(void)
{
	animTimer += DeltaTime;
	Vector2 temp = polkaDotter->GetTextureOffset();
	temp.x -= DeltaTime * 0.1f;
	temp.y += DeltaTime * 0.1f;
	polkaDotter->SetTextureOffset(Vector2(temp.x, temp.y));
	disc->Rotate(DeltaTime * 20);

	if (animTimer < 1)
	{
		GameManager.disableInteraction = true;
		fake->Translate(Vector2(DeltaTime * -450.0f, -400.0f * DeltaTime));
		fake->Rotate(DeltaTime * 180.1f);
		fake->SetScale(Vector2(fake->worldscale.x -= DeltaTime, fake->worldscale.y -= DeltaTime));

		if (animTimer <= 0.8f)
		{
			disc->Scale(DeltaTime * 4);
			bottom->worldscale += Vector2(DeltaTime * 1.25f, 0.0f);
		}
		else
		{
			disc->Scale(DeltaTime * -10);
			bottom->worldscale -= Vector2(0.0f, DeltaTime * 5.0f);
		}
			
	}
	else if (!finishedSetup)
	{
		polkaDotter->SetTransparency(1);
		fake->Owner()->GetComponent<SpriteRenderer>()->SetTransparency(0);
		background->GetComponent<SpriteRenderer>()->SetTexture("Menu/MainMenuArt.png");
		AssetManager.UnloadTexture("Menu/MainMenuFull.png");
		AssetManager.UnloadTexture("Menu/Fake.png");
		disc->SetScale(Vector2(1, 1));
		bottom->SetScale(Vector2(1, 1));

		displayTxt = bottom->Owner()->AddComponent<TextRenderer>();
		displayTxt->SetFont("GothicA1.ttf");
		displayTxt->SetText("BOTTOM");
		displayTxt->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
		displayTxt->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
		displayTxt->SetLayer(4);
		displayTxt->SetFontScale(0.8f);
		displayTxt->SetTextColor(1.0f, 0.93f, 0.24f);

		GameManager.disableInteraction = false;
		finishedSetup = true;
	}
}

Scene_MainMenu::~Scene_MainMenu(void)
{
	AudioManager.UnloadSound("ButtonHover.mp3");
	AudioManager.UnloadMusic("www.ogg");
	AssetManager.UnloadTexture("Menu/MainMenu.png");
	AssetManager.UnloadTexture("Menu/PolkaSquare.png");
	AssetManager.UnloadTexture("Menu/Button.png");
	AssetManager.UnloadTexture("Menu/ButtonPressed.png");
	AssetManager.UnloadTexture("Menu/Disc.png");
	AssetManager.UnloadTexture("Menu/Bottom.png");
	instance = NULL;
}

GameObject* Scene_MainMenu::GetObjRef(short type)
{
	if (type == 0)
	{
		return startBtn;
	}
	else
	{
		if (type == 1)
			return optionBtn;
		else
			return quitBtn;
	}
}

void BtnFunc_Start(Button* button)
{
	SceneManager.LoadScene(new Scene_Navigation, TransitionType::FadeTransition, true);
}

void BtnFunc_Options(Button* button)
{
	
}

void BtnFunc_Quit(Button* button)
{
	// Should have a "are you sure?"
	GameManager.exit = true;
}

void BtnFuncHover_Start(Button* button)
{
	if (menu->startPlay)
	{
		AudioManager.PlayClip("ButtonHover.mp3");
		button->Owner()->GetComponent<SpriteRenderer>()->SetTexture("Menu/ButtonPressed.png");
		menu->displayTxt->SetText("Start the game");
		cout << menu->displayTxt << endl;
		menu->startPlay = false;
	}

	Vector2 temp = menu->battleBtnPos;
	temp.x = menu->GetObjRef(0)->transform->worldposition.x >= -650 ? -650 : menu->GetObjRef(0)->transform->worldposition.x + DeltaTime * 150;
	menu->GetObjRef(0)->transform->SetPosition(temp);
}

void BtnFuncHover_Options(Button* button)
{
	if (menu->optionPlay)
	{
		AudioManager.PlayClip("ButtonHover.mp3");
		button->Owner()->GetComponent<SpriteRenderer>()->SetTexture("Menu/ButtonPressed.png");
		menu->displayTxt->SetText("Edit the game's settings");
		menu->optionPlay = false;
	}

	Vector2 temp = menu->optionBtnPos;
	temp.x = menu->GetObjRef(1)->transform->worldposition.x >= -650 ? -650 : menu->GetObjRef(1)->transform->worldposition.x + DeltaTime * 150;
	menu->GetObjRef(1)->transform->SetPosition(temp);
}

void BtnFuncHover_Quit(Button* button)
{
	if (menu->quitPlay)
	{
		AudioManager.PlayClip("ButtonHover.mp3");
		button->Owner()->GetComponent<SpriteRenderer>()->SetTexture("Menu/ButtonPressed.png");
		menu->displayTxt->SetText("Exit the game");
		menu->quitPlay = false;
	}

	Vector2 temp = menu->quitBtnPos;
	temp.x = menu->GetObjRef(2)->transform->worldposition.x >= -650 ? -650 : menu->GetObjRef(2)->transform->worldposition.x + DeltaTime * 150;
	menu->GetObjRef(2)->transform->SetPosition(temp);
}

void BtnFuncUnhover_Start(Button* button)
{
	if (!menu->startPlay)
	{
		if (menu->displayTxt != NULL)
			menu->displayTxt->SetText("");
		button->Owner()->GetComponent<SpriteRenderer>()->SetTexture("Menu/Button.png");
		menu->startPlay = true;
	}

	Vector2 temp = menu->battleBtnPos;
	temp.x = menu->GetObjRef(0)->transform->worldposition.x <= -670 ? -670 : menu->GetObjRef(0)->transform->worldposition.x - DeltaTime * 150;
	menu->GetObjRef(0)->transform->SetPosition(temp);
}

void BtnFuncUnHover_Options(Button* button)
{
	if (!menu->optionPlay)
	{
		if (menu->displayTxt != NULL)
			menu->displayTxt->SetText("");
		button->Owner()->GetComponent<SpriteRenderer>()->SetTexture("Menu/Button.png");
		menu->optionPlay = true;
	}

	Vector2 temp = menu->optionBtnPos;
	temp.x = menu->GetObjRef(1)->transform->worldposition.x <= -670 ? -670 : menu->GetObjRef(1)->transform->worldposition.x - DeltaTime * 150;
	menu->GetObjRef(1)->transform->SetPosition(temp);
}

void BtnFuncUnHover_Quit(Button* button)
{
	if (!menu->quitPlay)
	{
		if (menu->displayTxt != NULL)
			menu->displayTxt->SetText("");
		button->Owner()->GetComponent<SpriteRenderer>()->SetTexture("Menu/Button.png");
		menu->quitPlay = true;
	}

	Vector2 temp = menu->quitBtnPos;
	temp.x = menu->GetObjRef(2)->transform->worldposition.x <= -670 ? -670 : menu->GetObjRef(2)->transform->worldposition.x - DeltaTime * 150;
	menu->GetObjRef(2)->transform->SetPosition(temp);
}
