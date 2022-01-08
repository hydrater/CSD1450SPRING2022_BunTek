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
    //RarityTypes rarity = common;
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
    // this wont render lmao
    vector<AEGfxVertexList*> connectedLines;

    Node currentNode;
    static _mapData& Instance(void);
    void GenerateMapData(Vector2 originPos);
    void GenerateMapObject(void);
    void ClearList(void);

private:
    void AssignLines(vector<Node> *largerList, vector<Node> *smallerList);
    bool canAccessFirstNode = true; // REMEMBER TO RESET THIS
    static _mapData* instance;
    const float widthSize = 1400;
    const float cellHeight = 300;
    const int cellRows = 10;
    vector<vector<Node>> nodeList;
    bool CollideLines(Vector2 a, Vector2 b, Vector2 c, Vector2 d);
};



//	// Informing the library that we're about to start adding vertices
//	AEGfxMeshStart();
//
//	// This shape has 5 vertices
//	AEGfxVertexAdd(0.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f);
//	AEGfxVertexAdd(100.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f);
//	AEGfxVertexAdd(200.0f, 150.0f, 0xFFFFFFFF, 0.0f, 0.0f);
//	AEGfxVertexAdd(300.0f, -100.0f, 0xFFFFFFFF, 0.0f, 0.0f);
//	AEGfxVertexAdd(100.0f, -250.0f, 0xFFFFFFFF, 0.0f, 0.0f);
//	AEGfxVertexAdd(100.0f, -250.0f, 0xFFFFFFFF, 0.0f, 0.0f);
//	AEGfxVertexAdd(0.0f, 0.0f, 0xFFFFFFFF, 0.0f, 0.0f);
//
//	pMeshLine = AEGfxMeshEnd();