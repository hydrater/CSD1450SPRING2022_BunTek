#pragma once
#include "Component.h"
#include "GameScript.h"


class Cursor : public GameScript
{
public:
	Cursor();
	~Cursor();
	void Start(void) override;
	void Update(void) override;
	bool Clicked;
	bool ValidClick;
	Vector2 CursorPosition;
	float CursorAngle;

	struct mouseWorldPosition
	{
		s32 x, y;
	};
	Vector2 GetWorldPosition(void);


private:
	mouseWorldPosition worldPosition = {0, 0};
};
