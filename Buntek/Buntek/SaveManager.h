/*!*****************************************************************************
\file SaveManager.h
\project Beyond Aurorean Skies
\author: Algene Tan Chuan Hong (90%)
\co-authors: Isaiah Lim Ji Rong (2.5%), Steven Koe (2.5%), Bryan Boh Tai Hong (2.5%), Goh Kiat Beng (2.5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Managers the save data/files
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
*******************************************************************************/

#include <string>
#include <vector>
#include <map>
#include "ArtifactDatabase.h"
#include "GameManager.h"

#define SaveManager _saveManager::Instance()

using namespace std;

class _saveManager
{
private:
    _saveManager();
    ~_saveManager();

    // Make sure to update the size if total amount of artifacts created goes above the value
    int _size = 0;
    unsigned long _key[128] = {};
    int _value[128] = {};


public:
    static _saveManager& Instance(void);

    // Arifact
    void AddToArtifactList(unsigned long id);
    void RemoveFromArtifactList(unsigned long id);
    map<unsigned long, int> artifactSaveData;

    void SaveData(void);
    void LoadData(void);
    void DeleteSave(void);
};
