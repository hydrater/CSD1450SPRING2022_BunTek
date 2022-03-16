/*!*****************************************************************************
\file MapGenerator.h
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Generates the map
*******************************************************************************/

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
    Enemy = 0,
    Encounter = 1,
    Shop = 2,
    Elite = 3,
    Rest = 4,
    Boss,
    Nothing
};

class _mapData
{
public:
    _mapData(void);
    ~_mapData(void);
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
    GameObject* penaltyZone = nullptr;
    float penaltySpeed = 200;
    Vector2 penaltyPos;
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
    void PenaltyZoneUpdate(void);
    void DeleteMapData(void);
    Node* GetNode(GameObject* object);
    float playerTravelDistance = 400;

    GameObject* shopUI = 0;

    bool isTravelling = false; // Flag used for checking when travelling across nodes before enacting node
    vector<Node*> nodeList;
    int historyIDSize = 0;
    vector<int> travelHistoryIDs;
    vector<AEGfxVertexList*> travelHistoryLines;

    // Shop Artifacts
    struct ShopArtifacts {
        int ID = 0;
        vector<unsigned long> ArtifactsOnDisplay;
        vector<bool> ArtifactsPurchased;
    };
    vector<ShopArtifacts> Shops;

private:
    //void AssignLines(vector<Node> *largerList, vector<Node> *smallerList);
    bool canAccessFirstNode = true; // REMEMBER TO RESET THIS if using multiple start nodes
    const float minDistance = 125;
    const float maxDistance = 400;
    const float xBuffer = 75;
    const float yBuffer = 150;
    //bool CollideLines(Vector2 a, Vector2 b, Vector2 c, Vector2 d);
};