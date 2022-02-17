#pragma once
#include <typeinfo>
#include <vector>
#include "Vector2.h"
#include "ArtifactDatabase.h"
using namespace std;

#define GameManager _gameManager::Instance()

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
    bool exit = false;
    bool disableInteraction = false;
    Vector2 GetCursorPosition(void);

    // Profile
    struct Profile
    {
        // Current
        float hp;
        int stardust;
        int mapSize;
        short attackType;
    }playerProfile = {}, enemyProfile = {};

    struct BattleArtifactProfile
    {
        // Artifact list by events
        vector<Artifact> behaviorList_Passive;
        vector<Artifact> behaviorList_DealDamage;
        vector<Artifact> behaviorList_TakeDamage;
        vector<Artifact> behaviorList_WallBounce;
        vector<Artifact> behaviorList_PaddleHit;
        vector<Artifact> behaviorList_BallOnBallCollidision;

        // Any additional variables for specific artifacts
    }playerArtifactList = {}, enemyArtifactList{};

    // Camera info
    void CameraUpdate(void);
    void CameraShake(float period, float cameraStrength, Vector2 direction);
    void CameraEndShake(void);
    bool cameraLerpBack = false;

    // Battle arena info
    float areaTopBoundary = 0;
    float areaBottomBoundary = 0;
    float areaLeftBoundary = 0;
    float areaRightBoundary = 0;
    float friendlyAreaY = 0;
    float hostileAreaY = 0;

    // Battle
    void InitBattle(float _playerHp, float _enemyHp);
    void DealDamage(float damage, bool isPlayer);

    // Battle metrics
    float playerHp = 0, enemyHp = 0;
};
