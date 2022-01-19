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
	GameManager;
	AssetManager;
	AudioManager;
	MapData;
	Renderer;
	SceneManager.LoadScene(new Scene_MainMenu, TransitionType::None);
	SaveManager.SaveData();
	SaveManager.LoadData();

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

		if (AEInputCheckTriggered(AEVK_1))
		{
			SceneManager.LoadScene(new Scene_Navigation, TransitionType::FadeToBlack);
		}

		if (AEInputCheckTriggered(AEVK_2))
		{
			SceneManager.LoadScene(new Scene_Battle, TransitionType::FadeToBlack);
		}
		if (AEInputCheckTriggered(AEVK_3))
		{
			SceneManager.LoadScene(new Scene_Test, TransitionType::FadeToBlack);
		}
		if (AEInputCheckTriggered(AEVK_4))
		{
			/*if (SceneManager.navigationScene != nullptr)
				SceneManager.LoadScene(SceneManager.navigationScene, TransitionType::FadeToBlack);*/
		}

		// --------------------------------------------- Update --------------------------------------------- //
		SceneManager.EarlyUpdate();
		GameScriptManager.Update();
		AudioManager.Update();
		SceneManager.Update();

		// --------------------------------------------- Render --------------------------------------------- //
		GameManager.CameraUpdate();
		Renderer.Update();
		SceneManager.LateUpdate();
		// --------------------------------------------- Collision --------------------------------------------- //
		CollisionManager2D.CollideAll();
		// ------------------------------------------- End of Loop ------------------------------------------- //
		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
		{
			gGameRunning = 0;
			Renderer.FreeAll();
		}
	}
	//
	// ---------------------------------- Freeing the objects, fonts and textures ---------------------------------- //
	//AssetManager.FreeAll();

	// free the system
	AESysExit();
	//CleanPlaying();
}