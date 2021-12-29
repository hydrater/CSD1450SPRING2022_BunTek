#pragma once
#ifndef SCRIPT_H
#define SCRIPT_H

#include "Component.h"

class GameScript : public Component
{
public:
	GameScript();
	virtual ~GameScript();

	void Init(GameObject* owner) override;
	virtual void Start(void);
	virtual void Awake(void);
	virtual void Update(void);
private:
	bool hasStarted;
};

#endif