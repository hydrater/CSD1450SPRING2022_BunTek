#include "Scene_MainMenu.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "AssetManager.h"
#include "GameManager.h"
#include "Devtools.h"
#include "Scene_Credits.h"
#include "Scene_MainMenu.h"
#include "AudioEngine.h"
void BtnFunc_Back(Button* button);
void BtnFuncHover_Back(Button* button);
void BtnFuncUnhover_Back(Button* button);

void Scene_Credits::Start(void)
{
	AudioManager.LoadSound("ButtonHover.mp3");
	AudioManager.SetMusicVolume(0.05f);

	AssetManager.LoadTexture("Menu/Button.png");
	AssetManager.LoadTexture("Menu/ButtonPressed.png");

	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	backBtn = new GameObject();
	SpriteRenderer* tempRenderer;
	tempRenderer = backBtn->AddComponent<SpriteRenderer>();
	tempRenderer->SetLayer(2);
	tempRenderer->Size(471, 71);
	tempRenderer->SetTexture("Menu/Button.png");
	TextRenderer* tempTextRenderer;
	tempTextRenderer = backBtn->AddComponent<TextRenderer>();
	tempTextRenderer->SetFont("Ayar.ttf");
	tempTextRenderer->SetLayer(3);
	tempTextRenderer->SetTextColor(0, 0, 0);
	tempTextRenderer->SetText("Main Menu");
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
	backBtn->transform->SetPosition(Vector2(-670, 1000));
	Button* button;
	button = backBtn->AddComponent<Button>();
	button->sr = tempRenderer;
	button->tr = tempTextRenderer;
	button->ButtonEffect = &BtnFunc_Back;
	button->HoverEffect = &BtnFuncHover_Back;
	button->NotHoverEffect = &BtnFuncUnhover_Back;

	header = new GameObject();
	tempRenderer = header->AddComponent<SpriteRenderer>();
	tempRenderer->SetLayer(2);
	tempRenderer->Size(500, 100);
	tempRenderer->SetTexture("Menu/Ball.png");
	header->transform->SetPosition(Vector2(0, 400));
	tempTextRenderer = header->AddComponent<TextRenderer>();
	tempTextRenderer->SetFont("Ayar.ttf");
	tempTextRenderer->SetLayer(3);
	tempTextRenderer->SetWarpAround(true);
	tempTextRenderer->SetText("Credits");
	tempTextRenderer->SetTextColor(191, 255, 191);
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);

	buntekheader = new GameObject();
	tempRenderer = buntekheader->AddComponent<SpriteRenderer>();
	tempRenderer->SetLayer(2);
	tempRenderer->Size(500, 100); 
	tempRenderer->SetTexture("Menu/Ball.png");
	tempTextRenderer = buntekheader->AddComponent<TextRenderer>();
	buntekheader->transform->SetPosition(Vector2(0, 300));
	tempTextRenderer->SetFont("Ayar.ttf");
	tempTextRenderer->SetLayer(3);
	tempTextRenderer->SetTextColor(255, 230, 255);
	tempTextRenderer->SetFontSize(20);
	tempTextRenderer->SetWarpAround(true);
	tempTextRenderer->SetText("Created By Buntek");
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);	
	
	buntek = new GameObject();
	tempRenderer = buntek->AddComponent<SpriteRenderer>();
	tempRenderer->SetLayer(2);
	tempRenderer->Size(500, 100);
	tempRenderer->SetTexture("Menu/Ball.png");
	tempTextRenderer = buntek->AddComponent<TextRenderer>();
	buntek->transform->SetPosition(Vector2(0, 275));
	tempTextRenderer->SetFont("Ayar.ttf");
	tempTextRenderer->SetLayer(3);
	tempTextRenderer->SetTextColor(255, 230, 255);
	tempTextRenderer->SetFontSize(14);
	tempTextRenderer->SetWarpAround(true);
	tempTextRenderer->SetText("Steven Koe \nBryan Boh \nAlgene Tan Chuan Hong \nGoh Kiat Beng \n Isaiah Lim Ji Rong");
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);

	professorheader = new GameObject();
	tempRenderer = professorheader->AddComponent<SpriteRenderer>();
	tempRenderer->SetLayer(2);
	tempRenderer->Size(500, 100);
	tempRenderer->SetTexture("Menu/Ball.png");
	tempTextRenderer = professorheader->AddComponent<TextRenderer>();
	professorheader->transform->SetPosition(Vector2(0, 150));
	tempTextRenderer->SetFont("Ayar.ttf");
	tempTextRenderer->SetLayer(3);
	tempTextRenderer->SetTextColor(255, 230, 255);
	tempTextRenderer->SetFontSize(20);
	tempTextRenderer->SetWarpAround(true);
	tempTextRenderer->SetText("Faculty And Advisors \nLab Management And IT");
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);

	professors = new GameObject();
	tempRenderer = professors->AddComponent<SpriteRenderer>();
	tempRenderer->SetLayer(2);
	tempRenderer->Size(500, 100);
	tempRenderer->SetTexture("Menu/Ball.png");
	tempTextRenderer = professors->AddComponent<TextRenderer>();
	professors->transform->SetPosition(Vector2(0, 115));
	tempTextRenderer->SetFont("Ayar.ttf");
	tempTextRenderer->SetLayer(3);
	tempTextRenderer->SetTextColor(255, 230, 255);
	tempTextRenderer->SetFontSize(14);
	tempTextRenderer->SetText("\nGerald Wong \nCheng Ding Xiang");
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);	
	
	schoolheader = new GameObject();
	tempRenderer = schoolheader->AddComponent<SpriteRenderer>();
	tempRenderer->SetLayer(2);
	tempRenderer->Size(500, 100);
	tempRenderer->SetTexture("Menu/Ball.png");
	tempTextRenderer = schoolheader->AddComponent<TextRenderer>();
	schoolheader->transform->SetPosition(Vector2(0, 25));
	tempTextRenderer->SetFont("Ayar.ttf");
	tempTextRenderer->SetLayer(3);
	tempTextRenderer->SetTextColor(255, 230, 255);
	tempTextRenderer->SetFontSize(20);
	tempTextRenderer->SetText("Created At");
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);	
	
	school = new GameObject();
	tempRenderer = school->AddComponent<SpriteRenderer>();
	tempRenderer->SetLayer(2);
	tempRenderer->Size(500, 100);
	tempRenderer->SetTexture("Menu/Ball.png");
	tempTextRenderer = school->AddComponent<TextRenderer>();
	school->transform->SetPosition(Vector2(0, 0));
	tempTextRenderer->SetFont("Ayar.ttf");
	tempTextRenderer->SetLayer(3);
	tempTextRenderer->SetTextColor(255, 230, 255);
	tempTextRenderer->SetFontSize(14);
	tempTextRenderer->SetText("Digipen Institute of Technology Singapore");
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);

	presidentheader = new GameObject();
	tempRenderer = presidentheader->AddComponent<SpriteRenderer>();
	tempRenderer->SetLayer(2);
	tempRenderer->Size(500, 100);
	tempRenderer->SetTexture("Menu/Ball.png");
	tempTextRenderer = presidentheader->AddComponent<TextRenderer>();
	presidentheader->transform->SetPosition(Vector2(0, -35));
	tempTextRenderer->SetFont("Ayar.ttf");
	tempTextRenderer->SetLayer(3);
	tempTextRenderer->SetTextColor(255, 230, 255);
	tempTextRenderer->SetFontSize(20);
	tempTextRenderer->SetText("President");
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);	
	
	president = new GameObject();
	tempRenderer = president->AddComponent<SpriteRenderer>();
	tempRenderer->SetLayer(2);
	tempRenderer->Size(500, 100);
	tempRenderer->SetTexture("Menu/Ball.png");
	tempTextRenderer = president->AddComponent<TextRenderer>();
	president->transform->SetPosition(Vector2(0, -60));
	tempTextRenderer->SetFont("Ayar.ttf");
	tempTextRenderer->SetLayer(3);
	tempTextRenderer->SetTextColor(255, 230, 255);
	tempTextRenderer->SetFontSize(14);
	tempTextRenderer->SetText("Claude Comair");
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
	
	executivesheader = new GameObject();
	tempRenderer = executivesheader->AddComponent<SpriteRenderer>();
	tempRenderer->SetLayer(2);
	tempRenderer->Size(500, 100);
	tempRenderer->SetTexture("Menu/Ball.png");
	tempTextRenderer = executivesheader->AddComponent<TextRenderer>();
	executivesheader->transform->SetPosition(Vector2(0, -110));
	tempTextRenderer->SetFont("Ayar.ttf");
	tempTextRenderer->SetLayer(3);
	tempTextRenderer->SetTextColor(255, 230, 255);
	tempTextRenderer->SetFontSize(20);
	tempTextRenderer->SetText("Executives");
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
	
	executives = new GameObject();
	tempRenderer = executives->AddComponent<SpriteRenderer>();
	tempRenderer->SetLayer(2);
	tempRenderer->Size(1000, 500);
	tempRenderer->SetTexture("Menu/Ball.png");
	tempTextRenderer = executives->AddComponent<TextRenderer>();
	executives->transform->SetPosition(Vector2(0, -135));
	tempTextRenderer->SetFont("Ayar.ttf");
	tempTextRenderer->SetLayer(3);
	tempTextRenderer->SetTextColor(255, 230, 255);
	tempTextRenderer->SetFontSize(14);
	tempTextRenderer->SetText("Jason Chu  Samir Abou Samra  Michele Comair\nChristopher Comair  Michal Gats  Raymond Yan\nPrasanna Ghali  John Bauer  Dr.Erik Mohrmann\nDr.Charles Duba  Angela Kugler  Johnny Deek\nBenjamin Elinger  Mevin Gonsavlez");
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);	
	
	softwareHeader = new GameObject();
	tempRenderer = softwareHeader->AddComponent<SpriteRenderer>();
	tempRenderer->SetLayer(2);
	tempRenderer->Size(1000, 500);
	tempRenderer->SetTexture("Menu/Ball.png");
	tempTextRenderer = softwareHeader->AddComponent<TextRenderer>();
	softwareHeader->transform->SetPosition(Vector2(0, -265));
	tempTextRenderer->SetFont("Ayar.ttf");
	tempTextRenderer->SetLayer(3);
	tempTextRenderer->SetTextColor(255, 230, 255);
	tempTextRenderer->SetFontSize(20);
	tempTextRenderer->SetText("Software Used");
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
	
	software = new GameObject();
	tempRenderer = software->AddComponent<SpriteRenderer>();
	tempRenderer->SetLayer(2);
	tempRenderer->Size(1000, 500);
	tempRenderer->SetTexture("Menu/Ball.png");
	tempTextRenderer = software->AddComponent<TextRenderer>();
	software->transform->SetPosition(Vector2(0, -290));
	tempTextRenderer->SetFont("Ayar.ttf");
	tempTextRenderer->SetLayer(3);
	tempTextRenderer->SetTextColor(255, 230, 255);
	tempTextRenderer->SetFontSize(14);
	tempTextRenderer->SetText("Fmod");
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);

	bottom = new GameObject();
	tempRenderer = bottom->AddComponent<SpriteRenderer>();
	tempRenderer->SetLayer(2);
	tempRenderer->Size(500, 100);
	tempRenderer->SetTexture("Menu/Ball.png");
	tempTextRenderer = bottom->AddComponent<TextRenderer>();
	bottom->transform->SetPosition(Vector2(0, -400));
	tempTextRenderer->SetFont("Ayar.ttf");
	tempTextRenderer->SetLayer(3);
	tempTextRenderer->SetTextColor(255, 230, 255);
	tempTextRenderer->SetFontSize(14);
	tempTextRenderer->SetWarpAround(true);
	tempTextRenderer->SetText("WWW.DIGIPEN.EDU \nAll content @ 2022 Digipen Institute of Technology Singapore. \nAll Rights Reserved");
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
}

void Scene_Credits::Update(void)
{
	backBtn->transform->SetPosition(Vector2(-670, 400));
}
Scene_Credits::~Scene_Credits(void)
{
	AudioManager.UnloadSound("ButtonHover.mp3");
	AssetManager.UnloadTexture("Menu/Button.png");
	AssetManager.UnloadTexture("Menu/ButtonPressed.png");
}

GameObject* Scene_Credits::GetObjRef(short type)
{
	if (type == 0)
		return backBtn;
	else
	{

	}
}


void BtnFunc_Back(Button* button)
{
	SceneManager.LoadScene(new Scene_MainMenu, TransitionType::FadeTransition, true);
}

void BtnFuncHover_Back(Button* button)
{
	/*if (menu->startPlay)
	{
		AudioManager.PlayClip("ButtonHover.mp3");
		button->Owner()->GetComponent<SpriteRenderer>()->SetTexture("Menu/ButtonPressed.png");
		menu->displayTxt->SetText("Start the game");
		cout << menu->displayTxt << endl;
		menu->startPlay = false;
	}

	Vector2 temp = menu->backBtnPos;
	temp.x = menu->GetObjRef(0)->transform->worldposition.x >= -650 ? -650 : menu->GetObjRef(0)->transform->worldposition.x + DeltaTime * 150;
	menu->GetObjRef(0)->transform->SetPosition(temp);*/
}

void BtnFuncUnhover_Back(Button* button)
{/*
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
	*/
}