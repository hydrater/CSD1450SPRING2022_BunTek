#include "BallBehavior.h"
#include "GameScript.h"
#include "GameManager.h"
#include "SpriteRenderer.h"
#include "Skills.h"

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
	if (effect == "element")
	{
		if (element == "astral")
		{
			//this->Owner()->
		}
		if (element == "virtual")
		{

		}
		if (element == "elemental")
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

	if (effect == "special")
	{
		if (element == "warp")
		{

		}
		if (element == "covid")
		{

		}
		if (element == "ricochet")
		{

		}
		if (element == "splitter")
		{

		}
	}
}
