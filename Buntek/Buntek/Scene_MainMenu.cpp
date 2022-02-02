#include "Scene_MainMenu.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "Button.h"
#include "Scene_Navigation.h"
#include "UI_Shop.h"
#include "AssetManager.h"
#include "GameManager.h"

void BtnFunc_Start(Button* button);
void BtnFunc_Options(Button* button);
void BtnFunc_Quit(Button* button);

void Scene_MainMenu::Start(void)
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	AssetManager.LoadTexture("Menu/MainMenuArt.png");
	AssetManager.LoadTexture("Menu/PolkaSquare.png");
	AssetManager.LoadTexture("Menu/Button.png");

	background = new GameObject();
	background->AddComponent<SpriteRenderer>()->Size(1920, 1080);
	background->GetComponent<SpriteRenderer>()->SetTexture("Menu/MainMenuArt.png");
	background->GetComponent<SpriteRenderer>()->SetLayer(0);

	MainMenu = new GameObject();
	MainMenu->transform->SetPosition(Vector2(-100, 0));
	polkaDotter = MainMenu->AddComponent<SpriteRenderer>();
	polkaDotter->Size(1900, 1100);
	polkaDotter->SetTexture("Menu/PolkaSquare.png");
	polkaDotter->SetLayer(-1);

	battleBtn = new GameObject();
	SpriteRenderer* tempRenderer;
	tempRenderer = battleBtn->AddComponent<SpriteRenderer>();
	tempRenderer->Size(471, 71);
	tempRenderer->SetTexture("Menu/Button.png");
	TextRenderer* tempTextRenderer;
	tempTextRenderer = battleBtn->AddComponent<TextRenderer>();
	tempTextRenderer->SetFont("GothicA1.ttf");
	tempTextRenderer->SetLayer(1);
	tempTextRenderer->SetTextColor(0, 0, 0);
	tempTextRenderer->SetText("Start");
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
	battleBtn->transform->SetPosition(Vector2(-670, -200));
	Button* button;
	button = battleBtn->AddComponent<Button>();
	button->sr = tempRenderer;
	button->tr = tempTextRenderer;
	button->ButtonEffect = &BtnFunc_Start;

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

	// Load save data
	//SaveManager.LoadData();
}

void Scene_MainMenu::Update(void)
{
	Vector2 temp = polkaDotter->GetTextureOffset();
	temp.x -= DeltaTime * 0.1f;
	temp.y += DeltaTime * 0.1f;
	polkaDotter->SetTextureOffset(Vector2(temp.x, temp.y));
}

Scene_MainMenu::~Scene_MainMenu(void)
{
	AssetManager.UnloadTexture("Menu/MainMenu.png");
	AssetManager.UnloadTexture("Menu/PolkaSquare.png");
	AssetManager.UnloadTexture("Menu/Button.png");
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

