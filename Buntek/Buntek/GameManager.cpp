#include "GameManager.h"
#include "System.h"
#include "SpriteRenderer.h"

using namespace Math;

_gameManager* _gameManager::instance = 0;
_mapData* _mapData::instance = 0;

_gameManager::_gameManager()
{

}

_gameManager::~_gameManager()
{

}

_gameManager& _gameManager::Instance(void)
{
    if (instance != 0)
    {
        return *instance;
    }
    instance = new _gameManager();
    return *instance;
}

Vector2 _gameManager::GetCursorPosition(void)
{
    s32 x, y;
    AEInputGetCursorPosition(&x, &y);
    return Vector2((float)x - (float)AEGetWindowWidth() / 2, -((float)y - (float)AEGetWindowHeight() / 2));
}

void _gameManager::CameraUpdate(void)
{
    if (cameraShakeTime > 0)
    {
        shakeStrength = (Square(maxCameraShakeTime)-(Square(maxCameraShakeTime) - Square(cameraShakeTime)))* maxShakeStrength;

        // Update camera position
        pos += Vector2(RandFloatMinMax(-shakeStrength, shakeStrength), RandFloatMinMax(-shakeStrength, shakeStrength));
        pos = pos.Lerp(Vector2(0, 0), 0.1f);
        AEGfxSetCamPosition(pos.x, pos.y);
        cameraShakeTime -= DeltaTime;
    }
    else
    {
        if (cameraLerpBack)
        {
            pos = pos.Lerp(Vector2(0, 0), 0.1f);
            AEGfxSetCamPosition(pos.x, pos.y);
        }
    }
}

//void _gameManager::CameraUpdate(void)
//{
//    if (cameraShakeTime > 0)
//	{
//		float dt = DeltaTime;
//		float test = RandFloatMinMax(0, 3);
//
//		Vector2 newDir = Vector2(dir.x * shakeOffset, dir.y * shakeOffset);
//
//		shakeOffset -= cameraDecline;
//		// For random, comment out the switch
//		//pos = Vector2(RandFloatMinMax(-shakeOffset, shakeOffset), RandFloatMinMax(-shakeOffset, shakeOffset));
//		shakeIntervalTimer -= dt;
//
//		if (shakeIntervalTimer < 0)
//		{
//			switch (cameraShakeState)
//			{
//			case 0: // top left
//				pos = Vector2(newDir.x, newDir.y);
//				break;
//			case 1: // bottom right
//				pos = Vector2(-newDir.x, -newDir.y);
//			}
//
//			AEGfxSetCamPosition(pos.x, pos.y);
//			cameraShakeState += cameraShakeState < 2 ? 1 : -2;
//			shakeIntervalTimer = shakeInterval;
//		}
//		cameraShakeTime -= dt;
//	}
//	else
//	{
//		pos = Vector2(0, 0);
//		AEGfxSetCamPosition(pos.x, pos.y);
//	}
//}

void _gameManager::CameraShake(float period, float _shakeStrength, Vector2 direction)
{
    dir = direction;
    maxShakeStrength = _shakeStrength;
    shakeStrength = _shakeStrength;
    cameraShakeTime = period;
    maxCameraShakeTime = period;
}

void Skill::SpawnSkillObject(void)
{

}

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
    for (int i = 0; i < cellRows; i++)
    {
        short width = 1;
        if (!(i == 0 || i == cellRows - 1))
            width = (short)RandIntMinMax(2, 6);

        float cellSize = widthSize / width;
        float widthOffset = originPos.x - widthSize / 2;
        widthOffset += cellSize / 2;

        nodeList.push_back(vector<Node>());

        // Generate X nodes
        for (short j = 0; j < width; j++)
        {
            Node node = Node();

            float offsetX = RandFloatMinMax(-cellSize / 5, cellSize / 5);
            float offsetY = RandFloatMinMax(-50, 50);
            node.pos = Vector2(j + widthOffset + offsetX, i * cellHeight + originPos.y + offsetY);

            widthOffset += cellSize;

            nodeList[i].push_back(node);
        }
    }

    // Assigning the connection via random
    for (int i = 0; i < nodeList.size(); ++i)
    {
        if (i == nodeList.size() - 2)
        {
            // If 2nd last row
            for (int j = 0; j < nodeList[i].size(); ++j)
            {
                nodeList[i][j].connectedNodes.push_back(&nodeList[(size_t)nodeList.size() - 1][0]);
            }
        }
        else if (i < nodeList.size() - 1)
        {
            if (nodeList[i].size() > nodeList[(size_t)i + 1].size())
            {
                AssignLines(&nodeList[i], &nodeList[(size_t)i + 1]);
            }
            else
            {
                AssignLines(&nodeList[(size_t)i + 1], &nodeList[i]);
            }
        }
    }
}

void _mapData::AssignLines(vector<Node>* largerList, vector<Node> *smallerList)
{
    for (int i = 0; i < largerList->size(); ++i)
    {
        if (i == 0)
        {
            (*largerList)[i].connectedNodes.push_back(&(*smallerList)[0]);
            if (RandIntMinMax(0, 3) && (*smallerList).size() > 1)
            {
                (*largerList)[i].connectedNodes.push_back(&(*smallerList)[1]);
            }
        }
        else if (i == largerList->size() - 1)
        {
            (*largerList)[i].connectedNodes.push_back(&(*smallerList)[(size_t)smallerList->size()-1]);
            if (RandIntMinMax(0, 3) && (*smallerList).size() > 1)
            {
                (*largerList)[i].connectedNodes.push_back(&(*smallerList)[(size_t)smallerList->size() - 2]);
            }
        }
        else
        {
            if (RandIntMinMax(0, 2))
            {
                (*largerList)[i].connectedNodes.push_back(&(*smallerList)[RandIntMinMax(0, smallerList->size()-1)]);
            }
            else
            {
                (*largerList)[i].connectedNodes.push_back(&(*smallerList)[RandIntMinMax(0, smallerList->size() - 1)]);
                (*largerList)[i].connectedNodes.push_back(&(*smallerList)[RandIntMinMax(0, smallerList->size() - 1)]);
            }
        }
    }
}

void _mapData::GenerateMapObject(void)
{
    for (int i = 0; i < nodeList.size(); ++i)
    {
        for (int j = 0; j < nodeList[i].size(); ++j)
        {
            GameObject* temp = new GameObject;
            SpriteRenderer* tempRenderer = temp->AddComponent<SpriteRenderer>();
            tempRenderer->Size(50, 50);
            tempRenderer->SetTexture("Steven.jpg");

            temp->transform->worldposition = Vector2(nodeList[i][j].pos);

            //node.clickable = temp;
            
            //node.connectedNodes
            for (int k = 0; k < nodeList[i][j].connectedNodes.size(); k++)
            {
                AEGfxVertexList* newLine;
                AEGfxMeshStart();
                AEGfxVertexAdd(nodeList[i][j].pos.x, nodeList[i][j].pos.y, 0xFFFFFFFF, 0.0f, 0.0f);
                AEGfxVertexAdd(nodeList[i][j].connectedNodes[k]->pos.x, nodeList[i][j].connectedNodes[k]->pos.y, 0xFFFFFFFF, 0.0f, 0.0f);
                newLine = AEGfxMeshEnd();
                MapData.connectedLines.push_back(newLine);
            }
        }
    }
}

void _mapData::ClearList(void)
{
    for (int i = 0; i < 10; i++)
    {
        for (short j = 0; j < nodeList[i].size(); j++)
        {
            nodeList[i][j].clickable->Delete();
        }
        nodeList[i].clear();
    }

    nodeList.clear();
}

float _gameManager::easeIn(float t)
{
    return t * t;
}

float _gameManager::flip(float x)
{
    return 1 - x;
}

float _gameManager::easeOut(float t)
{
    float tmp = flip(t);
    return flip(tmp * tmp);
}

float _gameManager::easeInOut(float t)
{
    return lerpF(easeIn(t), easeOut(t), t);
    //t*t*t * (t * (6f*t - 15f) + 10f)
}

float _gameManager::lerpF(float start_value, float end_value, float t)
{
    t = AEClamp(t, 0, 1);
    return start_value + (end_value - start_value) * t;
}
