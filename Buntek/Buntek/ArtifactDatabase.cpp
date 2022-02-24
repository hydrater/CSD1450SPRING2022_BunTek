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
    case 0:
        return "test";
    case 1:
        return "test";
    case 2:
        return "test";
    case 3:
        return "test";
    case 4:
        return "test";
    case 30:
        return "test";
    case 120:
        return "test";
    case 140:
        return "test";
    case 220:
        return "test";
    case 221:
        return "test";
    case 300:
        return "test";
    case 400:
        return "test";
    case 401:
        return "test";
    case 420:
        return "test";
    case 500:
        return "test";
    case 520:
        return "test";
    case 530:
        return "test";
    case 540:
        return "test";
    case 541:
        return "test";
    case 630:
        return "test";
    case 631:
        return "test";
    case 640:
        return "test";
    default:
        return "Invalid ID";
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
    case 0:
        return "Increase damage";
    case 1:
        return "Increase max hp";
    case 2:
        return "Increase paddle speed";
    case 3:
        return "Increase ball speed";
    case 4:
        return "Increase ball spawn frequency";
    case 30:
        return "Increases healing";
    case 120:
        return "Battle won: Increase hp by 2, up to a max of 10 per stack";
    case 140:
        return "Battle won: Restores 10% of max hp";
    case 220:
        return "Wall bounce: Increases ball phase";
    case 221:
        return "Wall bounce: Increases ball speed";
    case 300:
        return "Ball phase >= 2 \nWhen dealing damage, increase ball speed";
    case 400:
        return "Ball phase >= 3 \nWhen dealing damage, restores hp";
    case 401:
        return "Ball phase >= 3 \nWhen dealing damage, deals extra damage";
    case 420:
        return "Ball phase >= 4 \nWhen dealing damage, spawns X ball in a random direction forward from the middle";
    case 500:
        return "Ball phase >= 3: \nWhen taking damage, opponent takes damage";
    case 520:
        return "Ball phase >= 4: \nWhen taking damage, spawns a ball in a random direction forward from the middle";
    case 530:
        return "Ball phase >= 3: \nWhen taking damage, if hp is below 20%, unable to take damage for a while";
    case 540:
        return "Ball phase >= 2: \nWhen taking damage, negate next damage taken";
    case 541:
        return "On death, restores 50% hp, destroy this artifact";
    case 630:
        return "Ball phase >= 2: \nWhen colliding with hostile balls, freeze the collided ball";
    case 631:
        return "Ball phase >= 2: \nWhen colliding with hostile balls, occasionally reflect collided ball";
    case 640:
        return "Ball phase >= 5: \nWhen colliding with hostile balls, destroy the collided ball";
    default:
        return "Invalid ID";
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
