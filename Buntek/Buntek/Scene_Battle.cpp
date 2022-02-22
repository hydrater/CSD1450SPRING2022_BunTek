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
	BattleHandler* _bh = BattleManager->GetComponent<BattleHandler>();

	
	
	EnemyHPBar = new GameObject();
	EnemyHPBar->transform->SetPosition(Vector2(0, 200));
	EnemyHPBar->AddComponent<UI_Hp>()->GenerateHpBar(false,100,100,5);
	
	SelfHPBar = new GameObject();
	SelfHPBar->transform->SetPosition(Vector2(0, -200));
	SelfHPBar->AddComponent<UI_Hp>()->GenerateHpBar(true);
	
}

void Scene_Battle::Update(void)
{
	
}

Scene_Battle::~Scene_Battle(void)
{
	
}
