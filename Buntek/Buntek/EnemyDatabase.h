#pragma once
#include <vector>
#include <string>
using namespace std;

#define EnemyDatabase _enemydatabase::Instance()

class _enemydatabase
{
private:
    static _enemydatabase* instance;
    _enemydatabase();
    ~_enemydatabase();

public:
    static _enemydatabase& Instance(void);
    vector<string> EnemyName;
    vector<string> EnemyDesc;
};