#include "SaveManager.h"
#include "MapGenerator.h"
#include "AudioEngine.h"
#include <fstream>
#include <iostream>

_saveManager::_saveManager()
{
}

_saveManager::~_saveManager()
{
}

void _saveManager::AddToArtifactList(unsigned long id)
{
    map<unsigned long, int>::iterator it;

    it = artifactSaveData.find(id);
    if (it != artifactSaveData.end())
        it->second++;
    else
        artifactSaveData[id] = 1;
}

void _saveManager::RemoveFromArtifactList(unsigned long id)
{
    map<unsigned long, int>::iterator it;

    it = artifactSaveData.find(id);
    if (it != artifactSaveData.end())
    {
        it->second--;
        if (it->second <= 0)
            artifactSaveData.erase(id);
    }
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

    ofstream wf("./save.dat", ios::out | ios::binary);
    if (!wf)
    {
        cout << "Cannot save file!" << endl;
        return;
    }

    // Serializing profile
    wf.write((char*)&GameManager.playerProfile, sizeof(_gameManager::Profile));
    wf.write((char*)AudioManager.GetAudioVolume(), sizeof(float));
    wf.write((char*)AudioManager.GetMusicVolume(), sizeof(float));
    
    // Serializing map data
    for (int i = 0; i < MapData.numNodes; ++i)
    {
        wf.write((char*)&MapData.nodeList[i]->pos.x, sizeof(float));
        wf.write((char*)&MapData.nodeList[i]->pos.y, sizeof(float));
        wf.write((char*)&MapData.nodeList[i]->nodeState, sizeof(short));
        wf.write((char*)&MapData.nodeList[i]->nodeType, sizeof(int));
    }
    wf.write((char*)&MapData.penaltyPos.x, sizeof(float));
    wf.write((char*)&MapData.penaltyPos.y, sizeof(float));
    wf.write((char*)&MapData.currentNode->ID, sizeof(int));
    wf.write((char*)&GameManager.level, sizeof(int));

    size_t historySize = MapData.travelHistoryIDs.size();
    wf.write((char*)&historySize, sizeof(size_t));

    for (int selID : MapData.travelHistoryIDs)
        wf.write((char*)&selID, sizeof(int));

    // Serializing artifacts 
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
}

void _saveManager::LoadData(void)
{
    ifstream rf("./save.dat", ios::out | ios::binary);
	if (!rf)
    {
		cout << "No save file detected!" << endl;
		return;
	}

    // Deserializing profile
    rf.read((char*)&GameManager.playerProfile, sizeof(_gameManager::Profile));
    
    float temp = 0;
    rf.read((char*)&temp, sizeof(float));
    AudioManager.SetAudioVolume(temp);
    rf.read((char*)&temp, sizeof(float));
    AudioManager.SetMusicVolume(temp);

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
    rf.read((char*)&MapData.penaltyPos.x, sizeof(float));
    rf.read((char*)&MapData.penaltyPos.y, sizeof(float));
    int currNodeID = 0;
    rf.read((char*)&currNodeID, sizeof(int));
    MapData.currentNode = MapData.nodeList[currNodeID];
    rf.read((char*)&GameManager.level, sizeof(int));

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

    rf.close();
    cout << "Save loaded" << endl;
}

void _saveManager::DeleteSave(void)
{
    remove("./save.dat");
}
