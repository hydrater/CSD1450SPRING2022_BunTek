#include "BallBehavior.h"
#include "GameScript.h"
#include "GameManager.h"
#include "SpriteRenderer.h"
#include "Skills.h"
#include "Component.h"

Skills::Skills()
{

}
Skills :: ~Skills()
{

}

void Skills :: Start(void)
{
	transform = this->Owner()->transform;
}

void Skills:: Update(void)
{
	//this->Owner()->GetComponent<BallBehavior>()-> nt rly sure what to put here
}

void Skills:: Effects(string effect, string element)
{

}
