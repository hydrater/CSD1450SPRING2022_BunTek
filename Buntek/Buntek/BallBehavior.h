#ifndef BALLBEHAVIOR_H
#define BALLBEHAVIOR_H
#include "GameScript.h"
#include "SpriteRenderer.h"
#include "Collider2D.h"
#include "BattleInput.h"
#include "CollisionManager2D.h"


class BallBehavior : public GameScript
{
public:
	BallBehavior(void);
	~BallBehavior(void);
	void Start(void) override;
	void Update(void) override;

	void BounceBall(bool isPlayer, GameObject* wall, float angle);

	GameObject* ballTrail = 0;
	SpriteRenderer* srBallTrail = 0;

	Vector2 velocity = Vector2(0, 0);
	float radius = 250;
	float GetSpeed(void);
	void SetSpeed(float _speed);
	void HitBall(Vector2 mousePos, bool isPlayer);
	bool playerPossess = false;
	SpriteRenderer* sr = 0;

	GameObject* ballParticle = 0;
	float hitPauseTimer = 0;
	bool checkTimer = false;

private:
	const float maxSpeed = 600;
	float initspeed = 300;
	float speed = 300;
	float angrange = 45;
	Transform* transform = 0;

	void BallHorizontalCheck(void);
};
#endif