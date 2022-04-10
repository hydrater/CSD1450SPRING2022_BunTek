/*!*****************************************************************************
\file Entity.h
\project Beyond Aurorean Skies
\author: Algene Tan Chuan Hong (90%)
\co-authors: Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Entity
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/

#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>
#include <typeinfo>

using std::string;
using std::vector;

class Transform;
class Material;
class Component;
class GameObject
{
public:
	GameObject();
	~GameObject();

	// Compulsory component
	Transform* transform;

	const int GetID(void);
	bool IsActive(void);
	void Activate(void);
	void Deactivate(void);
	void AddChild(GameObject* child);
	void DetachChild(GameObject* child);
	void DetachChild(int number);
	void DetachAllChild(void);
	void DetachParent(void);
	Transform* GetParent(void);
	void Delete(void);

	template <typename T>
	T* AddComponent()
	{
		if (!GetComponent<T>())
		{
			T* comp = new T();
			components.push_back(comp);
			comp->Init(this);
			return comp;
		}
		return NULL;
	}

	template <typename T>
	T* GetComponent()
	{
		for (auto& c : components)
		{
			// UNCOMMENT THIS TO SEE WHAT CAUSE THE ERROR
			if (c->remove)
				return NULL;
			if (typeid(*c) == typeid(T))
			{
				return static_cast<T*>(c);
			}
		}
		return NULL;
	}

	template <typename T>
	bool RemoveComponent()
	{
		for (auto &c : components)
		{
			if (typeid(*c) == typeid(T))
			{
				c->remove = true;
				return true;
			}
		}
		return false;
	}
	bool remove;
private:
	bool active;
	
	vector<Component*> components;
};

#endif