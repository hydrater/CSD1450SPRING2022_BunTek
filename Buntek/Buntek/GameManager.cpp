/*!*****************************************************************************
\file GameManager.cpp
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Manages the Game
*******************************************************************************/

#include "GameManager.h"
#include "System.h"
#include "SpriteRenderer.h"
#include "Scene_Navigation.h"
#include "SaveManager.h"
#include "MapGenerator.h"
#include "UI_DialogueHandler.h"
#include "Scene_MainMenu.h"
#include "Scene_Battle.h"
#include "AudioEngine.h"
#include "UI_Menu.h"

using namespace Math;

_gameManager::_gameManager()
{

}

_gameManager::~_gameManager()
{

}

_gameManager& _gameManager::Instance(void)
{
    static _gameManager instance;
    return instance;
}

Vector2 _gameManager::GetCursorPosition(void)
{
    s32 x, y;
    AEInputGetCursorPosition(&x, &y);
    return Vector2((float)x - (float)AEGetWindowWidth() / 2, -((float)y - (float)AEGetWindowHeight() / 2));
}

void _gameManager::InitBattleProfile(BattleArtifactProfile& battleProfile, map<unsigned long, int> artifactSaveData)
{
    battleProfile = BattleArtifactProfile();
    for (map<unsigned long, int>::iterator it = artifactSaveData.begin(); it != artifactSaveData.end(); ++it)
    {
        Artifact newArtifact;
        newArtifact.ID = it->first;
        newArtifact.count = it->second;

        unsigned long idType = it->first / 100;

        switch (idType)
        {
        case 0:
            battleProfile.behaviorList_Passive.push_back(newArtifact);
            break;

        case 2:
            battleProfile.behaviorList_WallBounce.push_back(newArtifact);
            break;

        case 3:
            battleProfile.behaviorList_PaddleHit.push_back(newArtifact);
            break;

        case 4:
            battleProfile.behaviorList_DealDamage.push_back(newArtifact);
            break;

        case 5:
            battleProfile.behaviorList_TakeDamage.push_back(newArtifact);
            break;

        case 6:
            battleProfile.behaviorList_BallOnBallCollision.push_back(newArtifact);
            break;

        default:
            break;
        }
    }
}

map<unsigned long, int> _gameManager::GenerateArtifactList(int maxAmtOfArtifacts)
{
    map<unsigned long, int> EnemyArtifactData;

    for (size_t i = 0; i < maxAmtOfArtifacts; ++i)
    {
        unsigned long id = ArtifactDatabase.DrawArtifact();
        map<unsigned long, int>::iterator it;

        it = EnemyArtifactData.find(id);
        if (it != EnemyArtifactData.end())
            it->second++;
        else
            EnemyArtifactData[id] = 1;
    }

    return EnemyArtifactData;
}

void _gameManager::Update(void)
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

    // Artifact List
    if (AEInputCheckTriggered(AEVK_I))
    {
        DisplayArtifactList();
    }

    // pause
    if (!optionMenuOpen && AEInputCheckTriggered(AEVK_ESCAPE))
    {
        DisplayPauseMenu();
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

void _gameManager::CameraEndShake(void)
{
    cameraShakeTime = 0;
    cameraLerpBack = false;
}

void _gameManager::DisplayArtifactList(void)
{
    if (artifactListUI)
    {
        artifactListUI->Delete();
        artifactListUI = NULL;
    }
    else
    {
        artifactListUI = devTools.CreateSpriteGameObject("WhiteTexture.png", 1920, 1080, AE_GFX_BM_BLEND, Vector2(0, 0), 9, 0.2f);
        artifactListUI->GetComponent<SpriteRenderer>()->SetColor(0, 0, 0);

        int x = -780, y = 360;
        for (map<unsigned long, int>::iterator it = SaveManager.artifactSaveData.begin(); it != SaveManager.artifactSaveData.end(); ++it)
        {
            GameObject* newArtifactUI = devTools.CreateArtifactUIGameObject(it->first, Vector2(x, y), 10);
            GameObject* textObj = new GameObject;
            textObj->transform->SetPosition(Vector2(x - 80, y + 50));
            devTools.AddTextToSpriteGameObject(textObj, "GothicA1.ttf", to_string(it->second), TextRenderer::xAlignmentTypes::Mid, TextRenderer::yAlignmentTypes::Mid, 50.f, 12);

            newArtifactUI->AddChild(textObj);
            artifactListUI->AddChild(newArtifactUI);

            x += 310;
            if (x > 800)
            {
                x = -780;
                y -= 340;
            }
        }
    }
}

void _gameManager::StartBattle(short enemyType)
{
    currentEnemy = enemyType;
    SceneManager.LoadScene(new Scene_Battle, TransitionType::FadeTransition, true);
}

void _gameManager::InitBattle(float _playerHp, float _enemyHp)
{
    playerHp = _playerHp;
    enemyHp = _enemyHp;
}

void _gameManager::DealDamage(float damage, bool isPlayer)
{
    if (isPlayer)
    {
        for (size_t i = 0; i < playerArtifactList.statusEffect.size(); ++i)
        {
            if (playerArtifactList.statusEffect[i].statusID == 00) {
                if (playerArtifactList.statusEffect[i].statusTimer > 0) {
                    damage = 0;
                }
                else if (playerArtifactList.statusEffect[i].statusCount > 0) {
                    playerArtifactList.statusEffect[i].statusCount--;
                    damage = 0;;
                }
            }
        }
        playerHp -= damage;
    }
    else
    {
        for (size_t i = 0; i < enemyArtifactList.statusEffect.size(); ++i)
        {
            if (enemyArtifactList.statusEffect[i].statusID == 00) {
                if (enemyArtifactList.statusEffect[i].statusTimer > 0) {
                    damage = 0;;
                }
                else if (enemyArtifactList.statusEffect[i].statusCount > 0) {
                    enemyArtifactList.statusEffect[i].statusCount--;
                    damage = 0;;
                }
            }
        }
        enemyHp -= damage;
    }
}

void _gameManager::HealthCheck(bool isPlayer) {
    if (isPlayer)
    {
        // Player game over
        if (playerHp <= 0 && !battleOver)
        {
            battleOver = true;
            GameManager.playerProfile.hp = GameManager.playerHp;
            GameOver();
        }
    }
    else
    {
        // Enemy game over
        if (enemyHp <= 0 && !battleOver)
        {
            battleOver = true;
            SaveManager.SaveData();
            vector<Artifact> behaviorList_BattleWon;
            for (map<unsigned long, int>::iterator it = SaveManager.artifactSaveData.begin(); it != SaveManager.artifactSaveData.end(); ++it)
            {
                Artifact newArtifact;
                newArtifact.ID = it->first;
                newArtifact.count = it->second;
                unsigned long idType = it->first / 100;
                if (idType == 1) {
                    behaviorList_BattleWon.push_back(newArtifact);
                }
            }
            GameManager.playerProfile.hp = GameManager.playerHp;
            ArtifactDatabase.ApplyArtifactBehavior(behaviorList_BattleWon, true);
            if (currentEnemy == 3)
            {
                ++level;
                MapData.GenerateMapData();
            }
            battleRewardPending = true;
            SceneManager.LoadScene(new Scene_Navigation, TransitionType::FadeTransition, true);
        }
    }
}

short _gameManager::GetEnemyType(void)
{
    return currentEnemy;
}

void _gameManager::PlayRandomBallSound(void)
{
    string ballSound = "Reflect" + to_string(RandIntMinMax(0, 2)) + ".wav";
    AudioManager.PlayClip(ballSound);
}

void _gameManager::GameOver(void)
{
    SaveManager.artifactSaveData.clear();
    SaveManager.DeleteSave();
    MapData.DeleteMapData();
    GameManager.playerProfile = {};
    GameManager.level = 0;
    SceneManager.LoadScene(new Scene_MainMenu , TransitionType::FadeTransition, true);
}

void _gameManager::DisplayOptionMenu(void)
{
    optionMenuOpen = !optionMenuOpen;
    if (optionMenuUI)
    {
        optionMenuUI->Delete();
        
        optionMenuUI = NULL;
    }
    else
    {
        optionMenuUI = new GameObject();
        optionMenuUI->AddComponent<UI_OptionMenu>()->CreateOptionMenu(7);
    }
}
void _gameManager::DisplayPauseMenu(void)
{
    pauseMenuOpen = !pauseMenuOpen;
    if (pauseMenuUI)
    {
        pauseMenuUI->Delete();

        pauseMenuUI = NULL;
    }
    else
    {
        pauseMenuUI = new GameObject();
        pauseMenuUI->AddComponent<UI_PauseMenu>()->CreatePauseMenu(7);
    }
}
void _gameManager::DisplayPauseOptionMenu(void) {
    DisplayOptionMenu();
    DisplayPauseMenu();

}