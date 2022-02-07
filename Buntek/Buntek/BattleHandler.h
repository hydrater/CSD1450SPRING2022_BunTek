#ifndef BATTLEHANDLER_H
#define BATTLEHANDLER_H
#include "GameScript.h"
#include "SpriteRenderer.h"
#include "BallBehavior.h"

class BattleHandler : public GameScript
{
public:
	BattleHandler(void);
	~BattleHandler(void);
	void Start(void) override;
	void Update(void) override;
	void StartBattle(void);
	bool battleStarted = false;
	float mainTimeScalar = 1.0f;
	float timeScalar = mainTimeScalar;
	

	GameObject* inputHandler = 0;
	GameObject* background = 0, * ball = 0, * friendlyArea = 0, * hostileArea = 0, * neutralArea = 0, * playerpaddle = 0, * playercursor = 0, * AIpaddle = 0, * AIcursor = 0, * hpBar = 0, * enemyhpBar = 0, * ballParticle = 0;
	float ballSpawnTimer = 0, scalingTimer = 0;
	vector<BallBehavior*>* ballList = 0;
	bool checkTimer = false;

	float hitPauseTimer = 0;
};

#endif