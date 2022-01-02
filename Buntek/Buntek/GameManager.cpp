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

void _gameManager::CameraUpdate(void)
{
    if (cameraShakeTime > 0)
    {
        float dt = DeltaTime;
        float test = RandFloatMinMax(0, 3);

        shakeOffset -= cameraDecline;
        // For random, comment out the switch
        //pos = Vector2(RandFloatMinMax(-shakeOffset, shakeOffset), RandFloatMinMax(-shakeOffset, shakeOffset));
        shakeIntervalTimer -= dt;

        if (shakeIntervalTimer < 0)
        {
            switch (cameraShakeState)
            {
            case 0: // top left
                pos.x = -shakeOffset;
                pos.y = -shakeOffset;
                break;
            case 1: // bottom right
                pos.x = shakeOffset;
                pos.y = shakeOffset;
                break;
            case 2: // top right
                pos.x = shakeOffset;
                pos.y = -shakeOffset;
                break;
            case 3: // bottom left
                pos.x = -shakeOffset;
                pos.y = shakeOffset;
                break;
            }

            /*float test = 4;
            pos.x += RandFloatMinMax(-test, test);
			pos.y += RandFloatMinMax(-test, test);*/

            AEGfxSetCamPosition(pos.x, pos.y);
            cameraShakeState += cameraShakeState < 3 ? 1 : -3;
            shakeIntervalTimer = shakeInterval;
        }
        cameraShakeTime -= dt;
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

void _gameManager::CameraShake(float period, float cameraStrength, Vector2 direction)
{
    dir = direction;
    shakeOffset = cameraStrength;
    cameraDecline = cameraStrength / period * DeltaTime;
    cameraShakeTime = period;
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
