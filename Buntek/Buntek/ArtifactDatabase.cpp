#include "ArtifactDatabase.h"
#include "SpriteRenderer.h"
#include "GameManager.h"
#include "BallBehavior.h"

_artifactdatabase::_artifactdatabase()
{

}

_artifactdatabase::~_artifactdatabase()
{

}

void _artifactdatabase::ExecuteBehavior(Artifact artifact, bool isPlayerTheCaster, GameObject* ball)
{
    // if (isPlayerTheCaster) means the player owns this artifact else it's the AI
    BallBehavior* tempBallBehavior;
    switch (artifact.ID)
    {
    case 120://Increase hp by 2 per battle won, up to a max of X
        GameManager.playerProfile.maxhp += 2 * artifact.count;
        break;
    case 140://Restores 10 hp of max hp
        GameManager.playerHp += 10;
        break;
    case 220://Increases ball bounce gain by X
        tempBallBehavior = ball->GetComponent<BallBehavior>();
        tempBallBehavior->ballPhase += artifact.count;
        break;
    case 221://Increases ball speed by X
        tempBallBehavior = ball->GetComponent<BallBehavior>();
        tempBallBehavior->SetTargetSpeed(tempBallBehavior->GetSpeed() * (1 + artifact.count / 10));
        break;
    case 300://B2: Increase ball speed by X
        tempBallBehavior = ball->GetComponent<BallBehavior>();
        tempBallBehavior->SetTargetSpeed(tempBallBehavior->GetSpeed() * (1 + artifact.count / 10));
        break;
    case 400://B3: Restores X hp
        if (isPlayerTheCaster) {
            GameManager.playerHp += artifact.count;
        }
        else {
            GameManager.enemyHp += artifact.count;
        }
        break;
    case 401://B3: Deals extra X damage
        tempBallBehavior = ball->GetComponent<BallBehavior>();
        tempBallBehavior->ballDamage += artifact.count;
        break;
    case 420://B4: Spawns X ball in a random direction forward from the middle
        if (GameManager.bh != NULL) {
            GameManager.bh->SpawnBall(isPlayerTheCaster);
        }
        break;
    case 500://B3: Opponent takes X damage
        if (isPlayerTheCaster) {
            GameManager.enemyHp -= artifact.count;
        }
        else {
            GameManager.playerHp -= artifact.count;
        }
        break;
    case 520://B4: Spawns X ball in a random direction forward from the middle
        if (GameManager.bh != NULL) {
            GameManager.bh->SpawnBall(isPlayerTheCaster);
        }
        break;
    case 521://B0: If hp is below <20%, unable to take damage for X second,

        break;
    case 540://B2: Negate next damage

        break;
    default:
        
        break;
    }
}

_artifactdatabase& _artifactdatabase::Instance(void)
{
    static _artifactdatabase instance;
    return instance;
}

string _artifactdatabase::GetName(unsigned long id)
{
    switch (id)
    {
    case 00000:
        return "test";
        break;
    default:
        return "Invalid ID";
        break;
    }
}

RarityTypes _artifactdatabase::GetRarity(unsigned long id)
{
    unsigned long temp = id % 100;
    temp /= 10;

    switch (temp)
    {
    case 2:
        return RarityTypes::Uncommon;
    case 3:
        return RarityTypes::Rare;
    case 4:
        return RarityTypes::Unique;
    default:
        return RarityTypes::Common;
    }
}

string _artifactdatabase::GetDescription(unsigned long id)
{
    switch (id)
    {
    case 00000:
        return "test description";
        break;
    default:
        return "Invalid ID";
        break;
    }
}

string _artifactdatabase::GetSpriteName(unsigned long id)
{
    switch (id)
    {
    case 00000:
        return "Steven.jpg";
        break;
    default:
        return "Steven.jpg";
        break;
    }
}

void _artifactdatabase::ApplyArtifactBehavior(vector<Artifact> artifactList, bool isPlayerTheCaster, GameObject* ball)
{
    for (size_t i = 0; i < artifactList.size(); ++i)
    {
        ExecuteBehavior(artifactList[i], isPlayerTheCaster, ball);
    }
}

unsigned long _artifactdatabase::DrawArtifact(void)
{
    int RNG = RandIntMinMax(0, 100);

    if (RNG < commonRate)
    {
        RNG = RandIntMinMax(0, (sizeof(common) / sizeof(*common)));
        return common[RNG];
    }
    else if (RNG < uncommonRate)
    {
        RNG = RandIntMinMax(0, (sizeof(uncommon) / sizeof(*uncommon)));
        return uncommon[RNG];
    }
    else
    {
        RNG = RandIntMinMax(0, (sizeof(rare) / sizeof(*rare)));
        return rare[RNG];
    }
}

unsigned long _artifactdatabase::DrawLegendary(void)
{
    int RNG = RandIntMinMax(0, (sizeof(legendary) / sizeof(*legendary)));
    return legendary[RNG];
}
