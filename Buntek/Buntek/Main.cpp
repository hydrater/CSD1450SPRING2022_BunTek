/*!*****************************************************************************
\file Main.cpp
\author: Algene Tan Chuan Hong (80%)
\co-authors: Isaiah Lim Ji Rong (10%), Steven Koe (3%), Bryan Boh Tai Hong (3%), Goh Kiat Beng (3%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Main logic
*******************************************************************************/
// ---------------------------------------------------------------------------
// includes
#include "Scene_Battle.h"
#include "Scene_Splash.h"
#include "Scene_MainMenu.h"
#include "Scene_Navigation.h"
#include "Scene_Test.h"
#include "UI_DialogueHandler.h"
#include "CollisionManager2D.h"
#include "AudioEngine.h"
#include "GameManager.h"
#include "Renderer.h"
#include "MapGenerator.h"
#include "SaveManager.h"
#include "ECSManager.h"
#include "DebuggingTools.h"

#include <windowsx.h>

short initStage = 0;
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
	AESysInit(hInstance, nCmdShow, 1900, 1050, 0, 120, true, NULL);
	//AEToogleFullScreen(true);

	// Changing the window title
	AESysSetWindowTitle("Beyond Aurorean Skies");

	// reset the system modules-
	AESysReset();

	// --------------------------------------------- Init --------------------------------------------- //
	AssetManager;
#if defined _DEBUG
	GameManager.isFullScreen = !GameManager.isFullScreen;
	AEToogleFullScreen(GameManager.isFullScreen);
#endif
	// Check if screen res is ultra wide for alpha testing
	{
#include "wtypes.h"
		//RECT desktop;
		//GetWindowRect(GetDesktopWindow(), &desktop);
		//if (desktop.right > 2500 || desktop.right < 1900 || desktop.bottom < 1050)
		//{
		//	cout << "Ultra wide monitor detected, disabling full screen...";
		//	GameManager.isFullScreen = false;
		//	AEToogleFullScreen(GameManager.isFullScreen);
		//}
	}
	AEToogleFullScreen(!GameManager.isFullScreen);
	// --------------------------------------------- Game Loop --------------------------------------------- //
	while (gGameRunning)
	{
		// ------------------------------------------- Start of Loop ------------------------------------------- //
		// Informing the system about the loop's start
		AESysFrameStart();

		// Check if need to minimize windows
		if (AESysGetWindowHandle() != GetFocus())
			ShowWindow(AESysGetWindowHandle(), SW_MINIMIZE);

		switch (initStage)
		{
			case 0:
			{
				AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
				initStage = 1;
				break;
			}

			case 1:
			{
				InitRNG();
				Renderer;
				ArtifactDatabase;
				GameManager;
				AudioManager;
				MapData;
				SaveManager.LoadData();
				SceneManager.LoadScene(new Scene_Splash, TransitionType::None, true);
				initStage = 2;
				break;
			}

			default:
			{
				// Handling Input
				AEInputUpdate();

				// Debugging tools
				Debugger.CheatsUpdate();

				// --------------------------------------------- Update --------------------------------------------- //
				SceneManager.EarlyUpdate();
				UIDialogueManager.Update();
				AudioManager.Update();
				SceneManager.Update();
				GameManager.Update();
				GameScriptManager.Update();

				// --------------------------------------------- Collision --------------------------------------------- //
				//CollisionManager2D.CollideAll();

				// --------------------------------------------- Render --------------------------------------------- //
				Renderer.Update();
				SceneManager.LateUpdate();

				// ------------------------------------------- End of Loop ------------------------------------------- //
				ECSManager.UpdateList();
				break;
			}
		}

		// Informing the system about the loop's end
		AESysFrameEnd();

		// check if forcing the application to quit
		if (0 == AESysDoesWindowExist() || GameManager.exit)
		{
			gGameRunning = 0;
			AudioManager.Free();
			AssetManager.Free();
			Renderer.Clear();
			Renderer.FreeMesh();
			ECSManager.Free();
		}
	}
	//
	// ---------------------------------- Freeing the objects, fonts and textures ---------------------------------- //
	//AssetManager.FreeAll();

	// free the system
	AESysExit();
}