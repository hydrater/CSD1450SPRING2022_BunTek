#include "GameManager.h"
#include "System.h"
#include "SpriteRenderer.h"
#include "Scene_Navigation.h"

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

void _gameManager::InitBattle(double _playerHp, double _enemyHp)
{
    playerHp = _playerHp;
    enemyHp = _enemyHp;
}

void _gameManager::DealDamage(double damage, bool isPlayer)
{
    if (isPlayer)
    {
        playerHp -= damage;
        if (playerHp <= 0)
        {
            SceneManager.LoadScene(new Scene_Navigation, TransitionType::FadeToBlack);
        }
    }
    else
    {
        enemyHp -= damage;
        if (enemyHp <= 0)
        {
            SceneManager.LoadScene(new Scene_Navigation, TransitionType::FadeToBlack);
        }
    }

    cout << "player hp: " << playerHp << " enemy hp: " << enemyHp << endl;
}

void Artifact::SpawnSkillObject(void)
{

}
