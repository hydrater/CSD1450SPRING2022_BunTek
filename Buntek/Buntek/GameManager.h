#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Vector2.h"
#include "Component.h"
using namespace std;

#define GameManager _gameManager::Instance()
#define MapData _mapData::Instance()

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
    Artifact skill1, skill2, skill3;

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
};

class Connection
{
public:
    Vector2 point1;
    Vector2 point2;
};

class _mapData
{
public:
    class Node
    {
    public:
        GameObject* clickable;
        Vector2 pos;
        bool reached = false;
        vector<Node*> connectedNodes;
        vector<Node*> connectedFrom;
    };
    vector<AEGfxVertexList*> connectedLines;

    Node currentNode;
    static _mapData& Instance(void);
    void GenerateMapData(Vector2 originPos);
    void GenerateMapObject(void);
    void ClearList(void);

private:
    void AssignLines(vector<Node> *largerList, vector<Node> *smallerList);
    bool canAccessFirstNode = true; // REMEMBER TO RESET THIS if using multiple start nodes
    static _mapData* instance;
    const float widthSize = 1400;
    const float cellHeight = 300;
    const int cellRows = 10;
    vector<vector<Node>> nodeList;
    bool CollideLines(Vector2 a, Vector2 b, Vector2 c, Vector2 d);
};
