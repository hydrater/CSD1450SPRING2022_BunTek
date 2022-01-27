#ifndef BALLBEHAVIOR_H
#define BALLBEHAVIOR_H
#include "GameScript.h"
#include "SpriteRenderer.h"
#include "Collider2D.h"
#include "BattleInput.h"
#include "CollisionManager2D.h"
using namespace Math;

class BallBehavior : public GameScript
{
public:
	BallBehavior(void);
	~BallBehavior(void);
	void Start(void) override;
	void Update(void) override;

	void BounceBall(bool isPlayer, GameObject* wall, float angle);

	Vector2 velocity = Vector2(0, 0);
	float radius = 250;
	float GetSpeed(void);
	void SetSpeed(float _speed);
	void SetTargetSpeed(float _targetSpeed);
	void ReflectBall( bool hasPossession, GameObject* paddle);
	void HitBall(Vector2 mousePos, bool isPlayer);
	bool playerPossess = false;
	SpriteRenderer* sr = 0;
	Collider2D* col = 0;

	BattleInput* battleInput = 0;
	GameObject* ballParticle = 0;
	float hitPauseTimer = 0;
	bool checkTimer = false;

private:
	const float maxSpeed = 2000;
	float speed = 400;
	float targetSpeed = speed;
	float angRange = 60;
	Transform* transform = 0;

	void BallHorizontalCheck(void);
};
#endif