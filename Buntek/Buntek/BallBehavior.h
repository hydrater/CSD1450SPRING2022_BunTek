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
	void AssignListPointer(BattleInput* _battleInput);
	void UpdateTrail(void);
	void BounceBall(bool isPlayer, Vector2 wallCoord, float angle);

	GameObject* ballTrail = 0;
	SpriteRenderer* srBallTrail = 0;

	Vector2 velocity = Vector2(0, 0);
	float radius = 250;
	float GetSpeed(void);
	void SetSpeed(float _speed);
	void HitBall(Vector2 mousePos, bool isPlayer);
	bool playerPossess = false;
	SpriteRenderer* sr = 0;

private:
	const float maxSpeed = 600;
	float initspeed = 300;
	float speed = 300;
	float angrange = 45;
	Transform* transform = 0;
	BattleInput* battleInput = 0;
	void BallVerticalCheck(void);
};
#endif