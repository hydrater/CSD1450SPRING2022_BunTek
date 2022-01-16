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

    StringBuffer s;
    Writer<StringBuffer> writer(s);

    writer.StartObject();
    writer.Key("name");
    writer.String("Steven");
    writer.Key("a");
    writer.StartArray();
    for (unsigned i = 0; i < 4; i++)
        writer.Uint(i);
    writer.EndArray();
    writer.EndObject();

    doc.Parse(s.GetString());

    ofstream ofs("./Save/output.json");
    OStreamWrapper osw(ofs);

    Writer<OStreamWrapper> asd(osw);
    doc.Accept(asd);
}

void _saveManager::LoadData(void)
{
    Document doc;

    ifstream ifs("./Save/alice.json");
    IStreamWrapper isw(ifs);

    doc.ParseStream(isw);

    printf("Title = %s\n", doc["book"].GetString());
}
