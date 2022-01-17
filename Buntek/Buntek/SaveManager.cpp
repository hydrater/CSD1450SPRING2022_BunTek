#include "SaveManager.h"
#include <fstream>
#include <vector>
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
    ofstream wf("./Save/sav.dat", ios::out | ios::binary);
    if (!wf) {
        cout << "Cannot open file!" << endl;
        return;
    }

    wf.write((char*)&profile, sizeof(Profile));
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
    rf.close();
    if (!rf.good()) {
        cout << "Error occurred at reading time!" << endl;
        return;
    }
}
