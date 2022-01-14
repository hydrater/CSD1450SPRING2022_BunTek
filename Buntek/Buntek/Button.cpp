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
	if (CheckTriggered(GameManager.GetCursorPosition())) {
		if (HoverEffect != NULL) {
			HoverEffect(this);
		}
		if (AEInputCheckTriggered(AEVK_LBUTTON) && ClickEffect != NULL) {
			ClickEffect(this);
		}
		else if (AEInputCheckReleased(AEVK_LBUTTON))
		{
			ButtonEffect(this);
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
	//add check for rotated button???
}

