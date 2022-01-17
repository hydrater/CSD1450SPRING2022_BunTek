#pragma once
#include <vector>
#include <string>
using namespace std;

#define ArtifactDatabase _artifactdatabase::Instance()

enum class RarityTypes : short
{
    Common = 0,
    Rare = 1,
    Lunary = 2,
    Astral = 3,
    Universal = 4
};

class Artifact
{
private:

public:
    int id = 0;
    string description;

    RarityTypes rarity = RarityTypes::Common;
};

class _artifactdatabase
{
private:
    static _artifactdatabase* instance;
    _artifactdatabase();
    ~_artifactdatabase();

public:
    static _artifactdatabase& Instance(void);

};