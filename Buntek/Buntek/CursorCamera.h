#pragma once
#include "GameScript.h"

class CursorCamera : public GameScript
{
public:
	CursorCamera(void);
	~CursorCamera(void);
	void Start(void) override;
	void Update(void) override;
	Vector2 camPos = Vector2(0, 0);

private:
	s32 x, y;
	const float upperBoundary = 200, lowerBoundary = 860, leftBoundary = 200, rightBoundary = 1720;
	const float maxX = 400, maxY = 1200;
	const float cameraMoveSpeed = 300;
};