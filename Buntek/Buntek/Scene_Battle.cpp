/*!*****************************************************************************
\file Scene_Battle.cpp
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Scene Battle Screen
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

void Scene_Battle::Update(void)
{
	
}

Scene_Battle::~Scene_Battle(void)
{
	
}
