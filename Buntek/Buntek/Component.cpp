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