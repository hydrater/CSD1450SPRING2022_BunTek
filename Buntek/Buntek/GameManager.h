/*!*****************************************************************************
\file GameManager.h
\author: Steven Koe (80%)
\co-authors: Algene Tan Chuan Hong (5%), Isaiah Lim Ji Rong (5%), Bryan Boh Tai Hong (5%), Goh Kiat Beng (5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Manages the Game
*******************************************************************************/

#pragma once
#include <typeinfo>
#include <vector>
#include "Vector2.h"
#include "ArtifactDatabase.h"
#include <map>
#include "BattleHandler.h"
using namespace std;

#define GameManager _gameManager::Instance()

class _gameManager
{
private:
    static _gameManager* instance;
    _gameManager();
    ~_gameManager();
    float cameraShakeTime = 0, maxCameraShakeTime = 0, maxShakeStrength = 0, shakeStrength = 0, lerpSpeed = 1.0f;

    Vector2 dir = Vector2(0, 0);
    map<unsigned long, int> EnemyArtifactData;
    short currentEnemy = 1;

    const float artifactsUIXSize = 800.f, artifactsUIYSize = 600.f;
    const short artifactsUILayer = 10;
    const Vector2 artifactObjPos = Vector2(-300.f, 160.f);
    const short artifactsObjLayer = 11;

public:
    static _gameManager& Instance(void);
    bool exit = false;
    bool disableInteraction = false;
    Vector2 GetCursorPosition(void);

    // Profile
    struct Profile
    {
        // Current
        float hp = 100;
        float basemaxhp = 100;
        int stardust;
        int currLevel = 1;
        short attackType;

        float bonusHp = 0;
        int bonusDamage = 0;
        float bonusPaddleSpeed = 1;
        float bonusBallSpeed = 1;
        float bonusBallSpawnRate = 1;
        float bonusHealing = 1;
    }playerProfile = {}, enemyProfile = {};

    struct BattleArtifactProfile
    {
        // Artifact list by events
        vector<Artifact> behaviorList_Passive;
        vector<Artifact> behaviorList_BattleWon;
        vector<Artifact> behaviorList_DealDamage;
        vector<Artifact> behaviorList_TakeDamage;
        vector<Artifact> behaviorList_WallBounce;
        vector<Artifact> behaviorList_PaddleHit;
        vector<Artifact> behaviorList_BallOnBallCollision;

        // Any additional variables for specific artifacts
        vector<Status> statusEffect;
    }playerArtifactList = {}, enemyArtifactList{};

    void InitBattleProfile(BattleArtifactProfile& battleProfile, map<unsigned long, int> artifactSaveData);
    map<unsigned long, int> GenerateArtifactList(int maxAmtOfArtifacts);

    // Camera info
    void Update(void);
    void CameraShake(float period, float cameraStrength, Vector2 direction);
    void CameraEndShake(void);
    bool cameraLerpBack = false;
    Vector2 pos = Vector2(0, 0);
    bool isFullScreen = true;

    // Artifact list UI
    GameObject* artifactListUI = NULL;
    void DisplayArtifactList(void);
    const float xOffset = 70, yOffset = 70, maxRow = 9;

    // Battle arena info
    float areaTopBoundary = 0;
    float areaBottomBoundary = 0;
    float areaLeftBoundary = 0;
    float areaRightBoundary = 0;
    float friendlyAreaY = 0;
    float hostileAreaY = 0;

    // Exploration
    int level = 0;
    void StartBattle(short enemyType);

    // Battle
    void InitBattle(float _playerHp, float _enemyHp);
    void DealDamage(float damage, bool isPlayer);
    void HealthCheck(bool isPlayer);
    short GetEnemyType(void);
    void PlayRandomBallSound(void);

    // Battle metrics
    BattleHandler* bh = 0;
    float playerHp = 0 , enemyHp = 0;
    bool battleOver = false, battleRewardPending = false;

    // Menu UI
    GameObject* optionMenuUI = NULL;
    bool optionMenuOpen = false;
    void DisplayOptionMenu(void);
    GameObject* pauseMenuUI = NULL;
    bool pauseMenuOpen = false;
    void DisplayPauseMenu(void);
    void DisplayPauseOptionMenu(void);
    GameObject* howToPlayMenuUI = NULL;
    bool howToPlayMenuOpen = false;
    void DisplayHowToPlayMenu(void);
    void DisplayPauseHowToPlayMenu(void);

    // Game over
    void GameOver(void);
};
