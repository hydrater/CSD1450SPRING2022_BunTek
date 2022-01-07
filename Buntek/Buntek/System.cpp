#include "System.h"
#include "AssetManager.h"
#include "GameManager.h"

_eventManager* _eventManager::instance = 0;
_sceneManager* _sceneManager::instance = 0;
_gameScriptManager* _gameScriptManager::instance = 0;

_eventManager::_eventManager()
{

}

_eventManager::~_eventManager()
{

}

_eventManager& _eventManager::Instance(void)
{
    if (instance != 0)
    {
        return *instance;
    }
    instance = new _eventManager();
    return *instance;
}

//void _eventManager::Awake(void)
//{
//	/*if (notAwake)
//	{
//		scene->Awake();
//		notAwake = false;
//	}*/
//}
//
//void _eventManager::Start(void)
//{
//
//}
//
//void _eventManager::Update(void)
//{
//    //if (notStarted)
//    //{
//    //    Awake();
//
//    //    scene->Start();
//    //    notStarted = false;
//    //}
//    //scene->Update();
//}

void Scene::Start(void)
{
}

void Scene::EarlyUpdate(void)
{
}

void Scene::Update(void)
{
}

void Scene::LateUpdate(void)
{
}

_sceneManager& _sceneManager::Instance(void)
{
    if (instance != 0)
    {
        return *instance;
    }
    instance = new _sceneManager();
    return *instance;
}

_sceneManager::_sceneManager()
{
    scene = 0;
    nextScene = 0;
    CurrentTransitionTypes = TransitionTypes::None;
    CurrentTransitionStage = TransitionStage::NotTransitioning;
    TransitionTimer = 0;
    TransitionDuration = 2;
    Transitor = 0;
    notStarted = true;
    notAwake = true;
    Transitioning = true;
}

_sceneManager::~_sceneManager()
{

}

void _sceneManager::LoadScene(Scene* newScene, TransitionTypes TransitionType)
{
    //if (scene != NULL)
    //{
    //    AssetManager.FreeAll();
    //    GameScriptManager.ClearList();
    //    delete scene;
    //}
    cout << "load" << endl;
    if (scene != NULL)
        nextScene = newScene;
    else
        scene = newScene;
    notStarted = true;
    CurrentTransitionTypes = TransitionType;
    Transitioning = true;
    GameManager.cameraLerpBack = false;
    AEGfxSetCamPosition(0, 0);
}

Scene* _sceneManager::GetScene(void)
{
    return scene;
}

void _sceneManager::Update(void)
{
    if (Transitioning) {
        switch (CurrentTransitionTypes)
        {
        case TransitionTypes::None:
            if (scene != NULL && nextScene != NULL)
            {
                AssetManager.FreeAll();
                GameScriptManager.ClearList();
                delete scene;
                scene = nextScene;
                nextScene = 0;
            }
            if (notStarted)
            {
                scene->Start();
                notStarted = false;
            }
            Transitioning = false;
            break;
        case TransitionTypes::FadeToBlack:
            FadeToBlack();
            break;
        default:
            break;
        }
    }
    scene->Update();
}

void _sceneManager::LateUpdate(void)
{
    scene->LateUpdate();
}

void _sceneManager::EarlyUpdate(void)
{
    scene->EarlyUpdate();
}
void _sceneManager::FadeToBlack(void) {
    switch (CurrentTransitionStage)
    {
    case TransitionStage::NotTransitioning:
        TransitionTimer = 0;
        Transitor = new GameObject();
        Transitor->AddComponent<SpriteRenderer>()->Size((float)AEGetWindowWidth(), (float)AEGetWindowHeight());
        Transitor->GetComponent<SpriteRenderer>()->SetTexture("BlackTexture.png");
        Transitor->GetComponent<SpriteRenderer>()->SetTransparency(0);
        CurrentTransitionStage = TransitionStage::TransitionTo;
        break;

    case TransitionStage::TransitionTo:
        TransitionTimer += DeltaTime;
        Transitor->GetComponent<SpriteRenderer>()->SetTransparency(lerpF(0,1,easeIn(TransitionTimer/TransitionDuration)));
        if (TransitionTimer > TransitionDuration) {
            TransitionTimer = 0;
            CurrentTransitionStage = TransitionStage::Transitioning;
        }
        break;

    case TransitionStage::Transitioning:
        if (scene != NULL && nextScene != NULL)
        {
            AssetManager.FreeAll();
            GameScriptManager.ClearList();
            delete scene;
            scene = nextScene;
            nextScene = 0;
        }
        if (notStarted)
        {
            scene->Start();
            notStarted = false;
        }
        Transitor = new GameObject();
        Transitor->AddComponent<SpriteRenderer>()->Size((float)AEGetWindowWidth(), (float)AEGetWindowHeight());
        Transitor->GetComponent<SpriteRenderer>()->SetTexture("BlackTexture.png");
        Transitor->GetComponent<SpriteRenderer>()->SetTransparency(1);
        CurrentTransitionStage = TransitionStage::TransitionFrom;
        break;

    case TransitionStage::TransitionFrom:
        TransitionTimer += DeltaTime;
        Transitor->GetComponent<SpriteRenderer>()->SetTransparency(lerpF(1, 0, easeIn(TransitionTimer / TransitionDuration)));
        if (TransitionTimer > TransitionDuration) {
            Transitor->Delete();
            TransitionTimer = 0;
            Transitioning = false;
            CurrentTransitionStage = TransitionStage::NotTransitioning;
        }
        break;

    default:
        break;
    }
}

_gameScriptManager::_gameScriptManager()
{

}

_gameScriptManager::~_gameScriptManager()
{

}

_gameScriptManager& _gameScriptManager::Instance(void)
{
    if (instance != 0)
    {
        return *instance;
    }
    instance = new _gameScriptManager();
    return *instance;
}

void _gameScriptManager::AddToList(GameScript* gameScript)
{
    gameScriptList.push_back(gameScript);
}

void _gameScriptManager::Update(void)
{
    for (int i = 0; i < gameScriptList.size(); ++i)
    {
        if (gameScriptList[i]->remove)
        {
            delete gameScriptList[i];
            gameScriptList.erase(gameScriptList.begin() + i);
            --i;
            continue;
        }

        if (!gameScriptList[i]->getStarted())
        {
            gameScriptList[i]->Start();
            gameScriptList[i]->setStarted(true);
        }

        gameScriptList[i]->Update();
    }
    //cout << gameScriptList.size() << endl;
}

void _gameScriptManager::ClearList(void)
{
    gameScriptList.clear();
}

