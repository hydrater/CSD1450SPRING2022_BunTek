#include "System.h"
#include "Renderer.h"
#include "GameManager.h"

_eventManager* _eventManager::instance = 0;
_sceneManager* _sceneManager::instance = 0;
_gameScriptManager* _gameScriptManager::instance = 0;

_eventManager::_eventManager(void)
{

}

_eventManager::~_eventManager(void)
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

template<typename T>
IEvent<T>::~IEvent()
{
    listeners.clear();
};
template<typename T>
void IEvent<T>::Subscribe(T listener)
{
    listeners.push_back(listener);
};
template<typename T>
bool IEvent<T>::Unsubscribe(T listener)
{
    for (int i = 0; i < listeners.size(); i++)
    {
        if (listeners[i] == listener)
        {
            listeners.erase(listeners.begin() + i);
            return true;
        }
    }

    return false;
};

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
    currentTransitionTypes = TransitionType::None;
    currentTransitionStage = TransitionStage::TransitionStart;
    transitionTimer = 0;
    notStarted = true;
    notAwake = true;
    transitioning = true;
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

_sceneManager::~_sceneManager(void)
{
    AEGfxMeshFree(transitionMesh);
}

void _sceneManager::LoadScene(Scene* newScene, TransitionType TransitionType, bool deleteCurrScene)
{
    if (scene != NULL)
        nextScene = newScene;
    else {
        scene = newScene;
        if (notStarted)
        {
            scene->Start();
            notStarted = false;
        }
    }
    notStarted = true;
    GameManager.cameraLerpBack = false;
    currentTransitionTypes = TransitionType;
    currentTransitionStage = TransitionStage::TransitionStart;
    transitioning = true;
    deleteScene = deleteCurrScene;
}

Scene* _sceneManager::GetScene(void)
{
    return scene;
}

void _sceneManager::Update(void)
{
    scene->Update();
}

void _sceneManager::LateUpdate(void)
{
    scene->LateUpdate();

    if (transitioning) {
        switch (currentTransitionTypes)
        {
        case TransitionType::None:
            if (scene != NULL && nextScene != NULL)
            {
                Renderer.FreeAll();
                GameScriptManager.ClearList();
                if (deleteScene)
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
        case TransitionType::FadeTransition:
            FadeTransition();
            break;
        default:
            break;
        }
    }
}

void _sceneManager::EarlyUpdate(void)
{
    scene->EarlyUpdate();
}
void _sceneManager::FadeTransition(void) {
    switch (currentTransitionStage)
    {
    case TransitionStage::TransitionStart: //fade start
        transitionTimer = 0;
        transitionTransparency = 0;
        currentTransitionStage = TransitionStage::TransitionIn;
        break;
    case TransitionStage::TransitionIn:// fading in
        transitionTimer += DeltaTime;
        transitionTransparency = lerpF(0, 1, easeIn(transitionTimer / transitionStageDuration));
        if (transitionTimer > transitionStageDuration) {
            transitionTimer = 0;
            transitionTransparency = 1;
            currentTransitionStage = TransitionStage::TransitionScene;
        }
        break;
    case TransitionStage::TransitionScene: //fade scene transition
        if (scene != NULL && nextScene != NULL)
        {
            Renderer.FreeAll();
            GameScriptManager.ClearList();
            if (deleteScene)
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
        else { //wait for next frame
            currentTransitionStage = TransitionStage::TransitionOut;
        }
        break;
    case TransitionStage::TransitionOut:// fading out
        transitionTimer += DeltaTime;
        transitionTransparency = 1 - (lerpF(0, 1, easeIn(transitionTimer / transitionStageDuration)));
        if (transitionTimer > transitionStageDuration) {
            transitionTimer = 0;
            transitionTransparency = 0;
            transitioning = false;
            currentTransitionStage = TransitionStage::TransitionStart;
        }
        break;
    }
    //render the fade 
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    AEGfxSetPosition(0.0f, 0.0f);
    AEGfxSetTintColor(0, 0, 0, transitionTransparency);
    AEGfxTextureSet(AssetManager.GetTexture("WhiteTexture.png"), 0, 0);
    AEGfxMeshDraw(transitionMesh, AE_GFX_MDM_TRIANGLES);
}

_gameScriptManager::_gameScriptManager(void)
{

}

_gameScriptManager::~_gameScriptManager(void)
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
    for (size_t i = 0; i < gameScriptList.size(); i++)
        delete gameScriptList[i];

    gameScriptList.clear();
}

