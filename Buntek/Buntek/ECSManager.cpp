/*!*****************************************************************************
\file ECSManager.cpp
\project Beyond Aurorean Skies
\author: Algene Tan Chuan Hong (90%)
\co-authors: Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles ECSManager
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/

#include "ECSManager.h"
#include "System.h"
#include <iostream>
using namespace std;

_ECSManager::_ECSManager(void)
{
}

_ECSManager::~_ECSManager(void)
{
    
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
            GameScriptManager.AddToPredelete(componentList[i]);
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
