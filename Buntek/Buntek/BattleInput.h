/*!*****************************************************************************
\file BattleInput.h
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Battle's Input
*******************************************************************************/

#ifndef BATTLEINPUT_H
#define BATTLEINPUT_H
#include "Component.h"
#include "GameScript.h"
#include "PaddleBehavior.h"
#include "Cursor.h"

class BallBehavior;
class BattleInput : public GameScript
{
public:
	BattleInput(void);
	~BattleInput(void);
	void Start(void) override;
	void Update(void) override;
	void RemoveFromList(BallBehavior* ballbehavior);
	void UpdateAIPosition(CursorBehaviour* Cursor, PaddleBehavior* Paddle, float* Timer, bool isPlayer);
	vector<BallBehavior*> ballList;
	PaddleBehavior* playerpaddle = 0, * AIPaddle = 0;
	CursorBehaviour* playerCursor = 0, * AICursor = 0;
	GameObject* LaunchBall = 0, *LaunchLine = 0;
	float timeScalar = 1.0f;
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

	const float AIRestYPosition = 400.f;

	const float ballSpeed = 300.f;
};
#endif