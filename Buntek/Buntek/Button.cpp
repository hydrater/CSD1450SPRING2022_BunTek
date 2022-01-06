#include "Button.h"
#include "GameManager.h"



Button::Button(void)
{
}

Button::~Button(void)
{
}

void Button::Start(void)
{
	transform = this->Owner()->transform;
}

void Button::Update(void)
{
	if (tr != NULL || sr != NULL) {
		tr->ScaleTexture(sr);
	}
	if (AEInputCheckTriggered(AEVK_LBUTTON))
	{
		bool triggered = CheckTriggered(GameManager.GetCursorPosition());
		if (triggered) {
			ButtonEffect();
		}
	}
}

bool Button::CheckTriggered(Vector2 mousePos) {
	if (transform->worldposition.x - sr->GetHalfWidth() < mousePos.x && transform->worldposition.x + sr->GetHalfWidth() > mousePos.x) {

		if (transform->worldposition.y - sr->GetHalfHeight() < mousePos.y && transform->worldposition.y + sr->GetHalfHeight() > mousePos.y) {
			return true;
		}
	}
	return false;
	//add check for rotated button
}

