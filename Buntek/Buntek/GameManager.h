#pragma once
#include <typeinfo>
#include <vector>
#include "Vector2.h"
using namespace std;

#define GameManager _gameManager::Instance()

enum class RarityTypes : short
{
    Common = 0,
    Rare = 1,
    Lunary = 2,
    Astral = 3,
    Universal = 4
};

class Artifact
{
private:

public:
    void SpawnSkillObject(void);
    int id = 0;
    string description;
   
    RarityTypes rarity = RarityTypes::Common;
};

class _gameManager
{
private:
    static _gameManager* instance;
    _gameManager();
    ~_gameManager();
    float cameraShakeTime = 0, maxCameraShakeTime = 0, maxShakeStrength = 0, shakeStrength = 0, lerpSpeed = 1.0f;
    Vector2 pos = Vector2(0, 0);
    Vector2 dir = Vector2(0, 0);

public:
    static _gameManager& Instance(void);
    Vector2 GetCursorPosition(void);

    // Camera info
    void CameraUpdate(void);
    void CameraShake(float period, float cameraStrength, Vector2 direction);
    bool cameraLerpBack = false;

    // Battle arena info
    float clickAoERadius = 50;
    float areaTopBoundary = 0;
    float areaBottomBoundary = 0;
    float areaLeftBoundary = 0;
    float areaRightBoundary = 0;
    float friendlyAreaX = 0;
    float hostileAreaX = 0;

    // Player metrics, move to private?
    int health = 0;
    int damage = 0;
    int paddleSpeed = 0;
    int ballSpeed = 0;
    int ballSpawnSpeed = 0;

    // Currency
    int stardust = 0;
    int ballSpawnID = 0;
    vector<int> artifactStacks;
};
