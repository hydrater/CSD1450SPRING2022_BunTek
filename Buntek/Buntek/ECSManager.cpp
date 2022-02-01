#include "ECSManager.h"
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

void _ECSManager::AddToList(Component* component)
{
    componentList.push_back(component);
}

void _ECSManager::UpdateList(void)
{
    cout << componentList.size() << endl;
}
