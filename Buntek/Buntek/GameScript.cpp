#include "GameScript.h"
#include "System.h"

GameScript::GameScript()
{
	hasStarted = false;
}

GameScript::~GameScript()
{
}

void GameScript::Init(GameObject* owner)
{
	this->gameObject = owner;
	// Add to event manager
	GameScriptManager.AddToList(this);
}

void GameScript::Start(void)
{

}

void GameScript::Awake(void)
{

}

void GameScript::Update(void)
{

}

void GameScript::setStarted(bool setValue)
{
	hasStarted = setValue;
}

bool GameScript::getStarted(void)
{
	return hasStarted;
}
