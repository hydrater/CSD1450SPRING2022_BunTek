#include "SaveManager.h"
#include <fstream>
#include <iterator>
#include <vector>

_saveManager* _saveManager::instance = 0;

_saveManager::_saveManager()
{
}

_saveManager::~_saveManager()
{
}

_saveManager& _saveManager::Instance(void)
{
    if (instance != 0)
    {
        return *instance;
    }
    instance = new _saveManager();
    return *instance;
}

void _saveManager::SaveData(void)
{
    Dog dog;

    dog.color = "green";
    dog.barkType = "whaf";
    dog.weight = 30;

    JSON::Value jsonDog = toJson(dog); // produces {"color":"green", "barkType":"whaf", "weight": 30}
    auto dog2 = fromJson<Dog>(jsonDog);

    std::cout << std::boolalpha << (dog == dog2) << std::endl; // pass the test, both dog are equal!
}

void _saveManager::LoadData(void)
{

}
