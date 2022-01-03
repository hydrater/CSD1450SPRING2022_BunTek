#pragma once
#include "System.h"
#include "BallBehavior.h"

class Scene_Battle : public Scene
{
public:
    void Start(void) override;
    void Update(void) override;
private:
    GameObject* inputHandler;
    GameObject* background, * ball, * friendlyArea, * hostileArea, * neutralArea, * playerpaddle, *playercursor, *AIcursor;
    float ballSpawnTimer = 0, scalingTimer = 0;
    vector<BallBehavior*>* ballList;
};
