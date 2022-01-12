#include "Scene_MainMenu.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "Button.h"
#include "Scene_Battle.h"
#include "DialogueBox.h"
#include "EncounterBox.h"

void MoveToBattle(void);

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

	// Create main dialogue box
	dialogue = new GameObject();
	dialogue->transform->SetPosition(Vector2(0, -280));
	tempRenderer = dialogue->AddComponent<SpriteRenderer>();
	tempRenderer->Size(1800, 360);
	tempRenderer->SetTexture("EncounterBox.png");
	tempRenderer->SetLayer(1);
	tempTextRenderer = dialogue->AddComponent<TextRenderer>();
	tempTextRenderer->SetFont("EquinoxR.otf");
	tempTextRenderer->SetTextColor(1, 1, 1);
	tempTextRenderer->SetLayer(1);
	
	// Create actor box
	SpriteRenderer* tempRenderer2 = 0;
	TextRenderer* tempTxtRenderer2 = 0;
	GameObject* tempGameObject = new GameObject();
	tempRenderer2 = tempGameObject->AddComponent<SpriteRenderer>();
	tempRenderer2->Size(400, 80);
	tempRenderer2->SetTexture("EncounterBox.png");
	tempRenderer2->SetLayer(1);
	tempTxtRenderer2 = tempGameObject->AddComponent<TextRenderer>();
	tempTxtRenderer2->SetFont("EquinoxR.otf");
	tempTxtRenderer2->SetTextColor(1, 1, 1);
	tempTxtRenderer2->SetLayer(1);
	
	// Create dialoguebox and assign
	DialogueBox* tempdialogue = tempGameObject->AddComponent<DialogueBox>();
	tempdialogue->AssignObjReferences(tempRenderer2, tempRenderer, tempTxtRenderer2, tempTextRenderer);
	tempdialogue->StartDialogueEvent("asd");

	CreateEncounter(Vector2(0, 0), 3, "aed");
}

void Scene_MainMenu::CreateEncounter(Vector2 position, int sortingLayer, string flag)
{
	encounter = new GameObject();
	encounter->transform->SetPosition(position);
	EncounterBox* tempEncounter = encounter->AddComponent<EncounterBox>();

	// Background
	GameObject* tempBackground = new GameObject();
	SpriteRenderer* tempBckgdRenderer = 0;
	tempBckgdRenderer = tempBackground->AddComponent<SpriteRenderer>();
	tempBckgdRenderer->Size(1500, 600);
	tempBckgdRenderer->SetTexture("EncounterBox.png");
	tempBckgdRenderer->SetLayer(sortingLayer - 2);
	encounter->AddChild(tempBackground);

	// Description
	GameObject* tempDescription = new GameObject();
	SpriteRenderer* tempDescRenderer = 0;
	tempDescRenderer = tempDescription->AddComponent<SpriteRenderer>();
	tempDescRenderer->Size(1000, tempBckgdRenderer->GetHalfHeight()/1.5);
	tempDescRenderer->SetTexture("EncounterBox.png");
	tempDescRenderer->SetLayer(sortingLayer - 2);

	// Header
	GameObject* tempHeader = new GameObject();
	SpriteRenderer* tempHeaderRenderer = 0;
	tempHeaderRenderer = tempHeader->AddComponent<SpriteRenderer>();
	tempHeaderRenderer->Size(800, 100);
	tempHeaderRenderer->SetTexture("paddle.png");
	tempHeaderRenderer->SetLayer(sortingLayer - 1);

	// HeaderText
	TextRenderer* tempHeaderTxtRenderer = 0;
	tempHeaderTxtRenderer = tempHeader->AddComponent<TextRenderer>();
	tempHeaderTxtRenderer->SetFont("EquinoxR.otf");
	tempHeaderTxtRenderer->SetTextColor(1, 0, 1);
	tempHeaderTxtRenderer->SetText("MING");
	tempHeaderTxtRenderer->SetLayer(sortingLayer);
	tempHeaderTxtRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Left);
	tempHeaderTxtRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
	tempHeaderTxtRenderer->SetXBuffer(50);
	tempHeader->transform->SetPosition(Vector2(position.x - tempBckgdRenderer->GetHalfWidth() + tempHeaderRenderer->GetHalfWidth(), position.y + tempBckgdRenderer->GetHalfHeight()));
	encounter->AddChild(tempHeader);

	// Description
	TextRenderer* tempDescTxtRenderer = 0;
	tempDescTxtRenderer = tempDescription->AddComponent<TextRenderer>();
	tempDescTxtRenderer->SetFont("EquinoxR.otf");
	tempDescTxtRenderer->SetTextColor(0, 1, 1);
	tempDescTxtRenderer->SetText("A CHICKEN FISH");
	tempDescTxtRenderer->SetLayer(sortingLayer);
	tempDescTxtRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Left);
	tempDescTxtRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Top);
	tempDescription->transform->SetPosition(Vector2(position.x + tempBckgdRenderer->GetHalfWidth() - tempDescRenderer->GetHalfWidth() - 20,
		position.y + tempBckgdRenderer->GetHalfHeight() - tempDescRenderer->GetHalfHeight() - 100));
	encounter->AddChild(tempDescription);

	// Display
	GameObject* tempDisplay = new GameObject();
	SpriteRenderer* tempDisplayRenderer = 0;
	tempDisplayRenderer = tempDisplay->AddComponent<SpriteRenderer>();
	tempDisplayRenderer->Size(450, 450);
	tempDisplayRenderer->SetTexture("Steven.jpg");
	tempDisplayRenderer->SetLayer(sortingLayer - 2);
	tempDisplay->transform->SetPosition(Vector2(position.x - tempBckgdRenderer->GetHalfWidth() + tempDisplayRenderer->GetHalfWidth() + 20, position.y - 20));
	encounter->AddChild(tempDisplay);

	// Buttons (Max 3)
	vector<Button*> buttonList;
	for (int i = 0; i < 3; ++i) {
		GameObject* tempButtonObj = new GameObject();
		SpriteRenderer* tempButtonRenderer = 0;
		tempButtonRenderer = tempButtonObj->AddComponent<SpriteRenderer>();
		tempButtonRenderer->Size(1000, 50);
		tempButtonRenderer->SetTexture("Buttons.png");
		tempButtonRenderer->SetLayer(sortingLayer - 1);

		TextRenderer* tempButtonTxtRenderer = 0;
		tempButtonTxtRenderer = tempButtonObj->AddComponent<TextRenderer>();
		tempButtonTxtRenderer->SetFont("EquinoxR.otf");
		tempButtonTxtRenderer->SetTextColor(1, 1, 0);
		tempButtonTxtRenderer->SetText("SCREM");
		tempButtonTxtRenderer->SetLayer(sortingLayer);
		tempButtonTxtRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
		tempButtonTxtRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);

		tempButtonObj->transform->SetPosition(Vector2(position.x + tempBckgdRenderer->GetHalfWidth() - tempButtonRenderer->GetHalfWidth() - 20,
			position.y - tempBckgdRenderer->GetHalfHeight() + (i+1) * tempBckgdRenderer->GetHalfHeight()/4 - 10));
		Button* tempButton = tempButtonObj->AddComponent<Button>();
		tempButton->sr = tempButtonRenderer;
		tempButton->tr = tempButtonTxtRenderer;
		
		encounter->AddChild(tempButtonObj);
		buttonList.push_back(tempButton);
	}
	

	tempEncounter->AssignObjReferences(tempHeaderRenderer, tempDisplayRenderer, tempBckgdRenderer, tempHeaderTxtRenderer, tempDescTxtRenderer, buttonList);
}

void Scene_MainMenu::Update(void)
{
	//Battle->GetComponent<Button>()->ButtonEffect();
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
}

void MoveToBattle(void)
{
	SceneManager.LoadScene(new Scene_Battle, TransitionTypes::FadeToBlack);
}