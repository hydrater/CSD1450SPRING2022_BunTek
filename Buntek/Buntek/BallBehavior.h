#pragma once
#include "GameScript.h"

class BallBehavior : public GameScript
{
public:
	BallBehavior();
	~BallBehavior();
	void Start(void) override;
	void Update(void) override;

	float AreaTopBoundary;
	float AreaBottomBoundary;
	float AreaLeftBoundary;
	float AreaRightBoundary;

	Vector2 position;
	Vector2 velocity;
	float radius;
	float clickableAngleLeft;
	float clickableAngleRight;
	float GetSpeed(void);
	void SetSpeed(float _speed);
	void HitBall(Vector2 mousePos);
	bool listCheck = false;

private:
	float speed;
	Transform* transform;
};