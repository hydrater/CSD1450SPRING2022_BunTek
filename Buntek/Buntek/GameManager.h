#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Vector2.h"
#include "Component.h"
using namespace std;

#define GameManager _gameManager::Instance()
#define MapData _mapData::Instance()

class Skill
{
private:

public:
    void SpawnSkillObject(void);
    int id = 0;
    string description;
    enum RarityTypes
    {
        common = 0,
        Rare = 1,
        Epic = 2,
        Legendary = 3
    };
    RarityTypes rarity = common;
};

class _gameManager
{
private:
    static _gameManager* instance;
    _gameManager();
    ~_gameManager();
    float cameraShakeTime = 0, shakeIntervalTimer= 0, shakeOffset = 0, cameraDecline = 0;
    char cameraShakeState = 0;
    Vector2 pos = Vector2(0, 0);
    Vector2 dir = Vector2(0, 0);
    const float shakeInterval = 0.05f;

public:
    static _gameManager& Instance(void);
    Skill skill1, skill2, skill3;
    void CameraUpdate(void);
    void CameraShake(float period, float cameraStrength, Vector2 direction);
    float clickAoERadius = 50;
    float areaTopBoundary = 0;
    float areaBottomBoundary = 0;
    float areaLeftBoundary = 0;
    float areaRightBoundary = 0;
    float friendlyAreaX = 0;
    float hostileAreaX = 0;

    
};

class _mapData
{
public:
    class Node
    {
    public:
        GameObject* clickable;
        short column;
        Vector2 pos;
        vector<Node*> connectedNodes;
        int id;
    };
    static _mapData& Instance(void);
    void GenerateList(void);
    void ClearList(void);

private:
    static _mapData* instance;
    vector<vector<Node>> nodeList;
};
