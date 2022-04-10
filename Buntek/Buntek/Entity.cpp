/*!*****************************************************************************
\file Entity.cpp
\project Beyond Aurorean Skies
\author: Algene Tan Chuan Hong (90%)
\co-authors: Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Entity
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/

#include "Entity.h"
#include "Transform.h"
#include "Component.h"
#include "ECSManager.h"

GameObject::GameObject() :
active(true),
remove(false)
{
	transform = AddComponent<Transform>();
	ECSManager.AddGameObjectToList(this);
}

GameObject::~GameObject()
{
	
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
Transform* GameObject::GetParent(void)
{
	return transform->parent;
}

void GameObject::Delete(void)
{
	remove = true;
	for (int i = 0; i < transform->children.size(); ++i)
	{
		transform->children[i]->Owner()->Delete();
	}
	for (auto& c : components)
	{
		c->Remove();
	}
	/*for (size_t i = 0; i < components.size(); i++)
	{
		delete components[i];
	}*/
	//delete this;
}
