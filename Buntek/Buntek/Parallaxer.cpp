#include "Parallaxer.h"

Parallaxer::Parallaxer(void)
{
	distance = 0;
}

Parallaxer::~Parallaxer(void)
{

}

void Parallaxer::Start(void)
{
	anchorPoint = this->Owner()->transform->worldposition;
}

void Parallaxer::Update(void)
{
	Vector2 vecDiff = GameManager.GetCursorPosition();

	vecDiff.Divide(distance);

	this->Owner()->transform->worldposition = anchorPoint + vecDiff;
}