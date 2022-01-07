#pragma once
#include "GameScript.h"
#include "SpriteRenderer.h"
#include "Collider2D.h"

class BallBehavior : public GameScript
{
public:
	BallBehavior(void);
	~BallBehavior(void);
	void Start(void) override;
	void Update(void) override;

	void UpdateTrail(void);

	GameObject* ballTrail;
	SpriteRenderer* srBallTrail = 0;

	Vector2 velocity = Vector2(0, 0);
	float radius = 250;
	float GetSpeed(void);
	void SetSpeed(float _speed);
	void HitBall(Vector2 mousePos, bool isPlayer);
	short listCheck = 139;
	bool playerPossess = false;
	SpriteRenderer* sr = 0;
	CircleCollider* circoll = 0;
	bool skillApplied = false;

	// Basic Elements
	bool elemAstral = false;
	bool elemVirtual = false;
	bool elemVirtualTriggered = false;
	bool elemElemental = false;

private:
	const float maxSpeed = 600;
	float initspeed = 300;
	float speed = 300;
	float angrange = 45;
	Transform* transform = 0;
};