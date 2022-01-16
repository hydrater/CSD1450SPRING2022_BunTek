#include <string>

using namespace std;

#define SaveManager _saveManager::Instance()

class _saveManager
{
private:
    static _saveManager* instance;
    _saveManager();
    ~_saveManager();

public:
    static _saveManager& Instance(void);
    struct profile
    {
        string name;
    };
    void SaveData(void);
    void LoadData(void);
};
