/*!*****************************************************************************
\file Component.cpp
\project Beyond Aurorean Skies
\author: Algene Tan Chuan Hong (90%)
\co-authors: Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Components
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/

#include "Component.h"
#include "ECSManager.h"

Component::Component() :
	active(true),
	remove(false)
{
	gameObject = NULL;
	ECSManager.AddComponentToList(this);
}

Component::~Component()
{
}

void Component::Init(GameObject* owner)
{
	this->gameObject = owner;
}

GameObject* Component::Owner(void)
{
	if (this != NULL)
		return gameObject;
	else
		return NULL;
}

bool Component::IsActive()
{
	return active;
}

void Component::Activate()
{
	active = true;
}

void Component::Deactivate()
{
	active = false;
}

void Component::Remove()
{
	remove = true;
}