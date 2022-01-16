#include <string>

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
        string name;
        string test;
    } profile;
    void SaveData(void);
    void LoadData(void);
};
