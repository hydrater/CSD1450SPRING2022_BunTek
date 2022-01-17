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

    writer.Key("health");
    writer.Int(profile.health);
    writer.Key("damage");
    writer.Int(profile.damage);
    writer.Key("paddleSpeed");
    writer.Int(profile.paddleSpeed);
    writer.Key("ballSpeed");
    writer.Int(profile.ballSpeed);
    writer.Key("ballSpawnFreq");
    writer.Int(profile.ballSpawnFreq);

    writer.Key("hp");
    writer.Double(profile.hp);
    writer.Key("stardust");
    writer.Int(profile.stardust);

    writer.StartArray();
    for (unsigned i = 0; i < 4; i++)
        writer.Uint(i);
    writer.EndArray();
    writer.EndObject();

    doc.Parse(s.GetString());

    ofstream ofs("./Save/sav.dat");
    OStreamWrapper osw(ofs);

    Writer<OStreamWrapper> asd(osw);
    doc.Accept(asd);
}

void _saveManager::LoadData(void)
{
    Document doc;

    ifstream ifs("./Save/sav.dat");
    IStreamWrapper isw(ifs);

    doc.ParseStream(isw);

    profile.health = doc["health"].GetInt();
    profile.damage = doc["damage"].GetInt();
    profile.paddleSpeed = doc["paddleSpeed"].GetInt();
    profile.ballSpeed = doc["ballSpeed"].GetInt();
    profile.ballSpawnFreq = doc["ballSpawnFreq"].GetInt();

    profile.hp = doc["hp"].GetInt();
    profile.stardust = doc["stardust"].GetInt();
}
