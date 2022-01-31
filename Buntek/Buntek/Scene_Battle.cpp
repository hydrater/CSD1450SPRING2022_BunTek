#include "Scene_Battle.h"
#include "Component.h"
#include "Entity.h"
#include "BattleHandler.h"
#include "AudioEngine.h"

using namespace Math;

void Scene_Battle::Start(void)
{
	BattleManager = new GameObject();
	BattleManager->AddComponent<BattleHandler>()->StartBattle();
}

void Scene_Battle::Update(void)
{
	
}

Scene_Battle::~Scene_Battle(void)
{
	
}
