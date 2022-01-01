// ---------------------------------------------------------------------------
// includes
#include "Scene_Battle.h"
#include "Scene_Splash.h"
#include "AssetManager.h"
#include "CollisionManager2D.h"
#include "AudioEngine.h"
#include "GameManager.h"

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
	// Move to main
	int gGameRunning = 1;

	// ------------------------------------------ System Init ------------------------------------------- //
	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 1920, 1060, 1, 60, true, NULL);
	//AEToogleFullScreen(true);

	// Changing the window title
	AESysSetWindowTitle("idk we need a pong game name atm");

	// reset the system modules-
	AESysReset();

	// --------------------------------------------- Init --------------------------------------------- //
	AssetManager;
	AudioManager;
	SceneManager.LoadScene(new Scene_Battle);
	// --------------------------------------------- Game Loop --------------------------------------------- //
	while (gGameRunning)
	{
		// ------------------------------------------- Start of Loop ------------------------------------------- //
		// Informing the system about the loop's start
		AESysFrameStart();

		// Handling Input
		AEInputUpdate();

		// Remove white backgrounds
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);

		// --------------------------------------------- Update --------------------------------------------- //
		SceneManager.Update();
		GameScriptManager.Update();
		AudioManager.Update();

		// --------------------------------------------- Render --------------------------------------------- //
		GameManager.CameraUpdate();
		AssetManager.RenderAll();

		// --------------------------------------------- Collision --------------------------------------------- //
		CollisionManager2D.CollideAll();
		// ------------------------------------------- End of Loop ------------------------------------------- //
		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
		{
			gGameRunning = 0;
			AssetManager.FreeAll();
		}
	}
	//
	// ---------------------------------- Freeing the objects, fonts and textures ---------------------------------- //
	//AssetManager.FreeAll();

	// free the system
	AESysExit();
	//CleanPlaying();
}