#include "Scene_MainMenu.h"
#include "SpriteRenderer.h"
#include "TextRenderer.h"
#include "AssetManager.h"
#include "GameManager.h"
#include "Devtools.h"
#include "Scene_Credits.h"

void Scene_Credits::Start(void)
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	header = new GameObject();
	SpriteRenderer* tempRenderer;
	tempRenderer = header->AddComponent<SpriteRenderer>();
	tempRenderer->SetLayer(2);
	tempRenderer->Size(1000, 1000);
	tempRenderer->SetTexture("Menu/Button.png");
	TextRenderer* tempTextRenderer;
	tempTextRenderer = header->AddComponent<TextRenderer>();
	tempTextRenderer->SetFont("Ayar.ttf");
	tempTextRenderer->SetLayer(3);
	tempTextRenderer->SetTextColor(0, 0, 0);
	tempTextRenderer->SetText("Credits\n123");
	tempTextRenderer->SetXAlignment(TextRenderer::xAlignmentTypes::Mid);
	tempTextRenderer->SetYAlignment(TextRenderer::yAlignmentTypes::Mid);
}

void Scene_Credits::Update(void)
{

}
Scene_Credits::~Scene_Credits(void)
{

}
;
