#include "Scene_Navigation.h"
#include "GameManager.h"
#include "CursorCamera.h"
#include "Component.h"
#include "SpriteRenderer.h"

void Scene_Navigation::Start(void)
{
	MapData.GenerateList(Vector2(0, -1200));
	inputHandler = new GameObject();
	inputHandler->AddComponent<CursorCamera>()->camPos = Vector2(0, -900);
	AEGfxSetCamPosition(0, -900);
}

void Scene_Navigation::Update(void)
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.3f);
}
