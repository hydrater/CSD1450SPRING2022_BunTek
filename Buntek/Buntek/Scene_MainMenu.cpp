#include "Scene_MainMenu.h"
#include "SpriteRenderer.h"
#include "Button.h"
#include "Scene_Battle.h"


void MoveToBattle(void);

void Scene_MainMenu::Start(void)
{
	

	background = new GameObject();
	background->AddComponent<SpriteRenderer>()->Size(1920, 1080);
	background->GetComponent<SpriteRenderer>()->SetTexture("MainMenu.png");

	Battle = new GameObject();
	SpriteRenderer* tempRenderer;
	tempRenderer = Battle->AddComponent<SpriteRenderer>();
	tempRenderer->Size(200, 100);
	tempRenderer->SetTexture("WhiteTexture.png");
	tempRenderer->SetFont("Roboto-Regular.ttf");
	tempRenderer->SetTextColor(1, 0, 0);
	tempRenderer->SetText("Battle");
	Battle->transform->SetPosition(Vector2(0, -200));
	Button* button;
	button = Battle->AddComponent<Button>();
	button->sr = tempRenderer;
	button->ButtonEffect = &MoveToBattle;
	
}

void Scene_MainMenu::Update(void)
{
	
	//string s = "test";

	//Battle->GetComponent<Button>()->ButtonEffect();
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
}

void MoveToBattle(void)
{
	SceneManager.LoadScene(new Scene_Battle);
}