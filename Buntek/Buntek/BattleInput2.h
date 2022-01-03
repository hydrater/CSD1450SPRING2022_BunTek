#pragma once
#include "Component.h"
#include "GameScript.h"
#include "BallBehavior.h"
#include "PaddleBehavior.h"
#include "Cursor.h"

class BattleInput2 : public GameScript
{
public:
	BattleInput2(void);
	~BattleInput2(void);
	void Start(void) override;
	void Update(void) override;
	vector<BallBehavior*> ballList;
	PaddleBehavior* playerpaddle, * AIPaddle;
	CursorBehaviour* playerCursor, * AICursor;


private:

	bool AIEnabled = false;
	float AIspeed = 0.05f;
	Vector2 AIposition = Vector2(0, 0);
	Vector2 AITargetPosition = Vector2(0, 0);

	float AIscalingTimer = 0;
	float AITimer = 0;
};
