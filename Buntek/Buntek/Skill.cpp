#include "BallBehavior.h"
#include "GameScript.h"
#include "GameManager.h"
#include "SpriteRenderer.h"
#include "Skill.h"

Skill :: Skill()
{

}
Skill :: ~Skill()
{

}

void Skill :: Start(void)
{
	transform = this->Owner()->transform;
}