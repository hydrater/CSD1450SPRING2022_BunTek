#include "ECSManager.h"
#include "System.h"
#include <iostream>
using namespace std;

_ECSManager::_ECSManager(void)
{
}

_ECSManager::~_ECSManager(void)
{
    /*for (int i = (int)componentList.size() - 1; i >= 0; --i)
        delete componentList[i];*/
}

_ECSManager& _ECSManager::Instance(void)
{
    static _ECSManager instance;
    return instance;
}

void _ECSManager::AddGameObjectToList(GameObject* GO)
{
    GOList.push_back(GO);
}

void _ECSManager::AddComponentToList(Component* component)
{
    componentList.push_back(component);
}

void _ECSManager::UpdateList(void)
{
    for  (unsigned i = 0; i < componentList.size(); ++i)
    {
        if (componentList[i] == NULL)
            continue;

        if (componentList[i]->remove)
        {
            GameScriptManager.ForceDelete(componentList[i]);
            delete componentList[i];
            componentList[i] = NULL;
        }
    }
    // Clean up null components
    for (int i = (int)componentList.size() -1; i >= 0; --i)
    {
        if (componentList[i] == NULL)
            componentList.erase(componentList.begin() + i);
    }

    // For GO
    for (unsigned i = 0; i < GOList.size(); ++i)
    {
        if (GOList[i] == NULL)
            continue;

        if (GOList[i]->remove)
        {
            delete GOList[i];
            GOList[i] = NULL;
        }
    }

    // Clean up GO
    for (int i = (int)GOList.size() - 1; i >= 0; --i)
    {
        if (GOList[i] == NULL)
            GOList.erase(GOList.begin() + i);
    }
}

void _ECSManager::Free(void)
{
    for (int i = 0; i < componentList.size(); ++i)
        delete componentList[i];

    componentList.clear();

    for (int i = 0; i < GOList.size(); ++i)
        delete GOList[i];

    GOList.clear();
}
