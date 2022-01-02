#include "Scene_MainMenu.h"
#include "SpriteRenderer.h"

GameObject* mainMenuBackground;

void Scene_MainMenu::Start(void)
{
	mainMenuBackground = new GameObject();
	mainMenuBackground->AddComponent<SpriteRenderer>()->Size(1920, 1080);
	mainMenuBackground->GetComponent<SpriteRenderer>()->SetTexture("MainMenu.png");
}

void Scene_MainMenu::Update(void)
{
}
