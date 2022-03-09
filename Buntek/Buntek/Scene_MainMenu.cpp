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
#include "Scene_Options.h"
#include "Scene_HowToPlay.h"
#include "Scene_Credits.h"

void BtnFunc_Start(Button* button);
void BtnFunc_HowToPlay(Button* button);
void BtnFunc_Options(Button* button);
void BtnFunc_Credits(Button* button);
void BtnFunc_Quit(Button* button);

void BtnFuncHover_Start(Button* button);
void BtnFuncHover_HowToPlay(Button* button);
void BtnFuncHover_Options(Button* button);
void BtnFuncHover_Credits(Button* button);
void BtnFuncHover_Quit(Button* button);

void BtnFuncUnhover_Start(Button* button);
void BtnFuncUnhover_HowToPlay(Button* button);
void BtnFuncUnHover_Options(Button* button);
void BtnFuncUnhover_Credits(Button* button);
void BtnFuncUnHover_Quit(Button* button);

Scene_MainMenu* Scene_MainMenu::instance = 0;

void Scene_MainMenu::Start(void)
{
	Scene_MainMenu::instance = this;
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	GameManager.disableInteraction = true;

	AudioManager.LoadSound("ButtonHover.mp3");
	AudioManager.LoadMusic("kidding.ogg");
	AudioManager.PlayMusic("kidding.ogg");

	AssetManager.LoadTexture("Menu/PolkaSquare.png");
	AssetManager.LoadTexture("Menu/Button.png");
	AssetManager.LoadTexture("Menu/ButtonPressed.png");
	AssetManager.LoadTexture("Menu/Disc.png");
	AssetManager.LoadTexture("Menu/Fake.png");
	AssetManager.LoadTexture("Menu/Bottom.png");
	AssetManager.LoadTexture("Menu/Border.png");
	AssetManager.LoadTexture("Menu/Title.png");
	AssetManager.LoadTexture("Concepts/Full-Yggdrasil.png");
	AssetManager.LoadTexture("Concepts/Mask-Yggdrasil.png");
	AssetManager.LoadTexture("Concepts/Mask-Volcano.png");
	AssetManager.LoadTexture("Concepts/Mask-Rainforest.png");
	AssetManager.LoadTexture("Concepts/Mask-CrystalCaves.png");

	background = new GameObject();
	background->transform->SetPosition(Vector2(20, 0));
	mainArtRenderer = background->AddComponent<SpriteRenderer>();
	mainArtRenderer->Size(1958, 1101);
	mainArtRenderer->SetTexture("Concepts/Full-Yggdrasil.png");
	mainArtRenderer->SetLayer(-1);
	background->AddComponent<Parallaxer>()->distance = 150.0f;

	mainMenu = new GameObject();
	mainMenu->transform->SetPosition(Vector2(-100, 0));
	polkaDotter = mainMenu->AddComponent<SpriteRenderer>();
	polkaDotter->Size(1900, 1100);
	polkaDotter->SetTexture("Menu/PolkaSquare.png");
	polkaDotter->SetLayer(-2);
	polkaDotter->SetOpacity(0);

	startBtn = new GameObject();
	SpriteRenderer* tempRenderer;
	tempRenderer = startBtn->AddComponent<SpriteRenderer>();
	tempRenderer->SetLayer(2);
	tempRenderer->Size(471, 71);
	tempRenderer->SetTexture("Menu/Button.png");
	TextRenderer* tempTextRenderer;
	tempTextRenderer = startBtn->AddComponent<TextRenderer>();
	tempTextRenderer->SetFont("Ayar.ttf");
	tempTextRenderer->SetLayer(3);
	tempTextRenderer->SetTextColor(0, 0, 0);
	tempTextRenderer->SetText("Start");
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
	startBtn->transform->SetPosition(Vector2(-670, 1000));
	Button* button;
	button = startBtn->AddComponent<Button>();
	button->sr = tempRenderer;
	button->tr = tempTextRenderer;
	button->ButtonEffect = &BtnFunc_Start;
	button->HoverEffect = &BtnFuncHover_Start;
	button->NotHoverEffect = &BtnFuncUnhover_Start;

	howtoplayBtn = new GameObject();
	tempRenderer = howtoplayBtn->AddComponent<SpriteRenderer>();
	tempRenderer->SetLayer(2);
	tempRenderer->Size(471, 71);
	tempRenderer->SetTexture("Menu/Button.png");
	tempTextRenderer = howtoplayBtn->AddComponent<TextRenderer>();
	tempTextRenderer->SetFont("Ayar.ttf");
	tempTextRenderer->SetLayer(3);
	tempTextRenderer->SetTextColor(0, 0, 0);
	tempTextRenderer->SetText("How To Play");
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
	howtoplayBtn->transform->SetPosition(Vector2(-670, 1000));
	button = howtoplayBtn->AddComponent<Button>();
	button->sr = tempRenderer;
	button->tr = tempTextRenderer;
	button->ButtonEffect = &BtnFunc_HowToPlay;
	button->HoverEffect = &BtnFuncHover_HowToPlay;
	button->NotHoverEffect = &BtnFuncUnhover_HowToPlay;

	optionBtn = new GameObject();
	tempRenderer = optionBtn->AddComponent<SpriteRenderer>();
	tempRenderer->SetLayer(2);
	tempRenderer->Size(471, 71);
	tempRenderer->SetTexture("Menu/Button.png");
	tempTextRenderer = optionBtn->AddComponent<TextRenderer>();
	tempTextRenderer->SetFont("Ayar.ttf");
	tempTextRenderer->SetLayer(3);
	tempTextRenderer->SetTextColor(0, 0, 0);
	tempTextRenderer->SetText("Alpha Survey");
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
	optionBtn->transform->SetPosition(Vector2(-670, 1000));
	button = optionBtn->AddComponent<Button>();
	button->sr = tempRenderer;
	button->tr = tempTextRenderer;
	button->ButtonEffect = &BtnFunc_Options;
	button->HoverEffect = &BtnFuncHover_Options;
	button->NotHoverEffect = &BtnFuncUnHover_Options;

	creditsBtn = new GameObject();
	tempRenderer = creditsBtn->AddComponent<SpriteRenderer>();
	tempRenderer->SetLayer(2);
	tempRenderer->Size(471, 71);
	tempRenderer->SetTexture("Menu/Button.png");
	tempTextRenderer = creditsBtn->AddComponent<TextRenderer>();
	tempTextRenderer->SetFont("Ayar.ttf");
	tempTextRenderer->SetLayer(3);
	tempTextRenderer->SetTextColor(0, 0, 0);
	tempTextRenderer->SetText("Credits");
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
	creditsBtn->transform->SetPosition(Vector2(-670, 1000));
	button = creditsBtn->AddComponent<Button>();
	button->sr = tempRenderer;
	button->tr = tempTextRenderer;
	button->ButtonEffect = &BtnFunc_Credits;
	button->HoverEffect = &BtnFuncHover_Credits;
	button->NotHoverEffect = &BtnFuncUnhover_Credits;

	quitBtn = new GameObject();
	tempRenderer = quitBtn->AddComponent<SpriteRenderer>();
	tempRenderer->Size(471, 71);
	tempRenderer->SetTexture("Menu/Button.png");
	tempRenderer->SetLayer(2);
	tempTextRenderer = quitBtn->AddComponent<TextRenderer>();
	tempTextRenderer->SetFont("Ayar.ttf");
	tempTextRenderer->SetLayer(3);
	tempTextRenderer->SetTextColor(0, 0, 0);
	tempTextRenderer->SetText("Quit");
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
	quitBtn->transform->SetPosition(Vector2(-670, 1000));
	button = quitBtn->AddComponent<Button>();
	button->sr = tempRenderer;
	button->tr = tempTextRenderer;
	button->ButtonEffect = &BtnFunc_Quit;
	button->HoverEffect = &BtnFuncHover_Quit;
	button->NotHoverEffect = &BtnFuncUnHover_Quit;

	title = devTools.CreateSpriteGameObject("Menu/Title.png", 1008, 116, AE_GFX_BM_BLEND, Vector2(-400, 400), 6)->GetComponent<SpriteRenderer>();

	mask = devTools.CreateSpriteGameObject("Concepts/Full-Yggdrasil.png", 1958, 1101, AE_GFX_BM_BLEND, Vector2(20, 0), 0)->GetComponent<SpriteRenderer>();
	mask->Owner()->AddComponent<Parallaxer>()->distance = 150.0f;
	mask->SetOpacity(0);

	fake = devTools.CreateSpriteGameObject("Menu/Fake.png", 2800, 1900, AE_GFX_BM_BLEND, Vector2(0, 0), 0)->transform;
	fake->SetRotation(-180);
	fake->SetScale(Vector2(2, 2));

	border = devTools.CreateSpriteGameObject("Menu/Border.png", 1920, 1080, AE_GFX_BM_BLEND, Vector2(0, 1080), 1)->transform;
	border->SetRotation(360);

	bottom = devTools.CreateSpriteGameObject("Menu/Bottom.png", 1920, 83, AE_GFX_BM_BLEND, Vector2(0, -490), 2)->transform;
	bottom->SetScale(Vector2(0.0f, 2.0f));

	disc = devTools.CreateSpriteGameObject("Menu/Disc.png", 400, 400, AE_GFX_BM_BLEND, Vector2(900, -420), 3)->transform;
	disc->SetScale(Vector2(0, 0));

	// Load save data
	//SaveManager.LoadData();
}

void Scene_MainMenu::Update(void)
{
	animTimer += DeltaTime;
	artSwitchTimer += DeltaTime;

	if (artSwitchTimer > 3)
	{
		mask->SetOpacity(mask->GetOpacity() + DeltaTime);
		mask->SetTextureOffset(Vector2(mask->GetTextureOffset().x + DeltaTime * 0.01f, 0.0f));
		switch (cycle)
		{
		case 0:
			mask->SetTexture("Concepts/Mask-CrystalCaves.png");
			break;

		case 1:
			mask->SetTexture("Concepts/Mask-Volcano.png");
			break;

		case 2:
			mask->SetTexture("Concepts/Mask-Rainforest.png");
			break;

		case 3:
			mask->SetTexture("Concepts/Mask-Yggdrasil.png");
			break;

		default:
			break;
		}

		if (artSwitchTimer > 4)
		{
			artSwitchTimer = 1.0f;
			mainArtRenderer->SetTextureOffset(mask->GetTextureOffset());
			mask->SetOpacity(0);
			mask->SetTextureOffset(Vector2(0, 0));
			mainArtRenderer->SetTexture(mask->GetTextureName());
			++cycle;
			if (cycle > 3)
				cycle = 0;
		}
	}
	mainArtRenderer->SetTextureOffset(Vector2(mainArtRenderer->GetTextureOffset().x + DeltaTime * 0.005f, 0.0f));

	Vector2 temp = polkaDotter->GetTextureOffset();
	temp.x -= DeltaTime * 0.1f;
	temp.y += DeltaTime * 0.1f;
	polkaDotter->SetTextureOffset(Vector2(temp.x, temp.y));
	disc->Rotate(DeltaTime * 20);

	if (animTimer < 1.0f)
	{
		fake->Translate(Vector2(DeltaTime * -450.0f, -400.0f * DeltaTime));
		fake->Rotate(DeltaTime * 180.1f);
		fake->SetScale(Vector2(fake->worldscale.x -= DeltaTime, fake->worldscale.y -= DeltaTime));

		border->Translate(Vector2(0.0f, -1080 * DeltaTime));
		border->Rotate(DeltaTime * -360.1f);

		startBtn->transform->Translate(Vector2(0.0f, DeltaTime * -1000));
		howtoplayBtn->transform->Translate(Vector2(0.0f, DeltaTime * -1100));
		optionBtn->transform->Translate(Vector2(0.0f, DeltaTime * -1200));
		creditsBtn->transform->Translate(Vector2(0.0f, DeltaTime * -1300));
		quitBtn->transform->Translate(Vector2(0.0f, DeltaTime * -1400));

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
		polkaDotter->SetOpacity(1);
		fake->Owner()->GetComponent<SpriteRenderer>()->SetOpacity(0);
		//border->Owner()->GetComponent<SpriteRenderer>()->SetTransparency(0);
		border->SetScale(Vector2(1, 1));
		border->SetPosition(Vector2(0, 0));
		border->SetRotation(0);
		border->Owner()->AddComponent<Parallaxer>()->distance = 150.0f;

		background->GetComponent<SpriteRenderer>()->SetTexture("Concepts/Mask-Yggdrasil.png");

		AssetManager.UnloadTexture("Concepts/Full-Yggdrasil.png");
		AssetManager.UnloadTexture("Menu/Fake.png");
		disc->SetScale(Vector2(1, 1));
		bottom->SetScale(Vector2(1, 1));

		startBtn->transform->SetPosition(Vector2(-670, 0));
		howtoplayBtn->transform->SetPosition(Vector2(-670, -100));
		optionBtn->transform->SetPosition(Vector2(-670, -200));
		creditsBtn->transform->SetPosition(Vector2(-670, -300));
		quitBtn->transform->SetPosition(Vector2(-670, -400));

		displayTxt = bottom->Owner()->AddComponent<TextRenderer>();
		displayTxt->SetFont("Ayar.ttf");
		displayTxt->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
		displayTxt->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
		displayTxt->SetLayer(5);
		displayTxt->SetFontSize(42);
		displayTxt->SetTextColor(0, 0, 0);

		GameManager.disableInteraction = false;
		finishedSetup = true;
	}
}

Scene_MainMenu::~Scene_MainMenu(void)
{
	AudioManager.UnloadSound("ButtonHover.mp3");
	AudioManager.UnloadMusic("kidding.ogg");
	AssetManager.UnloadTexture("Menu/PolkaSquare.png");
	AssetManager.UnloadTexture("Menu/Button.png");
	AssetManager.UnloadTexture("Menu/ButtonPressed.png");
	AssetManager.UnloadTexture("Menu/Disc.png");
	AssetManager.UnloadTexture("Menu/Bottom.png");
	AssetManager.UnloadTexture("Menu/Border.png");
	AssetManager.UnloadTexture("Menu/Title.png");
	AssetManager.UnloadTexture("Concepts/Mask-Yggdrasil.png");
	AssetManager.UnloadTexture("Concepts/Mask-Volcano.png");
	AssetManager.UnloadTexture("Concepts/Mask-Rainforest.png");
	AssetManager.UnloadTexture("Concepts/Mask-CrystalCaves.png");
	instance = NULL;
}

GameObject* Scene_MainMenu::GetObjRef(short type)
{
	if (type == 0)
		return startBtn;
	else
	{
		if (type == 1)
			return howtoplayBtn;
		if (type == 2)
			return optionBtn;
		if (type == 3)
			return creditsBtn;
		else
			return quitBtn;
	}
}

void BtnFunc_Start(Button* button)
{
	SceneManager.LoadScene(new Scene_Navigation, TransitionType::FadeTransition, true);
}

void BtnFunc_HowToPlay(Button* button)
{
	SceneManager.LoadScene(new Scene_HowToPlay, TransitionType::FadeTransition, true);
}

void BtnFunc_Options(Button* button)
{
	//SceneManager.LoadScene(new Scene_Options, TransitionType::FadeTransition, true);
	#include <windows.h>
	#include <shellapi.h>
	ShellExecute(0, 0, "https://docs.google.com/forms/d/e/1FAIpQLScuD-oyTXlUahcOZD3rJlF_7knbTXFmxq-3cLLfjQDjpKagKA/viewform?usp=sf_link", 0, 0, SW_SHOW);
}

void BtnFunc_Credits(Button* button)
{
	SceneManager.LoadScene(new Scene_Credits, TransitionType::FadeTransition, true);
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
		menu->startPlay = false;
	}

	Vector2 temp = menu->battleBtnPos;
	temp.x = menu->GetObjRef(0)->transform->worldposition.x >= -650 ? -650 : menu->GetObjRef(0)->transform->worldposition.x + DeltaTime * 150;
	menu->GetObjRef(0)->transform->SetPosition(temp);
}

void BtnFuncHover_HowToPlay(Button* button)
{
	if (menu->howtoPlay)
	{
		AudioManager.PlayClip("ButtonHover.mp3");
		button->Owner()->GetComponent<SpriteRenderer>()->SetTexture("Menu/ButtonPressed.png");
		menu->displayTxt->SetText("Tutorial");
		menu->howtoPlay = false;
	}

	Vector2 temp = menu->howtoplayBtnPos;
	temp.x = menu->GetObjRef(1)->transform->worldposition.x >= -650 ? -650 : menu->GetObjRef(1)->transform->worldposition.x + DeltaTime * 150;
	menu->GetObjRef(1)->transform->SetPosition(temp);
}

void BtnFuncHover_Options(Button* button)
{
	if (menu->optionPlay)
	{
		AudioManager.PlayClip("ButtonHover.mp3");
		button->Owner()->GetComponent<SpriteRenderer>()->SetTexture("Menu/ButtonPressed.png");
		menu->displayTxt->SetText("Opens the survey in your preferred browser");
		menu->optionPlay = false;
	}

	Vector2 temp = menu->optionBtnPos;
	temp.x = menu->GetObjRef(2)->transform->worldposition.x >= -650 ? -650 : menu->GetObjRef(2)->transform->worldposition.x + DeltaTime * 150;
	menu->GetObjRef(2)->transform->SetPosition(temp);
}

void BtnFuncHover_Credits(Button* button)
{
	if (menu->creditsPlay)
	{
		AudioManager.PlayClip("ButtonHover.mp3");
		button->Owner()->GetComponent<SpriteRenderer>()->SetTexture("Menu/ButtonPressed.png");
		menu->displayTxt->SetText("Credits");
		menu->creditsPlay = false;
	}

	Vector2 temp = menu->creditsBtnPos;
	temp.x = menu->GetObjRef(3)->transform->worldposition.x >= -650 ? -650 : menu->GetObjRef(3)->transform->worldposition.x + DeltaTime * 150;
	menu->GetObjRef(3)->transform->SetPosition(temp);
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
	temp.x = menu->GetObjRef(4)->transform->worldposition.x >= -650 ? -650 : menu->GetObjRef(4)->transform->worldposition.x + DeltaTime * 150;
	menu->GetObjRef(4)->transform->SetPosition(temp);
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

void BtnFuncUnhover_HowToPlay(Button* button)
{
	if (!menu->howtoPlay)
	{
		if (menu->displayTxt != NULL)
			menu->displayTxt->SetText("");
		button->Owner()->GetComponent<SpriteRenderer>()->SetTexture("Menu/Button.png");
		menu->howtoPlay = true;
	}

	Vector2 temp = menu->howtoplayBtnPos;
	temp.x = menu->GetObjRef(1)->transform->worldposition.x <= -670 ? -670 : menu->GetObjRef(1)->transform->worldposition.x - DeltaTime * 150;
	menu->GetObjRef(1)->transform->SetPosition(temp);
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
	temp.x = menu->GetObjRef(2)->transform->worldposition.x <= -670 ? -670 : menu->GetObjRef(2)->transform->worldposition.x - DeltaTime * 150;
	menu->GetObjRef(2)->transform->SetPosition(temp);
}

void BtnFuncUnhover_Credits(Button* button)
{
	if (!menu->creditsPlay)
	{
		if (menu->displayTxt != NULL)
			menu->displayTxt->SetText("");
		button->Owner()->GetComponent<SpriteRenderer>()->SetTexture("Menu/Button.png");
		menu->creditsPlay = true;
	}

	Vector2 temp = menu->creditsBtnPos;
	temp.x = menu->GetObjRef(3)->transform->worldposition.x <= -670 ? -670 : menu->GetObjRef(3)->transform->worldposition.x - DeltaTime * 150;
	menu->GetObjRef(3)->transform->SetPosition(temp);
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
	temp.x = menu->GetObjRef(4)->transform->worldposition.x <= -670 ? -670 : menu->GetObjRef(4)->transform->worldposition.x - DeltaTime * 150;
	menu->GetObjRef(4)->transform->SetPosition(temp);
}
