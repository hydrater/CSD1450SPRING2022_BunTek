// ---------------------------------------------------------------------------
// includes
#include "Scene.h"

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
	Scene* scene = new Battle;
	scene->Awake();

	// ------------------------------------------ System Init ------------------------------------------- //
	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 800, 600, 1, 60, true, NULL);

	// Changing the window title
	AESysSetWindowTitle("idk we need a pong game name atm");

	// reset the system modules
	AESysReset();

	scene->Start();

	// --------------------------------------------- Init --------------------------------------------- //

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
		scene->Update();

		// --------------------------------------------- Render --------------------------------------------- //
		scene->Render();

		// ------------------------------------------- End of Loop ------------------------------------------- //
		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;
	}

	// ---------------------------------- Freeing the objects, fonts and textures ---------------------------------- //
	scene->Free();

	// free the system
	AESysExit();
}