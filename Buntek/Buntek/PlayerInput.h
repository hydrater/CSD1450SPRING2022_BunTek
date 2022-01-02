#pragma once
#include "Component.h"
#include "GameScript.h"
#include "BallBehavior.h"

class PlayerInput : public GameScript
{
public:
	PlayerInput();
	~PlayerInput();
	void Start(void) override;
	void Update(void) override;
	Vector2 GetWorldPosition(void);
	vector<BallBehavior*> ballList;

private:
	struct mouseWorldPosition
	{
		s32 x, y;
	};
	mouseWorldPosition worldPosition = {0, 0};
};
