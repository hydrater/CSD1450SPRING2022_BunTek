#include <vector>
#include "Component.h"
#pragma once

#define ECSManager _ECSManager::Instance()

class _ECSManager
{
private:
    _ECSManager(void);
    ~_ECSManager(void);
    vector<Component*> componentList;

public:
    static _ECSManager& Instance(void);
    void AddToList(Component* component);
    void UpdateList(void);
};