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

    // Make sure to update the size if total artifact count goes above
    int _size = 0;
    unsigned long _key[128] = {};
    int _value[128] = {};

    void ArtifactListToHashtable(void);
    void HashtableToArtifactList(void);

public:
    static _saveManager& Instance(void);

    // Profile
    _gameManager::Profile profile = {};

    // Arifact
    map<unsigned long, int> artifactSaveData;
    struct ArtifactInventory
    {
        vector<Artifact> behaviorList_Reflect;
        vector<Artifact> behaviorList_DealDamage;
        vector<Artifact> behaviorList_TakeDamage;
    }artifactInventory;

    void SaveData(void);
    void LoadData(void);
};
