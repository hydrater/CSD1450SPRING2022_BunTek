#include "Scene_MainMenu.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "Button.h"
#include "Scene_Navigation.h"
#include "UI_DialogueBox.h"
#include "UI_EncounterBox.h"
#include "UI_RewardSelection.h"
#include "UI_Shop.h"
#include "UI_EnemyNodeBox.h"

void MoveToNavigation(Button* button);

void Scene_MainMenu::Start(void)
{
	background = new GameObject();
	background->AddComponent<SpriteRenderer>()->Size(1920, 1080);
	background->GetComponent<SpriteRenderer>()->SetTexture("MainMenu.png");
	background->GetComponent<SpriteRenderer>()->SetLayer(-1);

	Battle = new GameObject();
	SpriteRenderer* tempRenderer;
	tempRenderer = Battle->AddComponent<SpriteRenderer>();
	tempRenderer->Size(200, 100);
	tempRenderer->SetTexture("Buttons.png");
	TextRenderer* tempTextRenderer;
	tempTextRenderer = Battle->AddComponent<TextRenderer>();
	//tempRenderer->SetTexture("WhiteTexture.png");
	tempTextRenderer->SetFont("Astral.ttf");
	tempTextRenderer->SetTextColor(1, 1, 1);
	tempTextRenderer->SetText("B a t t l e");
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
	Battle->transform->SetPosition(Vector2(0, -200));
	Button* button;
	button = Battle->AddComponent<Button>();
	button->sr = tempRenderer;
	button->tr = tempTextRenderer;
	button->ButtonEffect = &MoveToNavigation;

	/*rewardsel = new GameObject();
	rewardsel->AddComponent<UI_RewardSelection>();
	vector<string> rewards{ "E" };
	rewardsel->GetComponent<UI_RewardSelection>()->CreateRewardSelection(Vector2(0, 0), 4, rewards);*/
}

void Scene_MainMenu::Update(void)
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
}

void MoveToNavigation(Button* button)
{
	SceneManager.LoadScene(new Scene_Navigation, TransitionType::FadeToBlack);
}

