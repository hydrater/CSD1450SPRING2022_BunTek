#pragma once
#include "GameScript.h"
#include "SpriteRenderer.h"

class BallBehavior : public GameScript
{
public:
	BallBehavior();
	~BallBehavior();
	void Start(void) override;
	void Update(void) override;

	Vector2 position = Vector2(0, 0);
	Vector2 velocity = Vector2(0, 0);
	float radius = 250;
	float GetSpeed(void);
	void SetSpeed(float _speed);
	void HitBall(Vector2 mousePos, bool isPlayer);
	short listCheck = 139;
	bool playerPossess = false;
	SpriteRenderer* sr;

private:
	float speed = 6;
	Transform* transform = 0;
};