/*!*****************************************************************************
\file ECSManager.h
\author: Algene Tan Chuan Hong (90%)
\co-authors: Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles ECSManager
*******************************************************************************/
#include <vector>
#include "Component.h"
#pragma once

#define ECSManager _ECSManager::Instance()

class _ECSManager
{
private:
    _ECSManager(void);
    ~_ECSManager(void);
    vector<GameObject*> GOList;
    vector<Component*> componentList;

public:
    static _ECSManager& Instance(void);
    void AddGameObjectToList(GameObject* GO);
    void AddComponentToList(Component* component);
    void UpdateList(void);
    void Free(void);
};