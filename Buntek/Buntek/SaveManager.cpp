#include "SaveManager.h"
#include "MapGenerator.h"
#include <fstream>
#include <iostream>

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
    static _saveManager instance;
    return instance;
}

void _saveManager::SaveData(void)
{
    // Prevent save if there's no map generated yet
    if (MapData.nodeList.size() == 0)
        return;

    ofstream wf("./Save/sav.dat", ios::out | ios::binary);
    if (!wf)
    {
        cout << "Cannot save file!" << endl;
        return;
    }

    // Serializing profile
    wf.write((char*)&profile, sizeof(_gameManager::Profile));

    // Serializing map data
    for (int i = 0; i < MapData.numNodes; ++i)
    {
        wf.write((char*)&MapData.nodeList[i]->pos.x, sizeof(float));
        wf.write((char*)&MapData.nodeList[i]->pos.y, sizeof(float));
        wf.write((char*)&MapData.nodeList[i]->nodeState, sizeof(short));
        wf.write((char*)&MapData.nodeList[i]->nodeType, sizeof(int));
    }
    wf.write((char*)&MapData.currentNode->ID, sizeof(int));

    size_t historySize = MapData.travelHistoryIDs.size();
    wf.write((char*)&historySize, sizeof(size_t));

    for (int selID : MapData.travelHistoryIDs)
        wf.write((char*)&selID, sizeof(int));

    // Serializing artifacts 
    ArtifactListToHashtable();
    _size = (int)artifactSaveData.size();
    int i = 0;
    for (map<unsigned long, int>::iterator it = artifactSaveData.begin(); it != artifactSaveData.end(); ++it)
    {
        _key[i] = it->first;
        _value[i] = it->second;
        ++i;
    }
    wf.write((char*)&_size, sizeof(_size));
    wf.write((char*)&_key, sizeof(_key));
    wf.write((char*)&_value, sizeof(_value));

    wf.close();
    cout << "Saved" << endl;
}

void _saveManager::LoadData(void)
{
    ifstream rf("./Save/sav.dat", ios::out | ios::binary);
	if (!rf)
    {
		cout << "No save file detected!" << endl;
		return;
	}

    // Deserializing profile
    rf.read((char*)&profile, sizeof(_gameManager::Profile));

    // Deserializing map data
    MapData.nodeList.clear();
    for (int i = 0; i < MapData.numNodes; ++i)
    {
        _mapData::Node* node = new _mapData::Node();

        node->ID = i;
        rf.read((char*)&node->pos.x, sizeof(float));
        rf.read((char*)&node->pos.y, sizeof(float));
        rf.read((char*)&node->nodeState, sizeof(short));
        rf.read((char*)&node->nodeType, sizeof(int));

        MapData.nodeList.push_back(node);
    }
    int currNodeID = 0;
    rf.read((char*)&currNodeID, sizeof(int));
    MapData.currentNode = MapData.nodeList[currNodeID];

    MapData.travelHistoryIDs.clear();
    size_t historySize = 0;
    rf.read((char*)&historySize, sizeof(size_t));
    for (size_t i = 0; i < historySize; ++i)
    {
        int selID = 0;
        rf.read((char*)&selID, sizeof(int));
        MapData.travelHistoryIDs.push_back(selID);
    }

    // Deserializing artifacts 
    rf.read((char*)&_size, sizeof(_size));
    rf.read((char*)&_key, sizeof(_key));
    rf.read((char*)&_value, sizeof(_value));
    for (int i = 0; i < _size; i++)
        artifactSaveData[_key[i]] = _value[i];
    HashtableToArtifactList();

    rf.close();
    cout << "Save loaded" << endl;
}
