#include <string>
#include <vector>
#include "ArtifactDatabase.h"

#define SaveManager _saveManager::Instance()

using namespace std;

class _saveManager
{
private:
    static _saveManager* instance;
    _saveManager();
    ~_saveManager();

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

        // Artifact
        int artifactCount[2048];
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
