#include "Scene_Navigation.h"
#include "GameManager.h"
#include "CursorCamera.h"
#include "Component.h"
#include "SpriteRenderer.h"
#include "AssetManager.h"
#include "AudioEngine.h"
#include "MapGenerator.h"
#include "UI_Shop.h"
#include "UI_EncounterBox.h"

void Scene_Navigation::Start(void)
{
	SceneManager.navigationScene = this;
	MapData.GenerateMapData(Vector2(0, -1200));
	MapData.GenerateMapObject();
	MapData.DisplayCurrentRoutes();
	MapData.DisplayBossNode();
	inputHandler = new GameObject();
	//inputHandler->AddComponent<CursorCamera>()->camPos = Vector2(0, -900);
	//AEGfxSetCamPosition(0, -900);
	AudioManager.LoadMusic("NavigationBGM.mp3");
	AudioManager.PlayMusic("NavigationBGM.mp3");
	AudioManager.SetMusicVolume(0.1f);
}

void Scene_Navigation::EarlyUpdate(void)
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.3f);

	if (mesh == 0)
	{
		AEGfxMeshStart();

		AEGfxTriAdd(
			-2160.0f, -3840.0f, 0x00FF00FF, 0.0f, 1.0f,
			2160.0f, -3840.0f, 0x00FFFF00, 1.0f, 1.0f,
			-2160.0f, 3840.0f, 0x0000FFFF, 0.0f, 0.0f);

		AEGfxTriAdd(
			2160.0f, -3840.0f, 0x00FFFFFF, 1.0f, 1.0f,
			2160.0f, 3840.0f, 0x00FFFFFF, 1.0f, 0.0f,
			-2160.0f, 3840.0f, 0x00FFFFFF, 0.0f, 0.0f);
		mesh = AEGfxMeshEnd();
	}

	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0.0f, 0.0f);
	AEGfxSetTintColor(1, 1, 1, 1);
	AEGfxTextureSet(AssetManager.GetTexture("BetterNebula.png"), 0, 0);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition(0.0f, 0.0f);
	for (int i = 0; i < MapData.connectedLines.size(); i++)
	{
		AEGfxMeshDraw(MapData.connectedLines[i], AE_GFX_MDM_LINES_STRIP);
	}
}

void Scene_Navigation::Update(void)
{
	// [To ADD: Node travelling Animation]
	while (MapData.isTravelling)
	{
		MapData.isTravelling = false;
		MapData.Travel(MapData.destinationNode);
	}
}

void Scene_Navigation::LateUpdate(void)
{
	if (MapData.shopUI && MapData.shopUI->IsActive())
		MapData.shopUI->GetComponent<UI_Shop>()->SetClickable(true);
	if (MapData.encounterUI && MapData.encounterUI->IsActive())
		MapData.encounterUI->GetComponent<UI_EncounterBox>()->SetClickable(true);
}

Scene_Navigation::~Scene_Navigation(void)
{
	AudioManager.Free("NavigationBGM.mp3");
	AEGfxMeshFree(mesh);
}
