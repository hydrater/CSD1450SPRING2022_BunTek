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
    transitionTimer = 0;
    notStarted = true;
    notAwake = true;
    transitioning = true;
    transitionInDone = false;
    transitionDone = false;
    transitionMesh = 0;
    transitionTransparency = 0;

    AEGfxMeshStart();

    AEGfxTriAdd(
        -2160.0f, -3840.0f, 0x00FF00FF, 0.0f, 1.0f,
        2160.0f, -3840.0f, 0x00FFFF00, 1.0f, 1.0f,
        -2160.0f, 3840.0f, 0x0000FFFF, 0.0f, 0.0f);

    AEGfxTriAdd(
        2160.0f, -3840.0f, 0x00FFFFFF, 1.0f, 1.0f,
        2160.0f, 3840.0f, 0x00FFFFFF, 1.0f, 0.0f,
        -2160.0f, 3840.0f, 0x00FFFFFF, 0.0f, 0.0f);

    transitionMesh = AEGfxMeshEnd();
}

_sceneManager::~_sceneManager()
{
    AEGfxMeshFree(transitionMesh);
}

void _sceneManager::LoadScene(Scene* newScene, TransitionTypes TransitionType)
{
    if (scene != NULL)
        nextScene = newScene;
    else
        scene = newScene;
    notStarted = true;
    GameManager.cameraLerpBack = false;
    currentTransitionTypes = TransitionType;
    transitioning = true;
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
    if (transitionTimer != 0 || transitionInDone) {
        AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
        AEGfxSetPosition(0.0f, 0.0f);
        AEGfxSetTintColor(0, 0, 0, transitionTransparency);
        AEGfxTextureSet(AssetManager.GetTexture("WhiteTexture.png"), 0, 0);
        AEGfxMeshDraw(transitionMesh, AE_GFX_MDM_TRIANGLES);
    }
    scene->LateUpdate();
}

void _sceneManager::EarlyUpdate(void)
{
    scene->EarlyUpdate();
}
void _sceneManager::FadeToBlack(void) {
    if (!transitionInDone) {
        transitionTimer += DeltaTime;
        transitionTransparency = lerpF(0, 1, easeIn(transitionTimer / transitionStageDuration));
        if (transitionTimer > transitionStageDuration) {
            transitionTimer = 0;
            transitionInDone = true;
            transitionTransparency = 1;
        }
    }
    else if(!transitionDone)
    {
        transitionTransparency = 1;
        transitionTimer += DeltaTime;
        if (transitionTimer > transitionDuration) {
            if (scene != NULL && nextScene != NULL)
            {
                AssetManager.FreeAll();
                GameScriptManager.ClearList();
                delete scene;
                AEGfxSetCamPosition(0, 0);
                scene = nextScene;
                nextScene = 0;
            }
            if (notStarted)
            {
                scene->Start();
                notStarted = false;
            }
            transitionTimer = 0;
            transitionDone = true;
        }
    }
    else {
        transitionTimer += DeltaTime;
        transitionTransparency = (lerpF(1, 0, easeIn(transitionTimer / transitionStageDuration)));
        if (transitionTimer > transitionStageDuration) {
            transitionTimer = 0;
            transitionTransparency = 0;
            transitioning = false;
            transitionInDone = false;
            transitionDone = false;
        }
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

        if (!gameScriptList[i]->IsActive() || !gameScriptList[i]->Owner()->IsActive())
            continue;

        if (!gameScriptList[i]->getStarted())
        {
            gameScriptList[i]->Start();
            gameScriptList[i]->setStarted(true);
        }

        gameScriptList[i]->Update();
    }
}

void _gameScriptManager::ClearList(void)
{
    gameScriptList.clear();
}

