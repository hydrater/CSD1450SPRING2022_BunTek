#include "System.h"

_eventManager* _eventManager::instance = 0;
_sceneManager* _sceneManager::instance = 0;

_eventManager& _eventManager::Instance(void)
{
    if (instance != 0)
    {
        return *instance;
    }
    instance = new _eventManager();
    return *instance;
}

_eventManager::_eventManager()
{

}

_eventManager::~_eventManager()
{

}

void _eventManager::Test(void)
{
    cout << "lmao" << endl;;
}

void Scene::Awake(void)
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
}

_sceneManager::~_sceneManager()
{

}

void _sceneManager::LoadScene(Scene* newScene)
{
    scene = newScene;
}

Scene* _sceneManager::GetScene(void)
{
    return scene;
}

void GameObject::Instantiate(void)
{

}

void GameObject::Update(void)
{
    cout << "test" << endl;
}
