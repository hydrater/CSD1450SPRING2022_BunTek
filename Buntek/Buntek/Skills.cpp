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
	Transform* tempTransform = Owner()->transform;
}

void Skills:: Effects(string effect, string element)
{
	if (element == "astral")
	{
		this->Owner()->GetComponent<BallBehavior>()->elemAstral == true;
		if (effect == "covid")
		{

		}
		if (effect == "ricochet")
		{

		}
	}
	if (element == "virtual")
	{
		this->Owner()->GetComponent<BallBehavior>()->elemVirtual == true;
		if (effect == "warp")
		{

		}
	}
	if (element == "elemental")
	{
		this->Owner()->GetComponent<BallBehavior>()->elemElemental == true;
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
