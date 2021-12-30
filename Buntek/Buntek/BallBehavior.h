#pragma once
#include "GameScript.h"

class BallBehavior : public GameScript
{
public:
	BallBehavior();
	~BallBehavior();
	void Test(void);
	void Start(void) override;
	void Update(void) override;

	Vector2 position;
	Vector2 velocity;
	float radius;
	float clickableAngleLeft;
	float clickableAngleRight;
private:

};