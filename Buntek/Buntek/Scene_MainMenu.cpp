#include "Scene_MainMenu.h"
#include "SpriteRenderer.h"


void Scene_MainMenu::Start(void)
{
	background = new GameObject();
	background->AddComponent<SpriteRenderer>()->Size(1920, 1080);
	background->GetComponent<SpriteRenderer>()->SetTexture("MainMenu.png");
}

void Scene_MainMenu::Update(void)
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
}
