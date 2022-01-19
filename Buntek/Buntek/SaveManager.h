#include <string>
#include <vector>
#include <map>
#include "ArtifactDatabase.h"

#define SaveManager _saveManager::Instance()

using namespace std;

class _saveManager
{
private:
    static _saveManager* instance;
    _saveManager();
    ~_saveManager();

    // Make sure to update the size if total artifact count goes above
    int _size = 0;
    unsigned long _key[128] = {};
    int _value[128] = {};

    map<unsigned long, int> artifactSaveData;

public:
    static _saveManager& Instance(void);
    struct Profile
    {
        // Stats
        int health;
        int damage;
        int paddleSpeed;
        int ballSpeed;
        int ballSpawnFreq;

        // Current
        float hp;
        int stardust;
        int mapSize;
    } profile = {};

    struct MapSave
    {
        float NodeWidth[64];
        float NodeHeight[64];
    }mapSave = {};

    struct ArtifactInventory
    {
        vector<Artifact> behaviorList_Reflect;
        vector<Artifact> behaviorList_DealDamage;
        vector<Artifact> behaviorList_TakeDamage;
    };

    void SaveData(void);
    void LoadData(void);
};
