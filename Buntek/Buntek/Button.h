#pragma once
#include "GameScript.h"

class Button : public GameScript
{
public:
	Button(void);
	~Button(void);
	void Start(void) override;
	void Update(void) override;
private:

};