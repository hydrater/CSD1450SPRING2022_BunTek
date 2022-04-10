/*!*****************************************************************************
\file GameScript.cpp
\project Beyond Aurorean Skies
\author: Algene Tan Chuan Hong (90%)
\co-authors: Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles GameScript
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/

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
