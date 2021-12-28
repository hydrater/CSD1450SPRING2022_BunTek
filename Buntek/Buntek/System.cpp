#include "System.h"

_eventManager* _eventManager::instance = 0;
_sceneManager* _sceneManager::instance = 0;

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

void _eventManager::Awake(void)
{
	/*if (notAwake)
	{
		scene->Awake();
		notAwake = false;
	}*/
}

void _eventManager::Start(void)
{

}

void _eventManager::Update(void)
{
    //if (notStarted)
    //{
    //    Awake();

    //    scene->Start();
    //    notStarted = false;
    //}
    //scene->Update();
}

void _eventManager::Render(void)
{

}

void _eventManager::Free(void)
{

}

void Scene::Start(void)
{

}

void Scene::Update(void)
{

}

void Scene::Render(void)
{

}

void Scene::Free(void)
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
        scene->Free();
        cout << "free success" << endl;
    }
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
