#include <string>
#include <vector>

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
        int test[10];
    } profile = {};
    struct MapSave
    {
        float NodeWidth[32];
        float NodeHeight[32];
    };

    void SaveData(void);
    void LoadData(void);
};
