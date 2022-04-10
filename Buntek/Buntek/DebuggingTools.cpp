/*!*****************************************************************************
\file DebuggingTools.cpp
\project Beyond Aurorean Skies
\author: Algene Tan Chuan Hong (90%)
\co-authors: Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Debugging Tools
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/

#include "DebuggingTools.h"
#include "SaveManager.h"
#include "System.h"
#include "Scene_Battle.h"
#include "Scene_Splash.h"
#include "Scene_MainMenu.h"
#include "Scene_Navigation.h"
#include "Scene_Test.h"
#include "MapGenerator.h"
#include "AudioEngine.h"

_debuggingTools::_debuggingTools()
{
}

_debuggingTools::~_debuggingTools()
{
}

_debuggingTools& _debuggingTools::Instance(void)
{
	static _debuggingTools instance;
	return instance;
}

void _debuggingTools::CheatsUpdate(void)
{
	#if NDEBUG
	return;
	#endif
	if (AEInputCheckTriggered(AEVK_F1))
	{
		GameManager.isFullScreen = !GameManager.isFullScreen;
		AEToogleFullScreen(GameManager.isFullScreen);
	}

	if (AEInputCheckTriggered(AEVK_1))
	{
		GameManager.disableInteraction = false;
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
	if (AEInputCheckTriggered(AEVK_4))
	{
		AudioManager.SetMusicVolume(0);
	}
	if (AEInputCheckTriggered(AEVK_5))
	{
		AudioManager.SetMusicVolume(1.0f);
	}
	
	if (AEInputCheckTriggered(AEVK_F2))
	{
		SaveManager.SaveData();
	}
	if (AEInputCheckTriggered(AEVK_F3))
	{
		SaveManager.LoadData();
	}
	if (AEInputCheckTriggered(AEVK_F4))
	{
		MapData.GenerateMapData();
	}
	if (AEInputCheckTriggered(AEVK_F5))
	{
		SceneManager.LoadScene(new Scene_Splash, TransitionType::FadeTransition, true);
	}
	if (AEInputCheckTriggered(AEVK_F6))
	{
		SceneManager.LoadScene(new Scene_MainMenu, TransitionType::None, true);
	}
	if (AEInputCheckTriggered(AEVK_O))
	{
		// Add all Artifacts
		SaveManager.AddToArtifactList(420);
		SaveManager.AddToArtifactList(420);
		SaveManager.AddToArtifactList(0);
		SaveManager.AddToArtifactList(1);
		SaveManager.AddToArtifactList(2);
		SaveManager.AddToArtifactList(3);
		SaveManager.AddToArtifactList(4);
		SaveManager.AddToArtifactList(30);
		SaveManager.AddToArtifactList(120);
		SaveManager.AddToArtifactList(140);
		SaveManager.AddToArtifactList(220);
		SaveManager.AddToArtifactList(221);
		SaveManager.AddToArtifactList(500);
		SaveManager.AddToArtifactList(520);
		SaveManager.AddToArtifactList(540);
	}
}
