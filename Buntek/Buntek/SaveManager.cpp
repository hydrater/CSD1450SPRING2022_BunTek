#include "SaveManager.h"
#include <fstream>
#include <vector>
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/writer.h"

using namespace std;
using namespace rapidjson;

_saveManager* _saveManager::instance = 0;

_saveManager::_saveManager()
{
}

_saveManager::~_saveManager()
{
}

_saveManager& _saveManager::Instance(void)
{
    if (instance != 0)
    {
        return *instance;
    }
    instance = new _saveManager();
    return *instance;
}

void _saveManager::SaveData(void)
{
    Document d;
    //d.Parse(json);

    ofstream ofs("output.json");
    OStreamWrapper osw(ofs);

    Writer<OStreamWrapper> writer(osw);
    d.Accept(writer);
}

void _saveManager::LoadData(void)
{
    using namespace rapidjson;
    using namespace std;

    ifstream ifs("./Save/alice.json");
    IStreamWrapper isw(ifs);

    Document d;
    d.ParseStream(isw);

    printf("Title = %s\n", d["book"].GetString());
}
