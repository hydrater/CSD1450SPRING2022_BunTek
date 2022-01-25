#ifndef BATTLEHANDLER_H
#define BATTLEHANDLER_H
#include "GameScript.h"
#include "SpriteRenderer.h"
#include "BallBehavior.h"

//#define BattleHandler _battleHandler::Instance().GetComponent<_battleHandler>()

class _battleHandler : public GameScript
{
public:
	_battleHandler(void);
	~_battleHandler(void);
	void Start(void) override;
	void Update(void) override;
	void StartBattle(void);
	bool battleStarted = false;
	float timeScalar = 1;

	//static GameObject* instance;
	//static GameObject& Instance(void);

	GameObject* inputHandler = 0;
	GameObject* background = 0, * ball = 0, * friendlyArea = 0, * hostileArea = 0, * neutralArea = 0, * playerpaddle = 0, * playercursor = 0, * AIpaddle = 0, * AIcursor = 0, * hpBar = 0, * enemyhpBar = 0, * ballParticle = 0;
	float ballSpawnTimer = 0, scalingTimer = 0;
	vector<BallBehavior*>* ballList = 0;
	float hitPauseTimer = 0;
	bool checkTimer = false;

};

#endif