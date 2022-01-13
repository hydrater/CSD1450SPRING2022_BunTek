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
	
	if (distance > 0) {
		vecDiff.Divide(distance);
		if (inverseMouseX) {
			vecDiff.x = -vecDiff.x;
		}
		if (inverseMouseY) {
			vecDiff.y = -vecDiff.y;
		}

		this->Owner()->transform->worldposition = anchorPoint + vecDiff;
	}
	else if (distance == 0){
		if (inverseMouseX) {
			vecDiff.x = -vecDiff.x;
		}
		if (inverseMouseY) {
			vecDiff.y = -vecDiff.y;
		}
		this->Owner()->transform->worldposition = anchorPoint + vecDiff;
	}
	
}