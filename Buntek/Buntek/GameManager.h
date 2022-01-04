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
    float cameraShakeTime = 0, maxCameraShakeTime = 0, maxShakeStrength = 0, shakeStrength = 0, lerpSpeed = 1.0f;
    Vector2 pos = Vector2(0, 0);
    Vector2 dir = Vector2(0, 0);

public:
    static _gameManager& Instance(void);
    Vector2 GetCursorPosition(void);
    Skill skill1, skill2, skill3;

    void CameraUpdate(void);
    void CameraShake(float period, float cameraStrength, Vector2 direction);
    bool cameraLerpBack = false;

    float clickAoERadius = 50;
    float areaTopBoundary = 0;
    float areaBottomBoundary = 0;
    float areaLeftBoundary = 0;
    float areaRightBoundary = 0;
    float friendlyAreaX = 0;
    float hostileAreaX = 0;

    float easeIn(float t);
    float flip(float x);
    float easeOut(float t);
    float easeInOut(float t);
    float lerpF(float start_value, float end_value, float t);
};

class _mapData
{
public:
    class Node
    {
    public:
        GameObject* clickable;
        bool reached;
        vector<Node*> connectedNodes;
    };
    Node currentNode;
    static _mapData& Instance(void);
    void GenerateMapData(Vector2 originPos);
    void GenerateMapObject(void);
    void ClearList(void);

private:
    static _mapData* instance;
    vector<vector<Node>> nodeList;
};
