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
	void UpdateAIPosition(CursorBehaviour* Cursor, PaddleBehavior* Paddle, float* Timer, bool isPlayer);
	vector<BallBehavior*> ballList;
	PaddleBehavior* playerpaddle, * AIPaddle;
	CursorBehaviour* playerCursor, * AICursor;


private:

	bool AIEnabled = false;
	Vector2 AIposition = Vector2(0, 0);
	Vector2 AITargetPosition = Vector2(0, 0);
	float AITimer = 0;

	bool PlayerAIEnabled = false;
	Vector2 PlayerAIposition = Vector2(0, 0);
	Vector2 PlayerAITargetPosition = Vector2(0, 0);
	float PlayerAITimer = 0;

	float AIspeed = 0.05f;
	float AIscalingTimer = 0;
};
