#include "SaveManager.h"
#include <fstream>
#include <vector>
#include <iostream>
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/ostreamwrapper.h"
#include "rapidjson/writer.h"
#include "rapidjson/document.h"

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
    Document doc;
    const char json[] = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";

    profile.name = "Steven";
    doc.Parse(json);


    ofstream ofs("./Save/output.json");
    OStreamWrapper osw(ofs);

    Writer<OStreamWrapper> writer(osw);
    doc.Accept(writer);
}

void _saveManager::LoadData(void)
{
    Document doc;

    ifstream ifs("./Save/alice.json");
    IStreamWrapper isw(ifs);

    doc.ParseStream(isw);

    printf("Title = %s\n", doc["book"].GetString());
}
