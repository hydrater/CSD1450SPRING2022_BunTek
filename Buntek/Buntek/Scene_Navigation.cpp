#include "Scene_Navigation.h"
#include "GameManager.h"
#include <vector>

void Scene_Navigation::Start(void)
{
	MapData.GenerateList(Vector2(0, -400));
}

void Scene_Navigation::Update(void)
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
}
