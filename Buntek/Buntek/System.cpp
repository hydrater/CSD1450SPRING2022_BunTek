#include "System.h"
#include "AssetManager.h"

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

void Scene::Update(void)
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
    notStarted = true;
    notAwake = true;
}

_sceneManager::~_sceneManager()
{

}

void _sceneManager::LoadScene(Scene* newScene)
{
    if (scene != NULL)
    {
        AssetManager.FreeAll();
        delete scene;
    }
    notStarted = true;
    scene = newScene;
}

Scene* _sceneManager::GetScene(void)
{
    return scene;
}

void _sceneManager::Update(void)
{
    if (notStarted)
    {
        scene->Start();
        notStarted = false;
    }
    scene->Update();
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
}
