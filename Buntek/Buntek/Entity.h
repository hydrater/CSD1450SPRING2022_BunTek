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
	int id;
	bool active;
	
	vector<Component*> components;
};

#endif