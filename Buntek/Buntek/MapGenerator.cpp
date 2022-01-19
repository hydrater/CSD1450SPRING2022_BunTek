#include "MapGenerator.h"
#include "Scene_Battle.h"
#include "UI_EnemyNodeBox.h"
#include "UI_EncounterBox.h"
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

void _mapData::GenerateMapData(Vector2 originPos)
{
    nodeList.clear();
    float StartXCoord = (float)(-AEGetWindowWidth() / 2) + buffer;
    float EndXCoord = (float)(AEGetWindowWidth() / 2) - buffer;
    float StartYCoord = (float)(-AEGetWindowHeight() / 2) + buffer;
    float EndYCoord = (float)(AEGetWindowHeight() / 2) - buffer;

    for (int i = 0; i < numNodes; i++) {
        Node* node = new Node();
        bool regenerateClose = true;
        bool hasNoConnection = false;
        node->pos = Vector2(RandIntMinMax((int)StartXCoord, (int)EndXCoord), RandIntMinMax((int)StartYCoord, (int)EndYCoord));
        float minsq = minDistance * minDistance;
        float maxsq = maxDistance * maxDistance;
        if (nodeList.size() == 0) {
            nodeList.push_back(node);
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
                    cout << distSq << "\tis close enough to \t" << maxsq << endl;
                    hasNoConnection = false;
                   /* node->linkedTo.push_back(nodeList[j]);
                    nodeList[j]->linkedTo.push_back(node);*/
                }
            }
        }
        nodeList.push_back(node);
    }

    //for (int i = 0; i < cellRows; i++)
    //{
    //    short width = 1;
    //    if (!(i == 0 || i == cellRows - 1))
    //        width = (short)RandIntMinMax(3, 6);

    //    float cellSize = widthSize / width;
    //    float widthOffset = originPos.x - widthSize / 2;
    //    widthOffset += cellSize / 2;

    //    nodeList.push_back(vector<Node>());

    //    // Generate X nodes
    //    for (short j = 0; j < width; j++)
    //    {
    //        Node node = Node();
    //        float randomness = 8;

    //        float offsetX = RandFloatMinMax(-cellSize / 5, cellSize / 5);
    //        float offsetY = RandFloatMinMax(-cellSize / 5, cellSize / 5);
    //        node.pos = Vector2(j + widthOffset + offsetX, i * cellHeight + originPos.y + offsetY);

    //        widthOffset += cellSize;

    //        nodeList[i].push_back(node);
    //    }
    //}

    //// Assigning the connection via random
    //for (int i = 0; i < nodeList.size(); ++i)
    //{
    //    if (i == 0) {
    //        for (int q = 0; q < nodeList[(size_t)i+1].size(); ++q)
    //        {
    //            nodeList[0][0].connectedNodes.push_back(&nodeList[1][q]);
    //        }
    //    }
    //    else if (i == nodeList.size() - 2)
    //    {
    //        // If 2nd last row
    //        for (int j = 0; j < nodeList[i].size(); ++j)
    //        {
    //            nodeList[i][j].connectedNodes.push_back(&nodeList[(size_t)nodeList.size() - 1][0]);
    //        }
    //    }
    //    // Assign using function
    //    else if (i < nodeList.size() - 1)
    //    {
    //        AssignLines(&nodeList[i], &nodeList[(size_t)i + 1]);
    //    }
//    }
}
//
//void _mapData::AssignLines(vector<Node>* firstList, vector<Node>* secondList)
//{
//    
//    int minconn = firstList->size() > secondList->size() ? (int)firstList->size() : (int)secondList->size();
//    vector<Connection> ConnectionList;
//
//    for (int i = 0; i < firstList->size(); ++i)
//    {
//        // If first position of layer
//        if (i == 0)
//        {
//            Connection c1;
//            c1.point1 = (*firstList)[i].pos;
//            c1.point2 = (*secondList)[0].pos;
//            ConnectionList.push_back(c1);
//
//            (*firstList)[i].connectedNodes.push_back(&(*secondList)[0]);
//            (*secondList)[0].connectedFrom.push_back(&(*firstList)[i]);
//
//            if (RandIntMinMax(0, 3) == 0 && (*secondList).size() > 1)
//            {
//                (*firstList)[i].connectedNodes.push_back(&(*secondList)[1]);
//                (*secondList)[1].connectedFrom.push_back(&(*firstList)[i]);
//                Connection c2;
//                c2.point1 = (*firstList)[i].pos;
//                c2.point2 = (*secondList)[0].pos;
//                ConnectionList.push_back(c2);
//            }
//        }
//        //If not last position of layer
//        else if (i != firstList->size() - 1)
//        {
//            int z = 0;
//
//            float currentpos = ((float)i + 1) / firstList->size();
//            for (; z < secondList->size(); ++z) {
//                if (currentpos <= (((float)z + 1) / secondList->size())) {
//                    break;
//                }
//            }
//            // z is now default target node
//
//            if (z < 2) {
//                z = 0;
//            }
//            else {
//                z -= 2;
//            }
//
//            for (int k = 0; k < 3; k++) {
//                Connection c1;
//                c1.point1 = (*firstList)[i].pos;
//                c1.point2 = (*secondList)[z].pos;
//                float chance;
//                switch (k) {
//                    case 0:
//                        chance = 1.0f;
//                        break;
//                    case 1:
//                        chance = 1.0f;
//                        break;
//                    case 2:
//                        chance = 1.0f;
//                        break;
//                    default:
//                        chance = 0.0f;
//                }
//
//                if (i > 0) {
//                    int hascollided = 0;
//                    /*Vector2 distVector = c1.point1 - c1.point2;
//                    float divfloat = 2.31f;
//                    bool isSmaller = distVector.LengthSquared() <= (AEGetWindowHeight() / divfloat) * (AEGetWindowHeight() / divfloat);
//
//                    cout << isSmaller << endl;*/
//
//                    
//
//                    
//                    
//                    for (int p = 0; p < i; p++) {
//                        
//                        
//                        if ((*firstList)[p].connectedNodes.size() < 1) {
//                            break;
//                        }
//                        for (int q = 0; q < (*firstList)[p].connectedNodes.size(); q++) {
//
//                           /* cout << endl;
//                            cout << "Checking if collision happened between line " << q << " of node " << p << ", and line " << k << " of node " << i << "...\n";*/
//                            if (CollideLines(c1.point1, c1.point2, (*firstList)[p].pos, (*firstList)[p].connectedNodes[q]->pos))
//                            {
//                                hascollided = 1;
//                                //cout << "Some collision happened between line " << q << " of node " << p << ", and line " << k << " of node \n" << i;
//
//                                if (q != (*firstList)[p].connectedNodes.size() - 1) {
//                                    //cout << "Thus, Line not added.\n";
//                                    break;
//                                }
//                                else {
//                                    //
//                                    //if (RandIntMinMax(0, 1) == 0) {
//                                    //    cout << "Thus, Line not added.\n";
//                                    //    break;
//                                    //}
//                                    //else {
//                                    //    cout << "Thus, Line not added.\n";
//                                    //    int x = q;
//                                    //    while (x != (*firstList)[p].connectedNodes.size() - 1){
//                                    //        (*firstList)[p].connectedNodes.erase((*firstList)[p].connectedNodes.begin() + x);
//                                    //        x++;
//                                    //    }
//
//                                    //    break;
//                                    //}
//                                    //
//                                    int x = q;
//                                    while (x != (*firstList)[p].connectedNodes.size() - 1) {
//                                        (*firstList)[p].connectedNodes.erase((*firstList)[p].connectedNodes.begin() + x);
//                                        x++;
//                                    }
//                                }
//                            }
//                        }
//                    }
//                    if (!hascollided) {
//                        //cout << "\nNew Line added, no collision detected\n";
//                       
//                        if ((*secondList)[z].connectedFrom.size() >0) {
//                            chance == 0.1;
//                        }
//                        
//                        if (RandFloatMinMax(0, 1) < chance) {
//                            (*firstList)[i].connectedNodes.push_back(&(*secondList)[z]);
//                            (*secondList)[z].connectedFrom.push_back(&(*firstList)[i]);
//
//                        }
//                        
//                    }
//                }
//                z++;
//            }
//        }
//        // If last position of layer
//        else
//        {
//            if (RandIntMinMax(0, 3) == 0 && (*secondList).size() > 1)
//            {
//                Connection c2;
//                c2.point1 = (*firstList)[i].pos;
//                c2.point2 = (*secondList)[(size_t)secondList->size() - 2].pos;
//                ConnectionList.push_back(c2);
//                (*firstList)[i].connectedNodes.push_back(&(*secondList)[(size_t)secondList->size() - 2]);
//                (*secondList)[(size_t)secondList->size() - 2].connectedFrom.push_back(&(*firstList)[i]);
//
//
//                if (i > 0) {
//                    for (int p = 0; p < i; p++) {
//                        if ((*firstList)[p].connectedNodes.size() < 1) {
//                            break;
//                        }
//                        if (CollideLines(c2.point1, c2.point2, (*firstList)[p].pos, (*firstList)[p].connectedNodes[(*firstList)[p].connectedNodes.size() - 1]->pos))
//                        {
//
//                            if (i - p > 1) {
//                                //cout << "Collided on far left20\n";
//                                ConnectionList.pop_back();
//                                (*firstList)[i].connectedNodes.pop_back();
//                                //cout << "popback successful for far left20!";
//                                break;
//
//                            }
//                            else {
//                                //cout << "Collided on left2\n";
//                                if (RandIntMinMax(0, 1) == 0) {
//                                    ConnectionList.pop_back();
//                                    (*firstList)[i].connectedNodes.pop_back();
//                                    //cout << "popback successful for left21!";
//                                    break;
//                                }
//                                else {
//                                    ConnectionList.erase(ConnectionList.end() - 1);
//                                    (*firstList)[p].connectedNodes.pop_back();
//                                    //cout << "popback successful for left22!";
//                                    break;
//                                }
//
//                            }
//                        }
//                    }
//                }
//            }
//            //Add last connection to the end
//            Connection c1;
//            c1.point1 = (*firstList)[i].pos;
//            c1.point2 = (*secondList)[(size_t)secondList->size() - 1].pos;
//            ConnectionList.push_back(c1);
//            (*firstList)[i].connectedNodes.push_back(&(*secondList)[(size_t)secondList->size() - 1]);
//            (*secondList)[(size_t)secondList->size() - 1].connectedFrom.push_back(&(*firstList)[i]);
//        }
//    }
//
//    bool redoCheck = true;
//
//    for (int i = 0; i < firstList->size(); ++i)
//    {
//        if ((*firstList)[i].connectedNodes.size() == 0) {
//            firstList->erase(firstList->begin() + i);
//        }
//    }
//    
//    for (int i = 0; i < secondList->size(); ++i) {
//        if ((*secondList)[i].connectedFrom.size() == 0) {
//            secondList->erase(secondList->begin() + i);
//        }
//    }
//}
//
//bool _mapData::CollideLines(Vector2 a, Vector2 b, Vector2 c, Vector2 d) {
//    //Line-Line collision
//    float denominator = ((b.x - a.x) * (d.y - c.y)) - ((b.y - a.y) * (d.x - c.x));
//    float numerator1 = ((a.y - c.y) * (d.x - c.x)) - ((a.x - c.x) * (d.y - c.y));
//    float numerator2 = ((a.y - c.y) * (b.x - a.x)) - ((a.x - c.x) * (b.y - a.y));
//
//    // Detect coincident lines (has a problem, read below)
//    if (denominator == 0) return numerator1 == 0 && numerator2 == 0;
//
//    float r = numerator1 / denominator;
//    float s = numerator2 / denominator;
//
//    return (r >= 0.01 && r <= 0.99) && (s >= 0.01 && s <= 0.99);
//}


void _mapData::GenerateMapObject(void)
{
    if (nodeList.size() > 0)
    {
        currentNode = nodeList[0];
        exitNode = nodeList[0];
    }
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

        switch (RandIntMinMax(0,3))
        {
        case 0:
            tempRenderer->SetTexture("UI/Encounter.png");
            nodeList[i]->nodeType = NodeType::Encounter;
            break;
        case 1:
            tempRenderer->SetTexture("UI/Enemy.png");
            nodeList[i]->nodeType = NodeType::Enemy;
            temp->AddComponent<UI_EnemyNodeBox>();
            temp->GetComponent<UI_EnemyNodeBox>()->CreateEnemyNode(temp, 3, 10);
            break;
        case 2:
            tempRenderer->SetTexture("UI/Elite.png");
            nodeList[i]->nodeType = NodeType::Elite;
            temp->AddComponent<UI_EnemyNodeBox>();
            temp->GetComponent<UI_EnemyNodeBox>()->CreateEnemyNode(temp, 3, 10);
            break;
        case 3:
            tempRenderer->SetTexture("Steven.jpg");
            nodeList[i]->nodeType = NodeType::Shop;
            break;
        case 4:
            tempRenderer->SetTexture("UI/Rest.png");
            nodeList[i]->nodeType = NodeType::Rest;
            break;
        default:
            tempRenderer->SetTexture("Steven.jpg");
            nodeList[i]->nodeType = NodeType::Nothing;
            break;
        }

        temp->transform->worldposition = Vector2(nodeList[i]->pos);
        nodeList[i]->nodeObject = temp;

        // Get current node and exit node
        currentNode = (nodeList[i]->pos.x < (*currentNode).pos.x) ? nodeList[i] : currentNode;
        exitNode = (nodeList[i]->pos.x > (*exitNode).pos.x) ? nodeList[i] : exitNode;
    }
}

void _mapData::ClearList(void)
{
    nodeList.clear();
}

void _mapData::DisplayNodeRoutes(float travelDistance)
{
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

void _mapData::DisplayBossNode(void)
{
    exitNode->nodeObject->GetComponent<SpriteRenderer>()->SetTexture("UI/boss.png");
    exitNode->nodeType = NodeType::Boss;
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
            encounterUI = new GameObject();
            encounterUI->AddComponent<UI_EncounterBox>();
            encounterUI->GetComponent<UI_EncounterBox>()->CreateEncounter(Vector2(0, 0), 3, "aed");
            break;
        case NodeType::Enemy:
            SceneManager.LoadScene(new Scene_Battle, TransitionType::FadeToBlack, true);
            break;
        case NodeType::Elite:
            SceneManager.LoadScene(new Scene_Battle, TransitionType::FadeToBlack, true);
            break;
        case NodeType::Boss:
            SceneManager.LoadScene(new Scene_Battle, TransitionType::FadeToBlack, true);
            break;
        case NodeType::Shop:
            SetClickable(false);
            SetHoverable(false);
            shopUI = new GameObject();
            shopUI->AddComponent<UI_Shop>();;
            shopUI->GetComponent<UI_Shop>()->CreateShop(3, artifacts, stats);
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
