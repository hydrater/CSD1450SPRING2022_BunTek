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
    void SpawnSkillObject(void);
    int id;
    string description;
    enum RarityTypes
    {
        common,
        Rare,
        Epic,
        Legendary
    };
    RarityTypes rarity;
};

class _gameManager
{
private:
    static _gameManager* instance;
    _gameManager();
    ~_gameManager();
    float cameraShakeTime = 0, shakeIntervalTimer= 0, shakeOffset = 0, cameraDecline = 0;
    char cameraShakeState = 0;
    Vector2 pos = Vector2(0, 0);
    const float shakeInterval = 0.05f;

public:
    static _gameManager& Instance(void);
    Skill skill1, skill2, skill3;
    void CameraUpdate(void);
    void CameraShake(float period, float cameraStrength);
};

class MapData
{
public:
    class Node
    {
    public:
        int row, height;
        Vector2 pos;
    };
    void GenerateList(void);

private:
    vector<Node> nodeList;
};
