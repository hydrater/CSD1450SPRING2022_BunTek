/*!*****************************************************************************
\file Scene_GameOver.cpp
\author: Algene Tan Chuan Hong (90%)
\co-authors: Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Scene Credits Screen
*******************************************************************************/

#include "Scene_MainMenu.h"
#include "AssetManager.h"
#include "GameManager.h"
#include "Devtools.h"
#include "Scene_GameOver.h"
#include "Scene_MainMenu.h"
#include "AudioEngine.h"

void Scene_GameOver::Start(void)
{
    AssetManager.LoadTexture("Gameover.png");

	gameOverBackground= new GameObject();
	SpriteRenderer* tempRenderer;
	tempRenderer = gameOverBackground->AddComponent<SpriteRenderer>();
	tempRenderer->SetLayer(1);
	tempRenderer->Size(1920, 1080);
	tempRenderer->SetTexture("Gameover.png");

	header = new GameObject();
	tempRenderer = header->AddComponent<SpriteRenderer>();
	tempRenderer->SetLayer(2);
	tempRenderer->Size(900, 700);
	tempRenderer->SetTexture("Menu/Ball.png");
	tempRenderer->SetOpacity(0);
	header->transform->SetPosition(Vector2(0, 0));
	gameOverTxt = header->AddComponent<TextRenderer>();
	gameOverTxt->SetFont("Ayar.ttf");
	gameOverTxt->SetFontSize(30);
	gameOverTxt->SetLayer(3);
	gameOverTxt->SetWarpAround(true);
	gameOverTxt->SetText("Game Over");
	gameOverTxt->SetTextColor(1, 1, 1);
	gameOverTxt->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	gameOverTxt->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);

	GameObject* tempObj = new GameObject();
	gameOverFade = tempObj->AddComponent<SpriteRenderer>();
	gameOverFade->SetLayer(3);
	gameOverFade->Size(1920, 1080);
	gameOverFade->SetTexture("Gameover.png");

	SceneManager.SetLoadTime(0);
}

void Scene_GameOver::Update(void)
{
	if (gameOverTime < 3)
	{
		gameOverTime += DeltaTime;
		gameOverTxt->SetFontSize(30 * (1 + gameOverTime));

		gameOverFade->SetOpacity(1 - gameOverTime/3);

		if (gameOverTime >= 3)
			SceneManager.LoadScene(new Scene_MainMenu, TransitionType::FadeTransition, true);
	}
}
Scene_GameOver::~Scene_GameOver(void)
{
	AssetManager.UnloadTexture("Gameover.png");
}
