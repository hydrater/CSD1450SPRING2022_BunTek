#include "Component.h"

Component::Component() :
	active(true),
	remove(false)
{
	gameObject = NULL;
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
	return gameObject;
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