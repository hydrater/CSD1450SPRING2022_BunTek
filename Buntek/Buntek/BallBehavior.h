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

private:
	Vector2 position;
};