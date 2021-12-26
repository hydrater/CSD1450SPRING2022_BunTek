#include "System.h"

EventManager* EventManager::instance = 0;
SceneManager* SceneManager::instance = 0;

EventManager& EventManager::Instance(void)
{
    if (instance != 0)
    {
        return *instance;
    }
    instance = new EventManager();
    return *instance;
}

EventManager::EventManager()
{

}

EventManager::~EventManager()
{

}

void EventManager::Test(void)
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

SceneManager& SceneManager::Instance(void)
{
    if (instance != 0)
    {
        return *instance;
    }
    instance = new SceneManager();
    return *instance;
}

SceneManager::SceneManager()
{
    scene = 0;
}

SceneManager::~SceneManager()
{

}

void SceneManager::UpdateScene(Scene* newScene)
{
    scene = newScene;
}

Scene* SceneManager::CurrentScene(void)
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
