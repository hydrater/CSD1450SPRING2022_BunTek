#include "GameManager.h"
#include "System.h"
using namespace Math;

_gameManager* _gameManager::instance = 0;

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

void _gameManager::CameraShake(float period, float cameraStrength)
{
    shakeOffset = cameraStrength;
    cameraDecline = cameraStrength / period * DeltaTime;
    cameraShakeTime = period;
}

void Skill::SpawnSkillObject(void)
{

}
