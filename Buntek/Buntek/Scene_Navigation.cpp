#include "Scene_Navigation.h"
#include "GameManager.h"
#include "CursorCamera.h"
#include "Component.h"
#include "SpriteRenderer.h"
#include "AssetManager.h"
#include "AudioEngine.h"
#include "MapGenerator.h"
#include "UI_Shop.h"
#include "UI_DialogueHandler.h"

void Scene_Navigation::Start(void)
{
	if (MapData.nodeList.size() == 0)
		MapData.GenerateMapData(Vector2(0, -1200));

	MapData.GenerateMapObject();

	MapData.DisplayNodeRoutes(MapData.playerTravelDistance);
	MapData.DisplayBossNode();
	inputHandler = new GameObject();
	AudioManager.LoadMusic("NavigationBGM.mp3");
	AudioManager.PlayMusic("NavigationBGM.mp3");
	AudioManager.SetMusicVolume(1.0f);
}

// Draw all lines
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

	
	MapData.DisplayNodeRoutes(MapData.playerTravelDistance);

	//Draw connected lines
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
	UIDialogueManager.SetDialogueClickable(true);
}

Scene_Navigation::~Scene_Navigation(void)
{
	AudioManager.UnloadMusic("NavigationBGM.mp3");
	AEGfxMeshFree(mesh);
}
