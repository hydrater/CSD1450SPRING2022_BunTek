#include "GameManager.h"
#include "System.h"
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
        pos = Vector2(RandFloatMinMax(-shakeStrength, shakeStrength), RandFloatMinMax(-shakeStrength, shakeStrength));

        AEGfxSetCamPosition(pos.x, pos.y);
        cameraShakeTime -= DeltaTime;
    }
    else
    {
        pos = Vector2(0, 0);
        AEGfxSetCamPosition(pos.x, pos.y);
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

void _mapData::GenerateList(void)
{
    for (int i = 0; i < 10; i++)
    {
        short width = (short)RandFloatMinMax(0, 5);
        for (short j = 0; j < width; j++)
        {
            Node node = Node();
            node.column = j;
            node.pos = Vector2(j * 100, i * 100);
            //node.id
            //node.clickable
            //node.connectedNodes
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
