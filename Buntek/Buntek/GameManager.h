#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Vector2.h"
using namespace std;

#define GameManager _gameManager::Instance()

class Skill
{
private:


public:
    int id;
    string description;
};

class _gameManager
{
private:
    static _gameManager* instance;
    _gameManager();
    ~_gameManager();

public:
    static _gameManager& Instance(void);
    Skill skill1, skill2, skill3;
};

class MapData
{
    class Node
    {
    public:
        int row, height;
        Vector2 pos;
    };

    vector<Node> nodeList;
};
