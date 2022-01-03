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
	vector<BallBehavior*> ballList;
	PaddleBehavior* playerpaddle;


private:

	bool AIEnabled = false;

	float AIscalingTimer = 0;
	float AITimer = 0;
};
