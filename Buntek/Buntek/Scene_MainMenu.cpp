#include "Scene_MainMenu.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "Button.h"
#include "Scene_Battle.h"
#include "DialogueBox.h"

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
	tempRenderer->SetTexture("Buttons.png");
	TextRenderer* tempTextRenderer;
	tempTextRenderer = Battle->AddComponent<TextRenderer>();
	//tempRenderer->SetTexture("WhiteTexture.png");
	tempTextRenderer->SetFont("EquinoxR.otf");
	tempTextRenderer->SetTextColor(1, 1, 1);
	tempTextRenderer->SetText("B a t t l e");

	Battle->transform->SetPosition(Vector2(0, -200));
	Button* button;
	button = Battle->AddComponent<Button>();
	button->sr = tempRenderer;
	button->tr = tempTextRenderer;
	button->ButtonEffect = &MoveToBattle;

	// Get main dialogue box
	dialogue = new GameObject();
	dialogue->transform->SetPosition(Vector2(0, -280));
	tempRenderer = dialogue->AddComponent<SpriteRenderer>();
	tempRenderer->Size(1800, 360);
	tempRenderer->SetTexture("EncounterBox.png");
	tempTextRenderer = dialogue->AddComponent<TextRenderer>();
	tempTextRenderer->SetFont("EquinoxR.otf");
	tempTextRenderer->SetTextColor(1, 1, 1);

	//// Get actor name dialogue box
	//GameObject* tempGameObject = new GameObject();
	//tempRenderer = tempGameObject->AddComponent<SpriteRenderer>();
	//tempRenderer->Size(300, 80);
	//tempRenderer->SetTexture("EncounterBox.png");
	//tempTextRenderer = tempGameObject->AddComponent<TextRenderer>();
	//tempTextRenderer->SetFont("EquinoxR.otf");
	//tempTextRenderer->SetTextColor(1, 1, 1);
	//DialogueBox* tempdialogue;
	//tempdialogue = tempGameObject->AddComponent<DialogueBox>();
	//tempdialogue->sr = tempRenderer;
	//tempdialogue->tr = tempTextRenderer;

	//// Assign actor name dialogue box to main dialogue box
	//tempdialogue = dialogue->AddComponent<DialogueBox>();
	//tempdialogue->isMainDialogue = true;
	//tempdialogue->sr = dialogue->GetComponent<SpriteRenderer>();
	//tempdialogue->tr = dialogue->GetComponent<TextRenderer>();
	//tempdialogue->tr->SetScale(1.5f);
	//tempdialogue->actorBox = tempGameObject->GetComponent<DialogueBox>();
	//tempdialogue->LoadFromFile("asd");
}

void Scene_MainMenu::Update(void)
{
	//// [TO REMOVE] This code is just to test DialogueBox functionality
	//if (AEInputCheckTriggered(AEVK_RBUTTON)) {
	//	dialogue->GetComponent<DialogueBox>()->ToggleDisplay(TestDialogueDisplay);
	//	TestDialogueDisplay = !TestDialogueDisplay;
	//}

	//Battle->GetComponent<Button>()->ButtonEffect();
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
}

void MoveToBattle(void)
{
	SceneManager.LoadScene(new Scene_Battle, TransitionTypes::FadeToBlack);
}