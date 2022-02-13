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