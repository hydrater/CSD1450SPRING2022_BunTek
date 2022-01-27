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

void _saveManager::ArtifactListToHashtable(void)
{
    artifactSaveData.clear();

    for (int i = 0; i < artifactInventory.behaviorList_Reflect.size(); ++i)
    {
        artifactSaveData.insert(pair<unsigned long, int>(artifactInventory.behaviorList_Reflect[i].ID, artifactInventory.behaviorList_Reflect[i].count));
    }

    for (int i = 0; i < artifactInventory.behaviorList_DealDamage.size(); ++i)
    {
        artifactSaveData.insert(pair<unsigned long, int>(artifactInventory.behaviorList_DealDamage[i].ID, artifactInventory.behaviorList_DealDamage[i].count));
    }

    for (int i = 0; i < artifactInventory.behaviorList_TakeDamage.size(); ++i)
    {
        artifactSaveData.insert(pair<unsigned long, int>(artifactInventory.behaviorList_TakeDamage[i].ID, artifactInventory.behaviorList_TakeDamage[i].count));
    }
}

void _saveManager::HashtableToArtifactList(void)
{
    // Switch based on event type
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
    ArtifactListToHashtable();

    _size = artifactSaveData.size();

    int i = 0;
    for (map<unsigned long, int>::iterator it = artifactSaveData.begin(); it != artifactSaveData.end(); ++it)
    {
        _key[i] = it->first;
        _value[i] = it->second;
        ++i;
    }

    ofstream wf("./Save/sav.dat", ios::out | ios::binary);
    if (!wf)
    {
        cout << "Cannot open file!" << endl;
        return;
    }
    wf.write((char*)&profile, sizeof(_gameManager::Profile));
    wf.write((char*)&_size, sizeof(_size));
    wf.write((char*)&_key, sizeof(_key));
    wf.write((char*)&_value, sizeof(_value));
    wf.close();
    if (!wf.good())
    {
        cout << "Error occurred at writing time!" << endl;
        return;
    }
}

void _saveManager::LoadData(void)
{
    ifstream rf("./Save/sav.dat", ios::out | ios::binary);
	if (!rf)
    {
		cout << "Cannot open file!" << endl;
		return;
	}
    rf.read((char*)&profile, sizeof(_gameManager::Profile));
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

    HashtableToArtifactList();
}
