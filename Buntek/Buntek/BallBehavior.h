#pragma once
#include "GameScript.h"
#include "Vector2.h"

class BallBehavior : public GameScript
{
public:
	BallBehavior();
	~BallBehavior();
	void Test(void);

private:
	Vector2 position;
};