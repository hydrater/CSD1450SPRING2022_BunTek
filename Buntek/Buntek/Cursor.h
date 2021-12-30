#pragma once
#include "Component.h"
#include "GameScript.h"


class Cursor : public GameScript
{
public:
	Cursor();
	~Cursor();
	void Test(void);
	void Start(void) override;
	void Update(void) override;
	bool Clicked;
	bool ValidClick;
	Vector2 CursorPosition;
	float CursorAngle;

private:
};
