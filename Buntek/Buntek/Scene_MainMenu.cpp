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

	
	// Create main dialogue box
	dialogue = new GameObject();
	dialogue->transform->SetPosition(Vector2(0, -280));
	tempRenderer = dialogue->AddComponent<SpriteRenderer>();
	tempRenderer->Size(1800, 360);
	tempRenderer->SetTexture("EncounterBox.png");
	tempTextRenderer = dialogue->AddComponent<TextRenderer>();
	tempTextRenderer->SetFont("EquinoxR.otf");
	tempTextRenderer->SetTextColor(1, 1, 1);
	
	// Create actor box
	SpriteRenderer* tempRenderer2 = 0;
	TextRenderer* tempTxtRenderer2 = 0;
	GameObject* tempGameObject = new GameObject();
	tempRenderer2 = tempGameObject->AddComponent<SpriteRenderer>();
	tempRenderer2->Size(400, 80);
	tempRenderer2->SetTexture("EncounterBox.png");
	tempTxtRenderer2 = tempGameObject->AddComponent<TextRenderer>();
	tempTxtRenderer2->SetFont("EquinoxR.otf");
	tempTxtRenderer2->SetTextColor(1, 1, 1);
	
	// Create dialoguebox and assign
	DialogueBox* tempdialogue = tempGameObject->AddComponent<DialogueBox>();
	tempdialogue->AssignObjReferences(tempRenderer2, tempRenderer, tempTxtRenderer2, tempTextRenderer);
	tempdialogue->StartDialogueEvent("asd");
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