#include "Scene_MainMenu.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "Button.h"
#include "Scene_Battle.h"
#include "DialogueBox.h"
#include "EncounterBox.h"
#include "UI_RewardSelection.h"
#include "EnemyNodeBox.h"

void MoveToBattle(Button* button);
void EnemyNodeHovers(Button* button);
void EnemyNodeNotHovers(Button* button);

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
	button->ButtonEffect = &MoveToBattle;
	button->affectedHoverObject = enemynode;
	button->HoverEffect = &EnemyNodeHovers;
	button->NotHoverEffect = &EnemyNodeNotHovers;
	//dialogue = new GameObject();
	//dialogue->AddComponent<DialogueBox>();
	//dialogue->GetComponent<DialogueBox>()->CreateDialogue("asd");
	
	encounter = new GameObject();
	encounter->AddComponent<EncounterBox>();
	encounter->GetComponent<EncounterBox>()->CreateEncounter(Vector2(0, 0), 3, "aed");

	rewardsel = new GameObject();
	rewardsel->AddComponent<UI_RewardSelection>();
	vector<string> rewards{ "E" };
	rewardsel->GetComponent<UI_RewardSelection>()->CreateRewardSelection(Vector2(0, 0), 4, rewards);

	enemynode = new GameObject();
	enemynode->AddComponent<EnemyNodeBox>();
	enemynode->GetComponent<EnemyNodeBox>()->CreateEnemyNode(Battle, 3, 10);
	enemynode->Deactivate();
	button->affectedHoverObject = enemynode;
}

void Scene_MainMenu::Update(void)
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
}

void MoveToBattle(Button* button)
{
	SceneManager.LoadScene(new Scene_Battle, TransitionTypes::FadeToBlack);
}

void EnemyNodeHovers(Button* button) 
{
	button->affectedHoverObject->Activate();
	float xpos = button->sr->GetHalfWidth() + button->affectedHoverObject->GetComponent<SpriteRenderer>()->GetHalfWidth();
	button->affectedHoverObject->transform->SetPosition(Vector2(xpos, button->Owner()->transform->worldposition.y));
}
void EnemyNodeNotHovers(Button* button)
{
	button->affectedHoverObject->Deactivate();
}