// ---------------------------------------------------------------------------
// includes
#include "Scene_Battle.h"
#include "Scene_Splash.h"
#include "Scene_MainMenu.h"
#include "Scene_Navigation.h"
#include "Scene_Test.h"
#include "CollisionManager2D.h"
#include "AudioEngine.h"
#include "GameManager.h"
#include "Renderer.h"
#include "MapGenerator.h"
#include "SaveManager.h"
// ---------------------------------------------------------------------------
// main
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Enable run-time memory check for debug builds.
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif

	// --------------------------------------------- Awake --------------------------------------------- //
	int gGameRunning = 1;

	// ------------------------------------------ System Init ------------------------------------------- //
	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 1920, 1060, 1, 60, true, NULL);
	//AEToogleFullScreen(true);

	// Changing the window title
	AESysSetWindowTitle("Person who made this engine is gay");

	// reset the system modules-
	AESysReset();

	// --------------------------------------------- Init --------------------------------------------- //
	InitRNG();
	ArtifactDatabase;
	GameManager;
	AssetManager;
	AudioManager;
	MapData;
	Renderer;
	SceneManager.LoadScene(new Scene_Splash, TransitionType::None, true);
	//SceneManager.LoadScene(new Scene_Battle, TransitionTypes::None);
	//SceneManager.LoadScene(new Scene_Splash, TransitionTypes::None);
	//SceneManager.LoadScene(new Scene_Navigation, TransitionTypes::None);
	// --------------------------------------------- Game Loop --------------------------------------------- //
	while (gGameRunning)
	{
		// ------------------------------------------- Start of Loop ------------------------------------------- //
		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();

		// Debugging tools
		if (AEInputCheckTriggered(AEVK_1))
		{
			SceneManager.LoadScene(new Scene_Navigation, TransitionType::FadeTransition, true);
		}

		if (AEInputCheckTriggered(AEVK_2))
		{
			SceneManager.LoadScene(new Scene_Battle, TransitionType::FadeTransition, true);
		}
		if (AEInputCheckTriggered(AEVK_3))
		{
			SceneManager.LoadScene(new Scene_Test, TransitionType::FadeTransition, true);
		}

		if (AEInputCheckTriggered(AEVK_F1))
		{
			SaveManager.SaveData();
		}
		if (AEInputCheckTriggered(AEVK_F2))
		{
			SaveManager.LoadData();
		}
		if (AEInputCheckTriggered(AEVK_F3))
		{
			MapData.GenerateMapData();
		}

		// --------------------------------------------- Update --------------------------------------------- //
		SceneManager.EarlyUpdate();
		GameScriptManager.Update();
		AudioManager.Update();
		SceneManager.Update();

		// --------------------------------------------- Collision --------------------------------------------- //
		CollisionManager2D.CollideAll();

		// --------------------------------------------- Render --------------------------------------------- //
		GameManager.CameraUpdate();
		Renderer.Update();
		SceneManager.LateUpdate();

		// ------------------------------------------- End of Loop ------------------------------------------- //
		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
		{
			gGameRunning = 0;
			AudioManager.Free();
			AssetManager.Free();
			Renderer.FreeRenderComponents();
			Renderer.FreeMesh();
		}
	}
	//
	// ---------------------------------- Freeing the objects, fonts and textures ---------------------------------- //
	//AssetManager.FreeAll();

	// free the system
	AESysExit();
}