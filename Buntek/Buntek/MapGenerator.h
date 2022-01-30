#pragma once
#include <vector>
#include "System.h"
#include "Vector2.h"
#include "Component.h"
#include <AEEngine.h>
#include "SpriteRenderer.h"
#include "Button.h"

#define MapData _mapData::Instance()

enum class NodeType {
    Enemy,
    Elite,
    Shop,
    Encounter,
    Rest,
    Boss,
    Nothing
};

class _mapData
{
public:
    class Node
    {
    // Not all members are added to the sava manager as binary serialization is not pointer safe
    public:
        int ID = 0;
        Vector2 pos;
        short nodeState = false;
        NodeType nodeType = NodeType::Nothing;
        GameObject* nodeObject = nullptr;
    };
    vector<AEGfxVertexList*> connectedLines;

    Node* currentNode = nullptr;
    Node* destinationNode = nullptr;
    Node* exitNode = nullptr;
    const int numNodes = 20;
    static _mapData& Instance(void);
    void GenerateMapData(void);
    void GenerateMapObject(void);
    void DisplayNodeRoutes( float travelDistance);
    void DisplayNodeHistory(void);
    bool CheckHovered(Node* thisNode, Vector2 mousePos);
    void Travel(Node* destination);
    void SetClickable(bool _canClick);
    void SetHoverable(bool _canHover);
    Node* GetNode(GameObject* object);
    float playerTravelDistance = 400;

    GameObject* shopUI = 0, * encounterUI = 0, * dialogueUI = 0;

    bool isTravelling = false; // Flag used for checking when travelling across nodes before enacting node
    vector<Node*> nodeList;
    vector<int> travelHistoryIDs;
    vector<AEGfxVertexList*> travelHistoryLines;

private:
    //void AssignLines(vector<Node> *largerList, vector<Node> *smallerList);
    bool canAccessFirstNode = true; // REMEMBER TO RESET THIS if using multiple start nodes
    static _mapData* instance;
    float minDistance = 125;
    float maxDistance = 400;
    float buffer = 75;
    
    //bool CollideLines(Vector2 a, Vector2 b, Vector2 c, Vector2 d);
};