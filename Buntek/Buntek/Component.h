#include <iostream>
#include <AEEngine.h>
#include "Entity.h"
#include "Transform.h"

using namespace std;

#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;
class Component
{
public:
	Component();
	virtual ~Component() = 0;

	// Function to initialize the component's owner when it is added to the entity
	virtual void Init(GameObject* owner);
	GameObject* Owner(void);

	bool IsActive(void);
	void Activate();
	void Deactivate();
	void Remove();	// queue it for deletion
	bool remove;	// queue for remove

protected:
	GameObject* gameObject;
	bool active;
	//bool add;	// queue for addition in runtime
};

#endif