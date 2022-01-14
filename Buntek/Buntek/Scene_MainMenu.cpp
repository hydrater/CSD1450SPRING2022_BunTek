#include "Scene_MainMenu.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "Button.h"
#include "Scene_Battle.h"
#include "DialogueBox.h"
#include "EncounterBox.h"
#include "EnemyNodeBox.h"

void MoveToBattle(Button* button);

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
	tempTextRenderer->SetFont("EquinoxR.otf");
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

	//dialogue = new GameObject();
	//dialogue->AddComponent<DialogueBox>();
	//dialogue->GetComponent<DialogueBox>()->CreateDialogue("asd");
	//
	encounter = new GameObject();
	encounter->AddComponent<EncounterBox>();
	encounter->GetComponent<EncounterBox>()->CreateEncounter(Vector2(0, 0), 3, "aed");
	 
	/*enemynode = new GameObject();
	enemynode->AddComponent<EnemyNodeBox>();
	enemynode->GetComponent<EnemyNodeBox>()->CreateEnemyNode(Battle, 3, 10);*/
		
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
	//EnemyNodeBox* enemyNodeBox = button->Owner()->GetComponent<EnemyNodeBox>();
	//if (button->test != NULL)
	//	return;
	//GameObject* enemyNodeBox = button->test;
	//enemyNodeBox->GetComponent<EnemyNodeBox>()->StartEnemyNode();
	//enemyNodeBox->GetComponent<EnemyNodeBox>()->CloseEnemyNode();
}