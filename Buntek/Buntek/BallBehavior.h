#pragma once
#include "GameScript.h"
#include "SpriteRenderer.h"

class BallBehavior : public GameScript
{
public:
	BallBehavior(void);
	~BallBehavior(void);
	void Start(void) override;
	void Update(void) override;

	Vector2 velocity = Vector2(0, 0);
	float radius = 250;
	float GetSpeed(void);
	void SetSpeed(float _speed);
	void HitBall(Vector2 mousePos, bool isPlayer);
	short listCheck = 139;
	bool playerPossess = false;
	SpriteRenderer* sr = 0;
	bool skillApplied = false;

	// Basic Elements
	bool elemAstral = false;
	bool elemVirtual = false;
	bool elemVirtualTriggered = false;
	bool elemElemental = false;

private:
	float initspeed = 300;
	float speed = 300;
	Transform* transform = 0;
};