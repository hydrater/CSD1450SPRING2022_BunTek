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
    float widthSize = 1600;

    cout << originPos.x << endl;

    for (int i = 0; i < 10; i++)
    {
        short width = 1;
        if (!(i == 0 || i == 9))
            width = (short)RandIntMinMax(2, 6);

        float cellSize = widthSize / width;
        float widthOffset = originPos.x - widthSize / 2;
        widthOffset += cellSize / 2;

        nodeList.push_back(vector<Node>());
        if (i > 0)
        {
            int previousRowSize = nodeList[(size_t)i-1].size();
            int minimumLinksPerNode = width / previousRowSize;
            int extraNodes = width % previousRowSize;
        }

        for (short j = 0; j < width; j++)
        {
            Node node = Node();

            GameObject* temp = new GameObject;
            SpriteRenderer* tempRenderer = temp->AddComponent<SpriteRenderer>();
            tempRenderer->Size(50, 50);
            tempRenderer->SetTexture("Steven.jpg");

            float offsetX = RandFloatMinMax(-cellSize / 3, cellSize / 3);
            float offsetY = RandFloatMinMax(-100, 100);

            temp->transform->worldposition = Vector2(j + widthOffset + offsetX, i * 300 + originPos.y + offsetY);

            node.clickable = temp;
            //node.connectedNodes

            widthOffset += cellSize;

            // Should maybe store a pointer
            nodeList[i].push_back(node);
        }
    }
}

void _mapData::GenerateMapObject(void)
{
    for (int i = 0; i < nodeList.size(); ++i)
    {
        for (int j = 0; j < nodeList[i].size(); ++j)
        {
            
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
