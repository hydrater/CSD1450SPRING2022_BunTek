// ---------------------------------------------------------------------------
// includes
#include "Scene_Battle.h"
#include "Scene_Splash.h"
#include "AudioEngine.h"
#include "AssetManager.h"

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
	AESysInit(hInstance, nCmdShow, 800, 600, 1, 60, true, NULL);

	// Changing the window title
	AESysSetWindowTitle("idk we need a pong game name atm");

	// reset the system modules-
	AESysReset();

	FMOD::System* system = NULL;
	FMOD::Channel* channel = nullptr;
	FMOD::ChannelGroup* channelGroup = nullptr;
	FMOD::Sound* sound = nullptr;
	SoundTest(system, channel, channelGroup, sound);

	// --------------------------------------------- Init --------------------------------------------- //
	AssetManager.Instance();
	SceneManager.LoadScene(new Scene_Battle);
	//SoundTest();
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

		bool isPlaying = false;
		LoopPlaying(&isPlaying, system, channel);
		// --------------------------------------------- Render --------------------------------------------- //
		AssetManager.RenderAll();
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

	// ---------------------------------- Freeing the objects, fonts and textures ---------------------------------- //
	

	// free the system
	AESysExit();
	CleanPlaying(system, channelGroup, sound);
}