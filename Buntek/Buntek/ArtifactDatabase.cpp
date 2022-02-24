#include "ArtifactDatabase.h"
#include "SpriteRenderer.h"
#include "GameManager.h"
#include "BallBehavior.h"
#include <algorithm>

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
    bool flag = false;
    switch (artifact.ID)
    {
    case 120://Increase hp by 2 per battle won, up to a max of X
        GameManager.playerProfile.maxhp += 2 * artifact.count;
        break;
    case 140://Restores 10&% hp of max hp
        GameManager.playerHp += GameManager.playerProfile.maxhp / 10;
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
    case 530://B3: If hp is below <20%, unable to take damage for X second,
        if (isPlayerTheCaster) {
            if (GameManager.playerHp < GameManager.playerProfile.maxhp / 5) {
                for (size_t i = 0; i < GameManager.playerArtifactList.statusEffect.size(); ++i)
                {
                    if (GameManager.playerArtifactList.statusEffect[i].statusID == 00) {
                        GameManager.playerArtifactList.statusEffect[i].statusTimer += artifact.count;
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    _gameManager::Status temp;
                    temp.statusID = 00;
                    temp.statusTimer = (float)artifact.count;
                    GameManager.playerArtifactList.statusEffect.push_back(temp);
                }

            }
        }
        else {
            if (GameManager.playerHp < GameManager.enemyProfile.maxhp / 5) {
                for (size_t i = 0; i < GameManager.enemyArtifactList.statusEffect.size(); ++i)
                {
                    if (GameManager.enemyArtifactList.statusEffect[i].statusID == 00) {
                        GameManager.enemyArtifactList.statusEffect[i].statusTimer += artifact.count;
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    _gameManager::Status temp;
                    temp.statusID = 00;
                    temp.statusTimer = (float)artifact.count;
                    GameManager.enemyArtifactList.statusEffect.push_back(temp);
                }

            }
        }
        break;
    case 540://B2: Negate next damage
        if (ball->GetComponent<BallBehavior>()->ballPhase >= 2) {
            if (isPlayerTheCaster) {
                for (size_t i = 0; i < GameManager.playerArtifactList.statusEffect.size(); ++i)
                {
                    if (GameManager.playerArtifactList.statusEffect[i].statusID == 00) {
                        GameManager.playerArtifactList.statusEffect[i].statusCount = 1;
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    _gameManager::Status temp;
                    temp.statusID = 00;
                    temp.statusCount = 1;
                    GameManager.playerArtifactList.statusEffect.push_back(temp);
                }
            }
            else {
                for (size_t i = 0; i < GameManager.enemyArtifactList.statusEffect.size(); ++i)
                {
                    if (GameManager.enemyArtifactList.statusEffect[i].statusID == 00) {
                        GameManager.enemyArtifactList.statusEffect[i].statusCount = 1;
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    _gameManager::Status temp;
                    temp.statusID = 00;
                    temp.statusCount = 1;
                    GameManager.enemyArtifactList.statusEffect.push_back(temp);
                }
            }
        }
        break;
    case 630:

        break;
    case 631:

        break;
    case 640:

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
        return "Power";
    case 1:
        return "Tree of Life";
    case 2:
        return "Dexterity";
    case 3:
        return "Zoomer Goggles";
    case 4:
        return "Urgency";
    case 30:
        return "Health Buddy";
    case 120:
        return "Life of Champion";
    case 140:
        return "Healing Fountain";
    case 220:
        return "Bouncy Necklace";
    case 221:
        return "Ninja Shoes";
    case 300:
        return "Smacker";
    case 400:
        return "Health Thief";
    case 401:
        return "Dual Strike";
    case 420:
        return "Trickery";
    case 500:
        return "Lethal Cut";
    case 520:
        return "Vengeful Trickery";
    case 530:
        return "Last Resort";
    case 540:
        return "Last Stand";
    case 541:
        return "Defiance";
    case 630:
        return "Freezing Touch";
    case 631:
        return "Reflection";
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
        return "Ball phase >= 2\nWhen dealing damage, increase ball speed";
    case 400:
        return "Ball phase >= 3\nWhen dealing damage, restores hp";
    case 401:
        return "Ball phase >= 3\nWhen dealing damage, deals extra damage";
    case 420:
        return "Ball phase >= 4\nWhen dealing damage, spawns X ball in a random direction forward from the middle";
    case 500:
        return "Ball phase >= 3:\nWhen taking damage, opponent takes damage";
    case 520:
        return "Ball phase >= 4:\nWhen taking damage, spawns a ball in a random direction forward from the middle";
    case 530:
        return "Ball phase >= 3:\nWhen taking damage, if hp is below 20%, unable to take damage for a while";
    case 540:
        return "Ball phase >= 2:\nWhen taking damage, negate next damage taken";
    case 541:
        return "On death, restores 50% hp, destroy this artifact";
    case 630:
        return "Ball phase >= 2:\nWhen colliding with hostile balls, freeze the collided ball";
    case 631:
        return "Ball phase >= 2:\nWhen colliding with hostile balls, occasionally reflect collided ball";
    case 640:
        return "Ball phase >= 5:\nWhen colliding with hostile balls, destroy the collided ball";
    default:
        return "Invalid ID";
    }
}

string _artifactdatabase::GetSpriteName(unsigned long id)
{
    string spriteName = "Artifacts/" + GetName(id) + ".png";
    spriteName.erase(remove(spriteName.begin(), spriteName.end(), ' '), spriteName.end());
    return spriteName;
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
        RNG = RandIntMinMax(0, (int)common.size()-1);
        return common[RNG];
    }
    else if (RNG < uncommonRate)
    {
        RNG = RandIntMinMax(0, (int)uncommon.size() - 1);
        return uncommon[RNG];
    }
    else
    {
        RNG = RandIntMinMax(0, (int)rare.size() - 1);
        return rare[RNG];
    }
}

unsigned long _artifactdatabase::DrawLegendary(void)
{
    int RNG = RandIntMinMax(0, (int)legendary.size() - 1);
    return legendary[RNG];
}
