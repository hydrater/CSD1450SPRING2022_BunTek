#pragma once
#include "GameScript.h"

class BallBehavior : public GameScript
{
public:
	BallBehavior();
	~BallBehavior();
	void Start(void) override;
	void Update(void) override;

	Vector2 position;
	Vector2 velocity;
	float radius;
	float GetSpeed(void);
	void SetSpeed(float _speed);
	void HitBall(Vector2 mousePos, bool isPlayer);
	short listCheck = 139;
	bool playerPossess = false;

private:
	float speed;
	Transform* transform;
};