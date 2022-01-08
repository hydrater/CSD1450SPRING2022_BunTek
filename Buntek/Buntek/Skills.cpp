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
	if (element == "astral")
	{
		this->Owner()->GetComponent<BallBehavior>()->elemAstral = true;
		this->Owner()->GetComponent<BallBehavior>()->SetSpeed(this->Owner()->GetComponent<BallBehavior>()->GetSpeed() * 1.50);
		if (effect == "covid")
		{

		}
		if (effect == "ricochet")
		{

		}
	}
	if (element == "virtual")
	{
		this->Owner()->GetComponent<BallBehavior>()->elemVirtual = true;
		//this->Owner()->GetComponent<BallBehavior>()-> opacity
		if (effect == "warp")
		{

		}
	}
	if (element == "elemental")
	{
		this->Owner()->GetComponent<BallBehavior>()->elemElemental = true;
		this->Owner()->GetComponent<BallBehavior>()->SetSpeed(this->Owner()->GetComponent<BallBehavior>()->GetSpeed() * 0.50);
		if (effect == "3splitter")
		{

		}
	}

	if (effect == "movement")
	{
		if (element == "curve")
		{

		}
		if (element == "Scurve")
		{

		}
		if (element == "wallMagnet")
		{

		}
		if (element == "spiral")
		{

		}
	}
}
