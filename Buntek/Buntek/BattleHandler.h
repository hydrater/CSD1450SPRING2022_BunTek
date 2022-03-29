/*!*****************************************************************************
\file BattleHandler.h
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief:File is used for handling of battles
*******************************************************************************/

#ifndef BATTLEHANDLER_H
#define BATTLEHANDLER_H
#include "GameScript.h"
#include "SpriteRenderer.h"
#include "BallBehavior.h"
#include "ParticleSystem.h"
#include <map>

class BattleHandler : public GameScript
{
public:
	BattleHandler(void);
	~BattleHandler(void);
	void Start(void) override;
	void Update(void) override;
	void StartBattle(float selfHp, float selfMaxHp, float enemyHp, float enemyMaxHp, int enemyHpBarCount);
	void SpawnBall(bool isPlayerBall);
	bool battleStarted = false;
	float mainTimeScalar = 1.0f;
	float timeScalar = mainTimeScalar;

	GameObject* inputHandler = 0;
	GameObject* background = 0, * ball = 0, * friendlyArea = 0, * hostileArea = 0, * neutralArea = 0, * playerpaddle = 0, * playercursor = 0, * AIpaddle = 0, * AIcursor = 0, * hpBar = 0, * enemyhpBar = 0, * ballParticle = 0;
	float playerBallSpawnTimerMax = 3, AIBallSpawnTimerMax = 3;
	float playerBallSpawnTimer = 3, AIBallSpawnTimer = 3, hitPauseTimer = 0;
	vector<BallBehavior*>* ballList = 0;
	bool checkTimer = false;

private:
	const float xOffset = 55, yOffset = 55, maxRow = 9;
	void SpawnArtifactList(Vector2 pos, map<unsigned long, int> artifactList, float xDir, float yDir);
	Vector2 playerArtifactListTopLeft = Vector2(0, 0), enemyArtifactListTopLeft = Vector2(0, 0);

	// Particle Effects
	const Vector2 particlePos = Vector2(0, 1);
	const float particleSpawnRate = 100.f, particleAngleSpread = 10.f;
	const float particlePowerMin = 80.f, particlePowerMax = 100.f;
	const float particleRotationMin = -10.f, particleRotationMax = 10.f;
	const float particleXDimension = 10.f, particleYDimension = 10.f;
	const short particleRenderLayer = 6;
};

#endif