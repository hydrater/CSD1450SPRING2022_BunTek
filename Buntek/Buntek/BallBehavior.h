#pragma once
#include "GameScript.h"

class BallBehavior : public GameScript
{
public:
	BallBehavior();
	~BallBehavior();
	void Start(void) override;
	void Update(void) override;
	//temp

	float AreaTopBoundary;
	float AreaBottomBoundary;
	float AreaLeftBoundary;
	float AreaRightBoundary;

	Vector2 position;
	Vector2 velocity;
	float radius;
	float clickableAngleLeft;
	float clickableAngleRight;
	float GetSpeed();

	bool listCheck = false;

private:
	float speed;
	Transform* transform;
};