#include "Scene_MainMenu.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "Scene_Navigation.h"
#include "UI_Shop.h"
#include "AssetManager.h"
#include "GameManager.h"
#include "AudioEngine.h"
#include "Parallaxer.h"
#include "Devtools.h"
#include "Scene_Options.h"
#include "Scene_HowToPlay.h"
#include "Scene_Credits.h"

/*void BtnFunc_Next(Button* button);
void BtnFuncHover_Next(Button* button);
void BtnFuncUnhover_Next(Button* button);*/

void Scene_HowToPlay::Start(void)
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	/*startBtn = new GameObject();
	SpriteRenderer* tempRenderer;
	tempRenderer = startBtn->AddComponent<SpriteRenderer>();
	tempRenderer->SetLayer(2);
	tempRenderer->Size(471, 71);
	tempRenderer->SetTexture("Menu/Button.png");
	TextRenderer* tempTextRenderer;
	tempTextRenderer = startBtn->AddComponent<TextRenderer>();
	tempTextRenderer->SetFont("Ayar.ttf");
	tempTextRenderer->SetLayer(3);
	tempTextRenderer->SetTextColor(0, 0, 0);
	tempTextRenderer->SetText("Start");
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
	startBtn->transform->SetPosition(Vector2(-670, 1000));*/
}

void Scene_HowToPlay::Update(void)
{

}
Scene_HowToPlay::~Scene_HowToPlay(void)
{

}
;
