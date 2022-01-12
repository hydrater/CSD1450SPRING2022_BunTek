#pragma once
#include "System.h"
#include "BallBehavior.h"

class Scene_Battle : public Scene
{
public:
    void Start(void) override;
    void Update(void) override;
private:
    GameObject* inputHandler = 0;
	GameObject* background = 0, * ball = 0, * friendlyArea = 0, * hostileArea = 0, * neutralArea = 0, * playerpaddle = 0, * playercursor = 0, * AIpaddle = 0, * AIcursor = 0;
    float ballSpawnTimer = 0, scalingTimer = 0;
    vector<BallBehavior*>* ballList = 0;
};
