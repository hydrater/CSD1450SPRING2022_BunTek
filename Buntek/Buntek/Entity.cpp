#include "Entity.h"
#include "Transform.h"
#include "Component.h"

GameObject::GameObject() :
active(true),
remove(false)
{
	transform = AddComponent<Transform>();
}


GameObject::~GameObject()
{
	transform->children.clear();
	transform->parent->Owner()->DetachChild(this);
	transform->parent = NULL;
	for (unsigned i = 0; i < components.size(); ++i)
	{
		if (components[i] != NULL)
		{
			delete components[i];
			components[i] = NULL;
		}
	}
}

const int GameObject::GetID(void)
{
	return id;
}

bool GameObject::IsActive(void)
{
	return active;
}

void GameObject::Activate(void)
{
	active = true;
}

void GameObject::Deactivate(void)
{
	active = false;
}

void GameObject::AddChild(GameObject* child)
{
	//children.push_back(child);
	//child->parent = this;
	child->transform->localposition = child->transform->worldposition - transform->worldposition;
	transform->children.push_back(child->transform);
	//transform->parent = transform;
	child->transform->parent = transform;
}

void GameObject::DetachChild(GameObject* child)
{
	for (unsigned i = 0; i < transform->children.size(); ++i)
	{
		if (transform->children[i] == child->transform)
		{
			transform->children[i]->parent = NULL;
			transform->children.erase(transform->children.begin() + i);
			break;
		}
	}
}

void GameObject::DetachChild(int number)
{
	transform->children[number]->parent = NULL;
	transform->children.erase(transform->children.begin() + number);
}

void GameObject::DetachAllChild(void)
{
	for (unsigned i = 0; i < transform->children.size(); ++i)
	{
		transform->children[i]->parent = NULL;
	}

	transform->children.clear();
}

void GameObject::DetachParent(void)
{
	transform->parent = NULL;
}

void GameObject::Delete(void)
{
	remove = true;
	for (int i = 0; i < transform->children.size(); ++i)
	{
		transform->children[i]->Owner()->Delete();
	}
	for (auto &c : components)
	{
		c->Remove();
	}
}
