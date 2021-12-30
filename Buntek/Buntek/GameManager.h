#pragma once
#include <string>
using namespace std;

#define GameManager _gameManager::Instance()

class _gameManager
{
private:
    static _gameManager* instance;
    _gameManager();
    ~_gameManager();

public:
    static _gameManager& Instance(void);

};

class Skill
{
private:
    

public:
    int id;
    string description;
};
