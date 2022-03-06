#include "DebuggingTools.h"
#include "SaveManager.h"
#include "System.h"
#include "Scene_Battle.h"
#include "Scene_Splash.h"
#include "Scene_MainMenu.h"
#include "Scene_Navigation.h"
#include "Scene_Test.h"
#include "MapGenerator.h"

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
	if (AEInputCheckTriggered(AEVK_F1))
	{
		AEToogleFullScreen(fullScreen);
		fullScreen = !fullScreen;
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
		SaveManager.AddToArtifactList(420);
	}
}
