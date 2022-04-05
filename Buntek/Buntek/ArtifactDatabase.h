/*!*****************************************************************************
\file ArtifactDatabase.h
\author: Bryan Boh Tai Hong (80%)
\co-authors: Algene Tan Chuan Hong (5%), Isaiah Lim Ji Rong (5%), Steven Koe (5%), Goh Kiat Beng (5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Artifact Database
*******************************************************************************/

#pragma once
#include <vector>
#include <string>
#include "Entity.h"
#include "Vector2.h"
using namespace std;

#define ArtifactDatabase _artifactdatabase::Instance()

struct Status
{
    int statusID = NULL;
    float statusTimer = 0;
    float statusCount = 0;
};

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
    unsigned long ID = 0;
    int count = 0;
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
    const vector<unsigned long> common{0, 1, 2, 3, 4, 300, 400, 401, 500};
    const vector<unsigned long> uncommon{120, 220, 221, 420, 520};
    const vector<unsigned long> rare{30, 530, 630, 631};
    const vector<unsigned long> legendary{140, 540, 541, 640};

public:
    static _artifactdatabase& Instance(void);
    string GetName(unsigned long id);
    RarityTypes GetRarity(unsigned long id);
    string GetDescription (unsigned long id);
    string GetSpriteName(unsigned long id);
    void ApplyArtifactBehavior(vector<Artifact> artifactList, bool isPlayerTheCaster, GameObject* ball = NULL);
    unsigned long DrawArtifact(void);
    unsigned long DrawLegendary(void);
    vector<unsigned long> DrawThreeArtifacts(void);
};