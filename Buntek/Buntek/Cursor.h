#pragma once
#include "Component.h"
#include "GameScript.h"
#include "BallBehavior.h"

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
	
	Vector2 GetWorldPosition(void);
	vector<BallBehavior*> ballList;

private:
	struct mouseWorldPosition
	{
		s32 x, y;
	};
	mouseWorldPosition worldPosition = {0, 0};
};
