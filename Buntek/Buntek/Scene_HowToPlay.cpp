/*!*****************************************************************************
\file Scene_HowToPlay.cpp
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Scene How to play Screen
*******************************************************************************/

#include "Scene_MainMenu.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "AssetManager.h"
#include "GameManager.h"
#include "Scene_HowToPlay.h"
#include "AudioEngine.h"

void BtnFunc_BackMain(Button* button);
void BtnFuncHover_BackMain(Button* button);
void BtnFuncUnhover_BackMain(Button* button);

void Scene_HowToPlay::Start(void)
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AssetManager.LoadTexture("PlayGuide.png");
	AudioManager.LoadSound("ButtonHover.mp3");

	AssetManager.LoadTexture("Menu/ButtonPressed.png");

	playerGuide = new GameObject();
	SpriteRenderer* tempRenderer;
	tempRenderer = playerGuide->AddComponent<SpriteRenderer>();
	tempRenderer->SetLayer(2);
	tempRenderer->Size(1920, 1080);
	tempRenderer->SetTexture("PlayGuide.png");

	backmainBtn = new GameObject();
	tempRenderer = backmainBtn->AddComponent<SpriteRenderer>();
	tempRenderer->SetLayer(3);
	tempRenderer->Size(200, 71);
	tempRenderer->SetTexture("Menu/Button.png");
	backmainBtn->transform->SetPosition(Vector2(-820, 480));
	TextRenderer* tempTextRenderer;
	tempTextRenderer = backmainBtn->AddComponent<TextRenderer>();
	tempTextRenderer->SetFont("Ayar.ttf");
	tempTextRenderer->SetLayer(3);
	tempTextRenderer->SetTextColor(0, 0, 0);
	tempTextRenderer->SetText("Back");
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
	Button* button;
	button = backmainBtn->AddComponent<Button>();
	button->sr = tempRenderer;
	button->tr = tempTextRenderer;
	button->ButtonEffect = &BtnFunc_BackMain;
	button->HoverEffect = &BtnFuncHover_BackMain;
	button->NotHoverEffect = &BtnFuncUnhover_BackMain;
}

void Scene_HowToPlay::Update(void)
{
	
}
Scene_HowToPlay::~Scene_HowToPlay(void)
{
	AudioManager.UnloadSound("ButtonHover.mp3");
	AssetManager.UnloadTexture("Menu/ButtonPressed.png");
	AssetManager.UnloadTexture("PlayGuide.png");

}
void BtnFunc_BackMain(Button* button)
{
	SceneManager.LoadScene(new Scene_MainMenu, TransitionType::FadeTransition, true);
}

void BtnFuncHover_BackMain(Button* button)
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

void BtnFuncUnhover_BackMain(Button* button)
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
