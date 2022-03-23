/*!*****************************************************************************
\file Scene_GameOver.cpp
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Scene Credits Screen
*******************************************************************************/

#include "Scene_MainMenu.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "AssetManager.h"
#include "GameManager.h"
#include "Devtools.h"
#include "Scene_GameOver.h"
#include "Scene_MainMenu.h"
#include "AudioEngine.h"

void Scene_GameOver::Start(void)
{
	//AssetManager.LoadTexture("Gameover.png");

	gameOverBackground= new GameObject();
	SpriteRenderer* tempRenderer;
	tempRenderer = gameOverBackground->AddComponent<SpriteRenderer>();
	tempRenderer->SetLayer(1);
	tempRenderer->Size(1920, 1080);
	tempRenderer->SetTexture("Gameover.png");
	//gameOverBackground->transform->SetPosition(Vector2(-820, 480));

	header = new GameObject();
	tempRenderer = header->AddComponent<SpriteRenderer>();
	tempRenderer->SetLayer(2);
	tempRenderer->Size(900, 700);
	tempRenderer->SetTexture("Menu/Ball.png");
	tempRenderer->SetOpacity(0);
	header->transform->SetPosition(Vector2(0, 400));
	TextRenderer* tempTextRenderer;
	tempTextRenderer = header->AddComponent<TextRenderer>();
	tempTextRenderer->SetFont("Ayar.ttf");
	tempTextRenderer->SetLayer(3);
	tempTextRenderer->SetWarpAround(true);
	tempTextRenderer->SetText("Game Over");
	tempTextRenderer->SetTextColor(191, 255, 191);
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);

}

void Scene_GameOver::Update(void)
{
	if (gameOverTime > 0)
	{
		gameOverTime -= DeltaTime;
		if (gameOverTime <= 0)
			SceneManager.LoadScene(new Scene_MainMenu, TransitionType::FadeTransition, true);
	}
}
Scene_GameOver::~Scene_GameOver(void)
{
	AssetManager.UnloadTexture("Gameover.png");
}

/*GameObject* Scene_GameOver::GetObjRef(short type)
{
	if (type == 0)
		return backBtn;
	else
	{

	}
}*/
