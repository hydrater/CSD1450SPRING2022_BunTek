#pragma once
#include <vector>
#include "System.h"
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
        GameObject* nodeObject = 0;
        Vector2 pos;
        bool reached = false;
        vector<Node> linkedTo;
        NodeType nodeType = NodeType::Nothing;
    };
    vector<AEGfxVertexList*> connectedLines;

    Node currentNode;
    static _mapData& Instance(void);
    void GenerateMapData(Vector2 originPos);
    void GenerateMapObject(void);
    void ClearList(void);
    void Travel(Node* destination);
    void SetClickable(bool _canClick);
    void SetHoverable(bool _canHover);

    GameObject* shopUI = 0, * encounterUI = 0, * dialogueUI = 0;

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