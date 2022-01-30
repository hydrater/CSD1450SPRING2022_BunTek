#include "MapGenerator.h"
#include "Scene_Battle.h"
#include "UI_EnemyNodeBox.h"
#include "UI_DialogueHandler.h"
#include "UI_Shop.h"
#include "Button.h"
#include "GameManager.h"

void EnactTravel(Button* button);

_mapData* _mapData::instance = 0;

_mapData& _mapData::Instance(void)
{
    if (instance != 0)
    {
        return *instance;
    }
    instance = new _mapData();
    return *instance;
}

void _mapData::GenerateMapData(void)
{
    nodeList.clear();
    float StartXCoord = (float)(-AEGetWindowWidth() / 2) + buffer;
    float EndXCoord = (float)(AEGetWindowWidth() / 2) - buffer;
    float StartYCoord = (float)(-AEGetWindowHeight() / 2) + buffer;
    float EndYCoord = (float)(AEGetWindowHeight() / 2) - buffer;

    for (int i = 0; i < numNodes; i++) 
    {
        Node* node = new Node();
        bool regenerateClose = true;
        bool hasNoConnection = false;
        node->pos = Vector2(RandIntMinMax((int)StartXCoord, (int)EndXCoord), RandIntMinMax((int)StartYCoord, (int)EndYCoord));
        node->ID = i;
        float minsq = minDistance * minDistance;
        float maxsq = maxDistance * maxDistance;
        if (nodeList.size() == 0) {
            node->nodeType = (NodeType)RandIntMinMax(0, 4);
            nodeList.push_back(node);
            currentNode = nodeList[0];
            exitNode = nodeList[0];
            continue;
        }
        while (regenerateClose || hasNoConnection) {
            node->pos = Vector2(RandIntMinMax((int)StartXCoord, (int)EndXCoord), RandIntMinMax((int)StartYCoord, (int)EndYCoord));
            regenerateClose = false;
            hasNoConnection = true;

            for (int j = 0; j < nodeList.size(); j++) {

                float distSq = (node->pos - nodeList[j]->pos).LengthSquared();

                if (distSq <= minsq) {
                    regenerateClose = true;
                    break;
                }
                else if (distSq <= maxsq) {
                    //cout << distSq << "\tis close enough to \t" << maxsq << endl;
                    hasNoConnection = false;
                    /* node->linkedTo.push_back(nodeList[j]);
                     nodeList[j]->linkedTo.push_back(node);*/
                }
            }
        }
        node->nodeType = (NodeType)RandIntMinMax(0, 4);
        nodeList.push_back(node);

        if (nodeList[i]->pos.x < (*currentNode).pos.x)
            currentNode = nodeList[i];

        if (nodeList[i]->pos.x > (*exitNode).pos.x)
            exitNode = nodeList[i];
    }

    currentNode->nodeType = NodeType::Nothing;
    exitNode->nodeType = NodeType::Boss;
}

void _mapData::GenerateMapObject(void)
{
    for (int i = 0; i < nodeList.size(); ++i)
    {
        GameObject* temp = new GameObject;
        SpriteRenderer* tempRenderer = temp->AddComponent<SpriteRenderer>();
        tempRenderer->Size(50, 50);

        Button* tempButton = temp->AddComponent<Button>();
        tempButton->sr = tempRenderer;
        tempButton->tr = NULL;
        tempButton->affectedObject = temp;
        tempButton->ButtonEffect = &EnactTravel;

        switch (nodeList[i]->nodeType)
        {
        case NodeType::Encounter:
            tempRenderer->SetTexture("UI/Encounter.png");
            break;
        case NodeType::Enemy:
            tempRenderer->SetTexture("UI/Enemy.png");
            temp->AddComponent<UI_EnemyNodeBox>();
            temp->GetComponent<UI_EnemyNodeBox>()->CreateEnemyNode(temp, 3, 10);
            break;
        case  NodeType::Elite:
            tempRenderer->SetTexture("UI/Elite.png");
            temp->AddComponent<UI_EnemyNodeBox>();
            temp->GetComponent<UI_EnemyNodeBox>()->CreateEnemyNode(temp, 3, 10);
            break;
        case NodeType::Shop:
            tempRenderer->SetTexture("UI/Shop.png");
            break;
        case NodeType::Rest:
            tempRenderer->SetTexture("UI/Rest.png");
            break;
        case NodeType::Boss:
            tempRenderer->SetTexture("UI/Boss.png");
            break;
        default:
            tempRenderer->SetTexture("Steven.jpg");
            break;
        }

        temp->transform->worldposition = Vector2(nodeList[i]->pos);
        nodeList[i]->nodeObject = temp;
    }
}

void _mapData::DisplayNodeRoutes(float travelDistance)
{
    // Don't run if UI or shop is open
    if (UIDialogueManager.UIOpen || MapData.shopUI)
    {
        MapData.SetClickable(false);
        MapData.SetHoverable(false);
        return;
    }

    MapData.connectedLines.clear();
    MapData.SetClickable(false);
    MapData.SetHoverable(false);
    for (int k = 0; k < nodeList.size(); k++)
    {
        bool closeEnough = false;
        float distBetSq = (nodeList[k]->pos - currentNode->pos).LengthSquared();
        closeEnough = distBetSq <= travelDistance * travelDistance;

        if (nodeList[k] != currentNode && closeEnough)
        {
            AEGfxVertexList* newLine;
            AEGfxMeshStart();
            AEGfxVertexAdd((*currentNode).pos.x, (*currentNode).pos.y, 0xFFFFFFFF, 0.0f, 0.0f);
            AEGfxVertexAdd((*nodeList[k]).pos.x, (*nodeList[k]).pos.y, 0xFFFFFFFF, 0.0f, 0.0f);
            newLine = AEGfxMeshEnd();
            MapData.connectedLines.push_back(newLine);

            nodeList[k]->nodeObject->GetComponent<Button>()->SetClickable(true);
            nodeList[k]->nodeObject->GetComponent<Button>()->SetHoverable(true);
        }
        
        // if node is being hovered over
        if (CheckHovered(nodeList[k], GameManager.GetCursorPosition())) {
            for (int i = 0; i < MapData.nodeList.size(); i++)
            {
                bool closeEnough = false;
                float distBetSq = (nodeList[i]->pos - nodeList[k]->pos).LengthSquared();
                closeEnough = distBetSq <= travelDistance * travelDistance;

                if (closeEnough && nodeList[i] != currentNode && nodeList[k] != currentNode && nodeList[i] != nodeList[k])
                {
                    AEGfxVertexList* newLine;
                    AEGfxMeshStart();
                    AEGfxVertexAdd((*nodeList[k]).pos.x, (*nodeList[k]).pos.y, 0xFFFFFFFF, 0.0f, 0.0f);
                    AEGfxVertexAdd((*nodeList[i]).pos.x, (*nodeList[i]).pos.y, 0xFFFFFFFF, 0.0f, 0.0f);
                    newLine = AEGfxMeshEnd();
                    MapData.connectedLines.push_back(newLine);
                }
            }
        }
    }
}

bool _mapData::CheckHovered(Node* thisNode, Vector2 mousePos) {
    SpriteRenderer* sr = thisNode->nodeObject->GetComponent<SpriteRenderer>();
    if (thisNode->pos.x - sr->GetHalfWidth() < mousePos.x && thisNode->pos.x + sr->GetHalfWidth() > mousePos.x) {

        if (thisNode->pos.y - sr->GetHalfHeight() < mousePos.y && thisNode->pos.y + sr->GetHalfHeight() > mousePos.y) {
            return true;
        }
    }
    return false;
}

void _mapData::Travel(Node* destination)
{
    if (destinationNode != nullptr)
    {
        // Get Artifacts and Stats [TO BE CHANGED WHEN ARTIFACTS AND STATS IMPLEMENTED!]
        vector<string> artifacts{ "E", "E", "A", "E", "E", "A" };
        vector<string> stats{ "E", "A", "E", "E", "A" };
        // Enact dest node effects
        currentNode = destinationNode;
        DisplayNodeRoutes(playerTravelDistance);
        switch (destinationNode->nodeType)
        {
        case NodeType::Encounter:
            SetClickable(false);
            SetHoverable(false);
            UIDialogueManager.CreateDialoguePreset("aed", 3);
            break;
        case NodeType::Enemy:
            SceneManager.LoadScene(new Scene_Battle, TransitionType::FadeTransition, true);
            break;
        case NodeType::Elite:
            SceneManager.LoadScene(new Scene_Battle, TransitionType::FadeTransition, true);
            break;
        case NodeType::Boss:
            SceneManager.LoadScene(new Scene_Battle, TransitionType::FadeTransition, true);
            break;
        case NodeType::Shop:
            SetClickable(false);
            SetHoverable(false);
            MapData.shopUI = new GameObject();
            MapData.shopUI->AddComponent<UI_Shop>();;
            MapData.shopUI->GetComponent<UI_Shop>()->CreateShop(3, artifacts, stats);
            break;
        case NodeType::Rest:

            break;
        default:
            break;
        }
    }
}

void _mapData::SetClickable(bool _canClick)
{
    for (int i = 0; i < nodeList.size(); ++i)
    {
        if (nodeList[i]->nodeObject)
            nodeList[i]->nodeObject->GetComponent<Button>()->SetClickable(_canClick);
    }
}

void _mapData::SetHoverable(bool _canHover)
{
    for (int i = 0; i < nodeList.size(); ++i)
    {
        if (nodeList[i]->nodeObject)
            nodeList[i]->nodeObject->GetComponent<Button>()->SetHoverable(_canHover);
    }
}

_mapData::Node* _mapData::GetNode(GameObject* object)
{
    for (Node* node : nodeList)
    {
        if (node->nodeObject == object)
            return node;
    }
}

void EnactTravel(Button* button)
{
    MapData.destinationNode = MapData.GetNode(button->Owner());
    MapData.isTravelling = true;
}
