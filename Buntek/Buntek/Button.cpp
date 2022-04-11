/*!*****************************************************************************
\file Button.cpp
\project Beyond Aurorean Skies
\author: Bryan Boh Tai Hong (80%)
\co-authors: Algene Tan Chuan Hong (5%), Isaiah Lim Ji Rong (5%), Steven Koe (5%), Goh Kiat Beng (5%)
\par DP email: lim.i@digipen.edu,t.chuanhongalgene@digipen.edu,b.boh@digipen.edu,kiatbeng.goh,steven.k@digipen.edu
\brief: Handles Button behaviour
All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
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
	//button trigger logic
	if (CheckTriggered(GameManager.GetCursorPosition()) && canHover) {
		if (HoverEffect != NULL) {
			HoverEffect(this);
		}
		if (AEInputCheckTriggered(AEVK_LBUTTON) && canClick && ClickEffect != NULL) {
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
}
//button default hover effect
void DefaultHoverEffect(Button* button) {
	if (button->hoverplay) {
		AudioManager.LoadSound("ButtonHover.wav");
		AudioManager.PlayClip("ButtonHover.wav");
		if (button->sr != NULL) {
			button->sr->Size(button->sr->GetHalfWidth() * 2 * 1.2f, button->sr->GetHalfHeight() * 2 * 1.2f);
		}
		if (button->tr != NULL) {
			button->tr->SetFontSize(button->tr->GetFontSize() * 1.2f);
		}
		button->hoverplay = false;
	}
}
//button default unhover effect
void DefaultNotHoverEffect(Button* button) {
	if (!button->hoverplay) {
		AudioManager.UnloadSound("ButtonHover.wav");
		if (button->sr != NULL) {
			button->sr->Size(button->sr->GetHalfWidth() * 2 / 6 * 5, button->sr->GetHalfHeight() * 2 / 6 * 5);
		}
		if (button->tr != NULL) {
			button->tr->SetFontSize(button->tr->GetFontSize() / 6 * 5);
		}
		button->hoverplay = true;
	}
}
