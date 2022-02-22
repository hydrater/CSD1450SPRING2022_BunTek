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
};
