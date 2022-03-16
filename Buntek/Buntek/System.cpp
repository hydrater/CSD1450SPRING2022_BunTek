#include "System.h"
#include "Renderer.h"
#include "GameManager.h"
#include "ECSManager.h"

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

bool _sceneManager::ResetScene(void)
{
    if (notStarted)
    {
        scene->Start();
        notStarted = false;
        loadingTimer = loadingTimerDuration;
        GameManager.CameraEndShake();
    }
    return notStarted;
}

_sceneManager& _sceneManager::Instance(void)
{
    static _sceneManager instance;
    return instance;
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
    loadingTimer = loadingTimerDuration;

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
    delete scene;
    AEGfxMeshFree(transitionMesh);
}

void _sceneManager::LoadScene(Scene* newScene, TransitionType TransitionType, bool deleteCurrScene)
{
    if (scene != NULL) {
        nextScene = newScene;
        notStarted = true;
        currentTransitionTypes = TransitionType;
        currentTransitionStage = TransitionStage::TransitionStart;
        transitioning = true;
    }
    else {
        scene = newScene;
        ResetScene();
    }
    deleteScene = deleteCurrScene;
}

Scene* _sceneManager::GetScene(void)
{
    return scene;
}

void _sceneManager::Update(void)
{
    loadingTimer -= DeltaTime;
    if (loadingTimer <= 0)
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
                Renderer.Clear();
                GameScriptManager.Clear();
                ECSManager.Free();
                GameManager.artifactListUI = NULL;
                if (deleteScene)
                    delete scene;
                scene = nextScene;
                nextScene = 0;
            }
            ResetScene();
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
            Renderer.Clear();
            GameScriptManager.Clear();
            ECSManager.Free();
            GameManager.artifactListUI = NULL;
            if (deleteScene)
                delete scene;
            AEGfxSetCamPosition(0, 0);
            scene = nextScene;
            nextScene = 0;
        }
        if (!ResetScene())
        { //wait for next frame
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
    static _gameScriptManager instance;
    return instance;
}

void _gameScriptManager::AddToList(GameScript* gameScript)
{
    gameScriptList.push_back(gameScript);
}

void _gameScriptManager::Update(void)
{
    for (int i = (int)gameScriptList.size() - 1; i >= 0; --i)
    {
        if (gameScriptList[i]->remove || gameScriptList[i] == NULL)
        {
            gameScriptList.erase(gameScriptList.begin() + i);
        }
    }

    for (int i = 0; i < gameScriptList.size(); ++i)
    {
        cout << gameScriptList[i]->ID << endl;
        if (!gameScriptList[i]->IsActive() || (gameScriptList[i]->Owner() != NULL && !gameScriptList[i]->Owner()->IsActive()))
            continue;

        if (!gameScriptList[i]->getStarted())
        {
            gameScriptList[i]->Start();
            gameScriptList[i]->setStarted(true);
        }

        gameScriptList[i]->Update();
        cout << "ended" << endl;
    }
}

void _gameScriptManager::Clear(void)
{
    gameScriptList.clear();
}
