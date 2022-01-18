#include "SaveManager.h"
#include <fstream>
#include <iostream>

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
    profile.health = 0;
    profile.damage = 0;
    profile.paddleSpeed = 0;
    profile.ballSpeed = 0;
    profile.ballSpawnFreq = 0;
    profile.hp = 0;
    profile.mapSize = 0;
    profile.stardust = 0;

    ofstream wf("./Save/sav.dat", ios::out | ios::binary);
    if (!wf) {
        cout << "Cannot open file!" << endl;
        return;
    }
    wf.write((char*)&profile, sizeof(Profile));
    wf.write((char*)&_size, sizeof(_size));
    wf.write((char*)&_stringSize, sizeof(_stringSize));
    wf.write((char*)&_count, sizeof(_count));

    wf.close();
    if (!wf.good()) {
        cout << "Error occurred at writing time!" << endl;
        return;
    }
}

void _saveManager::LoadData(void)
{
    ifstream rf("./Save/sav.dat", ios::out | ios::binary);
    if (!rf) {
        cout << "Cannot open file!" << endl;
        return;
    }
    rf.read((char*)&profile, sizeof(Profile));
    rf.read((char*)&_size, sizeof(_size));
    rf.read((char*)&_stringSize, sizeof(_stringSize));
    rf.read((char*)&_count, sizeof(_count));
    rf.close();
    if (!rf.good()) {
        cout << "Error occurred at reading time!" << endl;
        return;
    }
}
