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
	virtual void Update(void);
	void setStarted(bool setValue);
	bool getStarted(void);
private:
	bool hasStarted;
};

#endif