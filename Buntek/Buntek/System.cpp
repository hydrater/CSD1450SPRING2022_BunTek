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
    currentTransitionTypes = TransitionTypes::None;
    currentTransitionStage = TransitionStage::NotTransitioning;
    transitionTimer = 0;
    transitionDuration = 2;
    transitionObject = 0;
    notStarted = true;
    notAwake = true;
    transitioning = true;
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
    currentTransitionTypes = TransitionType;
    transitioning = true;
    GameManager.cameraLerpBack = false;
    AEGfxSetCamPosition(0, 0);
}

Scene* _sceneManager::GetScene(void)
{
    return scene;
}

void _sceneManager::Update(void)
{
    if (transitioning) {
        switch (currentTransitionTypes)
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
            transitioning = false;
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
    if (transitionObject != 0) {
        AssetManager.RenderSprite(transitionObject->GetComponent<SpriteRenderer>());
    }
    scene->LateUpdate();
}

void _sceneManager::EarlyUpdate(void)
{
    scene->EarlyUpdate();
}
void _sceneManager::FadeToBlack(void) {
    switch (currentTransitionStage)
    {
    case TransitionStage::NotTransitioning:
        transitionTimer = 0;
        transitionObject = new GameObject();
        transitionObject->AddComponent<SpriteRenderer>()->Size((float)AEGetWindowWidth(), (float)AEGetWindowHeight());
        transitionObject->GetComponent<SpriteRenderer>()->SetTexture("WhiteTexture.png");
        transitionObject->GetComponent<SpriteRenderer>()->SetColor(0, 0, 0);
        transitionObject->GetComponent<SpriteRenderer>()->SetTransparency(0);
        currentTransitionStage = TransitionStage::TransitionTo;
        break;

    case TransitionStage::TransitionTo:
        transitionTimer += DeltaTime;
        transitionObject->GetComponent<SpriteRenderer>()->SetTransparency(lerpF(0,1,easeIn(transitionTimer/transitionDuration)));
        if (transitionTimer > transitionDuration) {
            transitionTimer = 0;
            currentTransitionStage = TransitionStage::Transitioning;
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
            transitionObject = 0;
        }
        if (notStarted)
        {
            scene->Start();
            notStarted = false;
        }
        transitionObject = new GameObject();
        transitionObject->AddComponent<SpriteRenderer>()->Size((float)AEGetWindowWidth(), (float)AEGetWindowHeight());
        transitionObject->GetComponent<SpriteRenderer>()->SetTexture("WhiteTexture.png");
        transitionObject->GetComponent<SpriteRenderer>()->SetColor(0, 0, 0);
        transitionObject->GetComponent<SpriteRenderer>()->SetTransparency(1);
        currentTransitionStage = TransitionStage::TransitionFrom;
        break;

    case TransitionStage::TransitionFrom:
        transitionTimer += DeltaTime;
        transitionObject->GetComponent<SpriteRenderer>()->SetTransparency(lerpF(1, 0, easeIn(transitionTimer / transitionDuration)));
        if (transitionTimer > transitionDuration) {
            transitionObject->Delete();
            transitionObject = 0;
            transitionTimer = 0;
            transitioning = false;
            currentTransitionStage = TransitionStage::NotTransitioning;
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

