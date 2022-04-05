/*!*****************************************************************************
\file Component.h
\author: Algene Tan Chuan Hong (90%)
\co-authors: Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Components
*******************************************************************************/

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