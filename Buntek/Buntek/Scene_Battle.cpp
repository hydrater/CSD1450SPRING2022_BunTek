/*!*****************************************************************************
\file Scene_Battle.cpp
\project Beyond Aurorean Skies
\author: Algene Tan Chuan Hong (90%)
\co-authors: Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Scene Battle Screen
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/
#include "Scene_Battle.h"
#include "Component.h"
#include "Entity.h"
#include "BattleHandler.h"
#include "AudioEngine.h"
#include "GameManager.h"

using namespace Math;

void Scene_Battle::Start(void)
{
	BattleManager = new GameObject();
	BattleHandler* _bh = BattleManager->AddComponent<BattleHandler>();
	GameManager.bh = _bh;
	_bh->StartBattle(GameManager.playerProfile.hp, GameManager.playerProfile.basemaxhp,GameManager.enemyProfile.hp, GameManager.enemyProfile.basemaxhp,3);
}

void Scene_Battle::EarlyUpdate(void)
{
	if (IsWindowVisible(GetActiveWindow()) == FALSE && !GameManager.pauseMenuOpen && !GameManager.optionMenuOpen)
		GameManager.DisplayPauseMenu();
	else if (IsWindowVisible(GetActiveWindow()) == FALSE && GameManager.optionMenuOpen)
		AudioManager.PauseMusic(true);
	else if (GameManager.optionMenuOpen)
		AudioManager.PauseMusic(false);
}

void Scene_Battle::Update(void)
{
	
}

Scene_Battle::~Scene_Battle(void)
{
	
}
