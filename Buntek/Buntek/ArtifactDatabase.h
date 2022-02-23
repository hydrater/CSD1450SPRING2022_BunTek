#pragma once
#include <vector>
#include <string>
#include "Entity.h"
using namespace std;

#define ArtifactDatabase _artifactdatabase::Instance()

enum class RarityTypes : short
{
    Common = 0,
    Uncommon = 1,
    Rare = 2,
    Unique = 3,
};

// Yo we can have a constellation based on rarity amounts
// Init a list, one for each behavior type
class Artifact
{
public:
    unsigned long ID = 0, count = 0;
};

class _artifactdatabase
{
private:
    _artifactdatabase();
    ~_artifactdatabase();
    // Overload if necessary
    void ExecuteBehavior(Artifact artifact, bool isPlayerTheCaster, GameObject* ball);

    // Drop chance
    const int commonRate = 60, uncommonRate = 90;

    // Store list of ID here
    const unsigned long common[9] = { 0, 1, 2, 3, 4, 300, 400, 401, 500};
    const unsigned long uncommon[6] = {120, 220, 221, 420, 520, 521};
    const unsigned long rare[3] = {30, 630, 631};
    const unsigned long legendary[4] = {140, 540, 541, 640};

public:
    static _artifactdatabase& Instance(void);
    string GetName(unsigned long id);
    RarityTypes GetRarity(unsigned long id);
    string GetDescription (unsigned long id);
    string GetSpriteName(unsigned long id);
    void ApplyArtifactBehavior(vector<Artifact> artifactList, bool isPlayerTheCaster, GameObject* ball = NULL);
    unsigned long DrawArtifact(void);
    unsigned long DrawLegendary(void);
};