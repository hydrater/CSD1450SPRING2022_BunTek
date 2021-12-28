#include "GameScript.h"


GameScript::GameScript()
{
}


GameScript::~GameScript()
{
}

void GameScript::Init(Entity* owner)
{
	this->owner = owner;
	// Add to event manager
	cout << "Game script override success" << endl;
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
