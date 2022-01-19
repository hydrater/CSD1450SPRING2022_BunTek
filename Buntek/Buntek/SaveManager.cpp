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
    //profile.health = 0;
    //profile.damage = 0;
    //profile.paddleSpeed = 0;
    //profile.ballSpeed = 0;
    //profile.ballSpawnFreq = 0;
    //profile.hp = 0;
    //profile.mapSize = 0;
    //profile.stardust = 0;

    //_key[0] = 50;
    //_value[0] = 30;
    //_key[1] = 10248;
    //_value[2] = 500;
    //_key[3] = 500000;
    //_value[3] = 340;

    artifactSaveData[200] = 33;
    artifactSaveData[30] = 22;

    _size = artifactSaveData.size();

    int i = 0;
    for (map<unsigned long, int>::iterator it = artifactSaveData.begin(); it != artifactSaveData.end(); ++it)
    {
        _key[i] = it->first;
        _value[i] = it->second;
        ++i;
    }

    ofstream wf("./Save/sav.dat", ios::out | ios::binary);
    if (!wf) {
        cout << "Cannot open file!" << endl;
        return;
    }
    wf.write((char*)&profile, sizeof(Profile));
    wf.write((char*)&_size, sizeof(_size));
    wf.write((char*)&_key, sizeof(_key));
    wf.write((char*)&_value, sizeof(_value));
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
    rf.read((char*)&_key, sizeof(_key));
    rf.read((char*)&_value, sizeof(_value));
    rf.close();
    if (!rf.good()) {
        cout << "Error occurred at reading time!" << endl;
        return;
    }
    for (int i = 0; i < _size; i++)
        artifactSaveData[_key[i]] = _value[i];
}
