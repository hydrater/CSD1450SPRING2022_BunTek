/*!*****************************************************************************
\file Button.cpp
\author: <to be inserted>
\co-authors: Algene Tan Chuan Hong, Isaiah Lim Ji Rong, Steven Koe, Bryan Boh Tai Hong, Goh Kiat Beng
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Button behaviour
*******************************************************************************/

#include "Button.h"
#include "GameManager.h"
#include "AudioEngine.h"

void DefaultHoverEffect(Button*);
void DefaultNotHoverEffect(Button*);

Button::Button(void)
{
	HoverEffect = &DefaultHoverEffect;
	NotHoverEffect = &DefaultNotHoverEffect;
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
	if (GameManager.disableInteraction)
		return;

	if (tr != NULL && sr != NULL) {
		tr->ScaleTexture(sr);
	}
	if (CheckTriggered(GameManager.GetCursorPosition()) && canHover) {
		if (HoverEffect != NULL) {
			HoverEffect(this);
		}
		if (AEInputCheckTriggered(AEVK_LBUTTON) && ClickEffect != NULL) {
			ClickEffect(this);
		}
		else if (AEInputCheckReleased(AEVK_LBUTTON) && canClick)
		{
			ButtonEffect(this);
		}
	}
	else if (HoverEffect != NULL && NotHoverEffect != NULL) {
		NotHoverEffect(this);
	}
}

void Button::SetClickable(bool _canClick) {
	canClick = _canClick;
}

void Button::SetHoverable(bool _canHover) {
	canHover = _canHover;
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

void DefaultHoverEffect(Button* button) {
	if (button->hoverplay) {
		AudioManager.LoadSound("ButtonHover.wav");
		AudioManager.PlayClip("ButtonHover.wav");
		button->hoverplay = false;
	}
}

void DefaultNotHoverEffect(Button* button) {
	if (!button->hoverplay) {
		AudioManager.UnloadSound("ButtonHover.wav");
		button->hoverplay = true;
	}
}
