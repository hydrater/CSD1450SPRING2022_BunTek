#pragma once
#include "Component.h"
#include "GameScript.h"
#include "BallBehavior.h"
#include "PaddleBehavior.h"

class BattleInput : public GameScript
{
public:
	BattleInput(void);
	~BattleInput(void);
	void Start(void) override;
	void Update(void) override;
	Vector2 GetWorldPosition(void);
	vector<BallBehavior*> ballList;
	PaddleBehavior* playerpaddle;


private:
	struct mouseWorldPosition
	{
		s32 x, y;
	};
	mouseWorldPosition worldPosition = {0, 0};

	bool AIEnabled = false;
	float AITimer = 0;
};
