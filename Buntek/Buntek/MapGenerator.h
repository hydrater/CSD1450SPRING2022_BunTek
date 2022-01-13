#pragma once
#include <vector>
#include "Vector2.h"
#include "Component.h"
#include <AEEngine.h>
#include "SpriteRenderer.h"

#define MapData _mapData::Instance()

enum class NodeType {
    Nothing,
    Enemy,
    Elite,
    Boss,
    Encounter,
    Rest,
    Shop
};

class _mapData
{
public:
    class Node
    {
    public:
        Vector2 pos;
        bool reached = false;
        vector<Node> LinkedTo;
        NodeType nodeType = NodeType::Nothing;
    };
    vector<AEGfxVertexList*> connectedLines;

    Node currentNode;
    static _mapData& Instance(void);
    void GenerateMapData(Vector2 originPos);
    void GenerateMapObject(void);
    void ClearList(void);

private:
    //void AssignLines(vector<Node> *largerList, vector<Node> *smallerList);
    bool canAccessFirstNode = true; // REMEMBER TO RESET THIS if using multiple start nodes
    static _mapData* instance;
    float minDistance = 150;
    float maxDistance = 400;
    float buffer = 75;
    const int numNodes = 20;
    vector<Node> nodeList;
    //bool CollideLines(Vector2 a, Vector2 b, Vector2 c, Vector2 d);
};