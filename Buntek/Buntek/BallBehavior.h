/*!*****************************************************************************
\file BallBehaviour.h
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief:File is used for changing of ballbehaviour
*******************************************************************************/

#ifndef BALLBEHAVIOR_H
#define BALLBEHAVIOR_H
#include "GameScript.h"
#include "SpriteRenderer.h"
#include "Collider2D.h"
#include "BattleInput.h"
#include "CollisionManager2D.h"
#include "ParticleSystem.h"

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
	bool ReflectBall( bool hasPossession, GameObject* paddle);
	void HitBall(Vector2 mousePos, bool isPlayer);
	bool playerPossess = false;
	SpriteRenderer* sr = 0;
	Collider2D* col = 0;
	Collider2D* savedCol = 0;	// Saved collider of another instance (For trigger on enter)

	vector<Status> statusEffect;

	BattleInput* battleInput = 0;
	GameObject* ballParticle = 0;
	ParticleSystem* ballParticleSystem = 0;
	float hitPauseTimer = 0.04f;
	bool causeHitPause = false;
	bool checkTimer = false;
	bool isFaster = false;
	float timeScalar = 1.0f;
	float paddleBounceMultiplier = 2;
	int ballPhase = -1;
	int ballDamage = 10;

private:
	float speed = 200;
	float targetSpeed = speed;
	const float maxSpeed = 200;

	const int maxBallPhase = 8;
	const float ballPhaseSpeedIncrement = 50;

	const float maxRotSpeed = 3600;
	float rotSpeed = 0;
	float targetRotSpeed = 0;
	float angRange = 30;
	Transform* transform = 0;

	void BallHorizontalCheck(void);
};
#endif